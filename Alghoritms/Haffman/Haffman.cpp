#include "Node.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <locale>
#pragma warning(disable : 4996)

// сравнивает количество повторений Node
class LowestPriority {
public:
	bool operator() (const Node::node_ptr& left, const Node::node_ptr& rigth)
	{
		if (left->get_freq() > rigth->get_freq())
			return true;
		return false;
	}
};

// priority_queue - по сути сортированный вектор в данном случае
using queue_t = std::priority_queue < Node::node_ptr, std::vector<Node::node_ptr>, LowestPriority>;

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

// создаём дерево
void make_queue(queue_t & queue, std::vector<int> & frequency)
{
	unsigned char ch = 0;
	// заполняем очередь данными
	std::for_each(frequency.begin(), frequency.end(), [&ch, &queue](const int& value) {
		if (value != 0) {
			Node::node_ptr node = std::make_shared<Node>(ch, value); // создаем указатель на Node
			queue.push(node); // добавляем в очередь
		}
		ch++;
		});

	while (queue.size() != 1)
	{
	    // берем две верхние Node с очереди
		Node::node_ptr left = queue.top(); // присваиваем верхний Node очередь переменной
		queue.pop(); // удаляем этот Node

		// делаем тоже самое
		Node::node_ptr right = queue.top();
		queue.pop();


		std::string name = left->get_name() + right->get_name(); // складываем символы
		// создаём новый Node из двух старых, передаём уже созданный name и складываем их повторения
		Node::node_ptr _new = std::make_shared<Node>(name, left->get_freq() + right->get_freq());
		// тут мы просто настраиваем список
		left->parent = _new;
		right->parent = _new;
		_new->left = left;
		_new->right = right;
		queue.push(_new); // добавляем данный Node в очередь
		// сокращаем до тех пор , пока не останется одна Node в очереди
	}

}

void make_codes(Node::node_ptr & node, std::string str, std::vector<std::string> & codes)
{
    // далее проходимся по дереву и заполняем вектор данными

    // левая - 0, правая - 1
	if (node->left != nullptr) {
		make_codes(node->left, str + "0", codes);
	}
	if (node->right != nullptr) {
		make_codes(node->right, str + "1", codes);
	}

	// если у Node нет левого и правого Node, то означает, что код для символа готов
	if (node->left == nullptr && node->right == nullptr) {
		node->set_code(str); // устанавливаем код
		codes[(int)node->get_char()] = str; // заполняем вектор кодов
		//std::cout << "[" << (char)node->get_char() << "] = " << str << std::endl;
	}

}

// функция преобразует исходный текст в код
std::string message_to_code(std::string filename, const std::vector<std::string> & codes)
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
		message += codes[static_cast<unsigned char>(ch)];
	}
	ifs.close();
	return message;
}

void write_to_file(std::string filename, const std::string & text, std::vector<std::string> & codes, std::vector<int> & frequency) {
	std::ofstream ofs(filename, std::ofstream::ate);

	if (!ofs) {
		std::cerr << "Error in [" << __func__ << "]: " << strerror(errno);
	}
	ofs << "Частота повторений символов: " << std::endl;

	unsigned char ch = 0;
    // вывод повторений для каждого символа
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
    // вывод кодов для каждого символа
	auto print_codes = [&ch, &ofs, &codes](const int& value) {
		if (ch == 10) {
			ofs << "[" << "\\n" << "] = " << codes[(int)ch] << std::endl;
			ch++;
			return;
		}
		if (value != 0)
			ofs << "[" << ch << "]  = " << codes[(int)ch] << std::endl;
		ch++;
	};
	std::for_each(frequency.begin(), frequency.end(), print_codes);
	ofs << std::endl << "Итоговый текст: " << std::endl;
	ofs << text;
	ofs.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // вектор который для количества повторений в строке
    // индекс - символ , значение - количество повторений
    std::vector<int> frequency(255, 0);

    std::string filename = "text.txt"; // входной файл
    std::string filename_write = "text_out.txt"; // выходной файл
    read_frequency(filename, frequency); //чтение строки и запись повторений

	queue_t queue; // создаем очередь
	make_queue(queue, frequency); // преобразуем очередь N-е количество Node в один
	Node::node_ptr root = queue.top(); // берем верхний Node
	std::vector<std::string> codes{ 255,"" }; //хеш таблица кодирования (ключ - символ, значение - код)
	make_codes(root, "", codes); // кодирует символы
	std::string message = message_to_code(filename, codes); // получаем кодированное сообщение
	write_to_file(filename_write, message, codes, frequency); // записываем в файл

	// очистка очереди
	while (!queue.empty())
	{
		queue.pop();
	}
}

