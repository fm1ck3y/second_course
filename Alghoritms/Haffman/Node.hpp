#pragma once
#ifndef NODE_H
#define NODE_H
#include <iostream>

class Node
{
public:
	using node_ptr = std::shared_ptr<Node>;
	node_ptr left{ nullptr };
	node_ptr right{ nullptr };
	node_ptr parent{ nullptr };

	Node() = default;
	Node(unsigned char ch, int f) : ch(ch), frequency(f) {};
	Node(std::string& n, int f) : name(n), frequency(f) {};

	friend std::ostream& operator<<(std::ostream& os, const Node node);

	std::string get_code() const { return this->code; }
	int get_freq() const { return this->frequency; }
	std::string get_name() const {
		if (this->ch == 0)
			return this->name;
		if (this->ch == 10)
			return "\n";
		return std::string(1, static_cast<char>(this->ch));
	}
	unsigned char get_char() const { 
		return this->ch; 
	}
	void set_code(std::string code) {
		this->code = code;
	}

private:
	unsigned char ch{ 0 };
	std::string name{ "" };
	int frequency{ 0 };
	std::string code{ "" };
};

std::ostream& operator<<(std::ostream& os, const Node node)
{
	return os << "[" << node.get_name() << "] = " << node.get_freq() << "; [" << node.get_code() << "]";
}

#endif // !
