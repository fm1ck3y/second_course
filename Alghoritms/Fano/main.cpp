#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

#pragma warning(disable : 4996)

// данная функция читает данные из файла и записывает их в вектор
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

// рекурсивная функция для заполнения символов кодами
void binary_dfs(std::map<unsigned char, std::string> &words, const std::vector<int> &frequency, const std::vector<unsigned char> &unique,
                int start, int end) {
    if (end-start <= 1) return; // проверка на диапазон
    int diff = (end - start) / 2; // делим диапазон пополам
    // первую половину диапазона заполняем нулями
    for (int i = start; i < start+diff; ++i) {
        words[unique[i]] += "0";
    }
    // вторую половину диапазно заполняем единицами
    for (int i = start+diff; i < end; ++i) {
        words[unique[i]] += "1";
    }
    // запускаем рекурсивно функцию передавая основным параметры и диапазон = первой половине данного
    binary_dfs(words, frequency, unique, start, start+diff);
    // запускаем рекурсивно функцию передавая основным параметры и диапазон = второй половине данного
    binary_dfs(words, frequency, unique, start+diff, end);
}

// функция преобразует исходное сообщение из файла в кодированное сообщение
std::string message_to_code(std::string filename, std::map<unsigned char, std::string> &words)
{
    // инициализируется message
    std::string message{ "" };
    // открывается файл
    std::ifstream ifs(filename, std::ifstream::binary);
    if (!ifs) {
        std::cerr << "Error in [" << __func__ << "]" << std::endl;
    }
    char ch;
    // считывается исходная строка
    while (true) {
        ifs.read(&ch, 1);
        if (ifs.eof())
            break;
        // каждый символ заменяется своим кодом
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
    // вывод повторений для каждого символа
    auto print_frequency = [&ch, &ofs](const int& value) {
        // эта проверка для символа переноса строки (чтобы выглядело красиво)
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
    // вывод кодов для каждого символа
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
    // вектор который для количества повторений в строке
    // индекс - символ , значение - количество повторений
    std::vector<int> frequency(255, 0);
    std::string filename = "text.txt"; // входной файл
    std::string filename_write = "text_out.txt"; // выходной файл
    read_frequency(filename, frequency); //чтение строки и запись повторений
    std::map<unsigned char, std::string> words = {}; // хеш таблица кодирования (ключ - символ, значение - код)
    unsigned char ch = 0;
    // создаем вектор уникальных символов
    std::vector<unsigned char> unique;
    // заполняем вектор уникальными символами из текста
    for_each(frequency.begin(), frequency.end(), [&words, &ch, &unique](const int &value) {
        if (value != 0) {
            words[ch] = "";
            unique.push_back(ch);
        }
        ch++;
    });

    // запускаем функцию заполнения символов кодами
    binary_dfs(words, frequency, unique, 0, unique.size());

    std::string message_encrypt {""};
    message_encrypt = message_to_code(filename,words); // кодирует сообщение
    write_to_file(filename_write,message_encrypt,words,frequency); // вывод всю информацию в файл
    return 0;
}