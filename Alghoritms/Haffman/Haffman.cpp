#include "Node.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <locale>
#pragma warning(disable : 4996)
class LowestPriority {
public:
	bool operator() (const Node::node_ptr& left, const Node::node_ptr& rigth)
	{
		if (left->get_freq() > rigth->get_freq())
			return true;
		return false;
	}
};

using queue_t = std::priority_queue < Node::node_ptr, std::vector<Node::node_ptr>, LowestPriority>;

void read_frequency(std::string filename, std::vector<int>& frequency)
{
	std::ifstream ifs(filename, std::ifstream::binary);
	if (!ifs) {
		std::cerr << "Error in [" << __func__ << "]: " << strerror(errno);
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

void make_queue(queue_t & queue, std::vector<int> & frequency)
{
	unsigned char ch = 0;
	std::for_each(frequency.begin(), frequency.end(), [&ch, &queue](const int& value) {
		if (value != 0) {
			Node::node_ptr node = std::make_shared<Node>(ch, value);
			queue.push(node);
		}
		ch++;
		});

	while (queue.size() != 1)
	{
		Node::node_ptr left = queue.top();
		queue.pop();

		Node::node_ptr right = queue.top();
		queue.pop();
		std::string name = left->get_name() + right->get_name();
		Node::node_ptr _new = std::make_shared<Node>(name, left->get_freq() + right->get_freq());
		left->parent = _new;
		right->parent = _new;
		_new->left = left;
		_new->right = right;
		queue.push(_new);
	}

}

void make_codes(Node::node_ptr & node, std::string str, std::vector<std::string> & codes)
{
	if (node->left != nullptr) {
		make_codes(node->left, str + "0", codes);
	}
	if (node->right != nullptr) {
		make_codes(node->right, str + "1", codes);
	}

	if (node->left == nullptr && node->right == nullptr) {
		node->set_code(str);
		codes[(int)node->get_char()] = str;
		//std::cout << "[" << (char)node->get_char() << "] = " << str << std::endl;
	}

}

std::string message_to_code(std::string filename, const std::vector<std::string> & codes)
{
	std::string message{ "" };
	std::ifstream ifs(filename, std::ifstream::binary);
	if (!ifs) {
		std::cerr << "Error in [" << __func__ << "]: " << strerror(errno);
	}
	char ch;
	while (true) {
		ifs.read(&ch, 1);
		if (ifs.eof())
			break;
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
	std::vector<int> frequency(255, 0);
	std::string filename = "text.txt";
	std::string filename_write = "text_out.txt";
	read_frequency(filename, frequency);

	/*unsigned char ch = 0;
	auto print_frequency = [&ch](const int& value) {
		if (value != 0)
			std::cout << "[" << ch << "] = " << value << std::endl;
		ch++;
	};

	std::for_each(frequency.begin(), frequency.end(), print_frequency);
	*/
	queue_t queue;
	make_queue(queue, frequency);
	Node::node_ptr root = queue.top();
	std::vector<std::string> codes{ 255,"" };
	make_codes(root, "", codes);

	std::string message = message_to_code(filename, codes);
	write_to_file(filename_write, message, codes, frequency);

	while (!queue.empty())
	{
		//std::cout << *(queue.top()) << std::endl;
		queue.pop();
	}
}

