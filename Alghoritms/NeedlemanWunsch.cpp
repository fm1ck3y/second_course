#include <iostream>
#include <malloc.h>

#pragma warning(disable:6386)
#pragma warning(disable:6011)
#pragma warning(disable:6385)

std::string read_word()
{
	std::string word;
	std::cout << "¬ведите первое слово >> ";
	std::cin >> word;
	return word;
}

template <typename T>
T Max(T el1, T el2)
{
	if (el1 > el2)
		return el1;
	return el2;
}

void print_array(int** array, int N, int M, std::string word_1, std::string word_2)
{
	std::cout << "\t\t";
	for (size_t i = 0; i < N; i++)
		std::cout << word_1[i] << '\t';
	std::cout << std::endl;
	for (size_t i = 0; i < N; i++)
	{
		if (i == 0) std::cout << '\t';
		else std::cout << word_2[i - 1] << '\t';
		for (size_t j = 0; j < M; j++)
		{
			std::cout << array[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	std::string word_1 = read_word();
	std::string word_2 = read_word();
	//std::string word_1 = "CCAGAGAC";
	//std::string word_2 = "CCAAGGCT";
	size_t N = word_1.length() + 1;
	size_t M = word_2.length() + 1;
	//std::string n_word_1 = word_1;
	//std::string n_word_2 = word_2;

	// allocate memory
	int** array = (int**)malloc(N * sizeof(int*));
	for (size_t i = 0; i < N; i++)
		array[i] = (int*)malloc(M * sizeof(int));

	// init array
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			array[i][j] = 0;

	for (size_t i = 0; i < N; i++)
		array[i][0] = i;
	for (size_t i = 0; i < M; i++)
		array[0][i] = i;


	for (size_t j = 1; j < M; j++)
	{
		for (size_t i = 1; i < N; i++)
		{
			int min = array[i - 1][j] + 1;
			if (array[i][j - 1] + 1 < min)
				min = array[i][j - 1] + 1;

			if (array[i - 1][j - 1] + (word_2[i - 1] != word_1[j - 1]) < min)
				min = array[i - 1][j - 1] + (word_2[i - 1] != word_1[j - 1]);
			array[i][j] = min;
		}
	}

	print_array(array, N, M, word_1, word_2);

	// free memory
	for (size_t i = 0; i < N; i++)
		free(array[i]);
	free(array);
}
