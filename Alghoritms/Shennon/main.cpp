#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

#pragma warning(disable : 4996)

void read_frequency(std::string filename, std::vector<int> &frequency) {
    std::ifstream ifs(filename, std::ifstream::binary);
    if (!ifs) {
        std::cerr << "Error in [" << __func__ << "]" << std::endl;
    }

    while (true) {
        char ch;
        ifs.read(&ch, 1);
        if (ch == 13) continue;
        if (ifs.eof())
            break;
        frequency[static_cast<unsigned char>(ch)]++;
    }
    ifs.close();
}

void binary_dfs(std::map<unsigned char, std::string> &words, const std::vector<int> &frequency, const std::vector<unsigned char> &unique,
           int start, int end) {
    if (end-start <= 1) return;
    int diff = (end - start) / 2;
    for (int i = start; i < start+diff; ++i) {
        words[unique[i]] += "0";
    }
    for (int i = start+diff; i < end; ++i) {
        words[unique[i]] += "1";
    }
    binary_dfs(words, frequency, unique, start, start+diff);
    binary_dfs(words, frequency, unique, start+diff, end);
}

std::string message_to_code(std::string filename, std::map<unsigned char, std::string> &words)
{
    std::string message{ "" };
    std::ifstream ifs(filename, std::ifstream::binary);
    if (!ifs) {
        std::cerr << "Error in [" << __func__ << "]" << std::endl;
    }
    char ch;
    while (true) {
        ifs.read(&ch, 1);
        if (ifs.eof())
            break;
        message += words[static_cast<unsigned char>(ch)];
    }
    ifs.close();
    return message;
}

void write_to_file(std::string filename, const std::string & text, std::map<unsigned char, std::string> &words, std::vector<int> & frequency) {
    std::ofstream ofs(filename, std::ofstream::ate);

    if (!ofs) {
        std::cerr << "Error in [" << __func__ << "]" << std::endl;
    }
    ofs << "Частота повторений символов: " << std::endl;

    unsigned char ch = 0;
    auto print_frequency = [&ch, &ofs](const int& value) {
        if (ch == 10) {
            ofs << "[" << "\\n" << "] = " << value << std::endl;
            ch++;
            return;
        }
        if (value != 0)
            ofs << "[" << ch << "]  = " << value << std::endl;
        ch++;
    };
    std::for_each(frequency.begin(), frequency.end(), print_frequency);

    ch = 0;
    ofs << std::endl << "Коды каждого символа:" << std::endl;
    auto print_codes = [&ch, &ofs, &words](const int& value) {
        if (ch == 10) {
            ofs << "[" << "\\n" << "] = " << words[ch] << std::endl;
            ch++;
            return;
        }
        if (value != 0)
            ofs << "[" << ch << "]  = " << words[ch] << std::endl;
        ch++;
    };
    std::for_each(frequency.begin(), frequency.end(), print_codes);
    ofs << std::endl << "Итоговый текст: " << std::endl;
    ofs << text;
    ofs.close();
}


int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<int> frequency(255, 0);
    std::string filename = "text.txt";
    std::string filename_write = "text_out.txt";
    read_frequency(filename, frequency);
    std::map<unsigned char, std::string> words = {};
    unsigned char ch = 0;
    std::vector<unsigned char> unique;
    for_each(frequency.begin(), frequency.end(), [&words, &ch, &unique](const int &value) {
        if (value != 0) {
            words[ch] = "";
            unique.push_back(ch);
        }
        ch++;
    });

    binary_dfs(words, frequency, unique, 0, unique.size());

    std::string message_encrypt {""};
    message_encrypt = message_to_code(filename,words);
    write_to_file(filename_write,message_encrypt,words,frequency);
    return 0;
}
