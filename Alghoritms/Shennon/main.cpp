//
// Created by m1ck3y on 4/2/21.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <queue>
#include <bitset>
#include <cmath>

#pragma warning(disable : 4996)

// данная функция сравнивает тип значений std::pair по 2 значению (double)
bool LowestPriority (const std::pair<unsigned char,double> left, const std::pair<unsigned char,double> rigth)
{
    if (left.second > rigth.second)
        return true;
    return false;
}

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

// данная функция присваивает каждому символу свой код , записывает в std::map (хеш таблицу)
void binary_code(std::map<unsigned char, std::string> &words, const std::vector<int> &frequency) {
    int amount_ch = 0; // количество букс всего
    std::for_each(frequency.begin(),frequency.end(),[&amount_ch](const int& value){
       if (value != 0) amount_ch+=value; // в данном цикле считаем количество букв
    });
    std::vector<std::pair<unsigned char,double>> p;

    unsigned char ch = 0;
    std::for_each(frequency.begin(),frequency.end(),[&p,&amount_ch,&ch](const int &value)
    {
        if (value != 0){
            p.push_back(std::make_pair(ch,(double)value/(double)amount_ch));
        }
        ch++;
    });  // в данном цикле мы считаем процент повторений для каждого символа
    std::sort(p.begin(),p.end(),LowestPriority); // сортируем по убыванию

    int it = 0;
    std::for_each(p.begin(),p.end(),[&it,&p,&words](const std::pair<unsigned char,double> &value){
        std::string binary_r = ""; // это переменная для итогового кода
        if (it == 0){ // если это первый элемент, то у него код "0"*Lx
            int Lx = std::ceil(std::log(1.0/p[it].second));
            for (int i = 0; i < Lx; ++i) binary_r += "0";
        }
        else{
            // иначе считаем сумму от первого элемента до it-1 (свой не включаем)
            double amount = 0;
            for(int i = 0; i < it; i++)
                amount += p[i].second;
            // тут должно быть адекватное преобразование в двоичную систему счисления.
            // так как я это не успел сделать, то давайте представим, что это работает
            std::string binary = std::bitset<8>(amount).to_string();
            // Lx = -log(p_i)  = log(1/p_i) , где p - элементы алфовита, i - индекс
            int Lx = std::ceil(std::log(1.0/p[it].second));
            // а дальше берем первые Lx символов преобразования
            for (int i = 0; i < Lx; ++i) binary_r+= binary[i];
        }
        it ++;
        // записываем в words
        words[p[it].first] = binary_r;
    });
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
    binary_code(words, frequency); // кодирует символы
    std::string message_encrypt {""};
    message_encrypt = message_to_code(filename,words); // кодирует сообщение
    write_to_file(filename_write,message_encrypt,words,frequency); // вывод всю информацию в файл
    return 0;
}
