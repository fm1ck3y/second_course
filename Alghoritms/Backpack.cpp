#include <iostream>
#include <vector>
#include <malloc.h>

#pragma warning(disable:6386)
#pragma warning(disable:6011)
#pragma warning(disable:6385)

template <typename T>
T Max(T el1, T el2)
{
	if (el1 > el2)
		return el1;
	return el2;
}

void findAns(int i, int j, std::vector<std::pair<int, int>> &ans, int** array, std::vector<std::pair<int, int>> &items)
{
	if (array[i][j] == 0 || i < 0 || j < 0)
		return;
	if (array[i - 1][j] == array[i][j])
		findAns(i - 1, j, ans, array,items);
	else {
		findAns(i - 1, j - items[i-1].first,ans,array,items);
		ans.push_back(items[i-1]);
	}
}

void print_array(int** array, int N, int M)
{
	std::cout << '\t';
	for (size_t i = 0; i < M; i++)
		std::cout << i << '\t';
	std::cout << std::endl;
	for (size_t i = 0; i < N; i++)
	{
		std::cout << i << '\t';
		for (size_t j = 0; j < M; j++)
		{
			std::cout << array[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::vector<std::pair<int, int>> items; // pair<вес,ценность>
	int N = 5+1; // количество предметов +1
	items.push_back(std::make_pair(3, 1));
	items.push_back(std::make_pair(4, 6));
	items.push_back(std::make_pair(5, 4));
	items.push_back(std::make_pair(8, 7));
	items.push_back(std::make_pair(9, 6));
	const int W = 13; // вместимость

	int** array = (int**)malloc(N * sizeof(int*));
	for (size_t i = 0; i < N; i++)
		array[i] = (int*)malloc(W * sizeof(int));

	for (size_t i = 0; i < W; i++)
		array[0][i] = 0;
	for (size_t i = 0; i < N; i++)
		array[i][0] = 0;

	for (size_t i = 1; i < N; i++)
		for (size_t j = 1; j < W; j++)
			if (j >= items[i-1].first)
				array[i][j] = Max(array[i - 1][j], array[i - 1][j - items[i-1].first] + items[i-1].second);
			else
				array[i][j] = array[i - 1][j];
	
	print_array(array, N, W);

	std::vector<std::pair<int, int>> ans;
	findAns(N - 1, W - 1, ans, array, items);
	std::cout << "Предметы которые надо положить в рюкзак: " << std::endl;
	for (auto item : ans)
		std::cout << "Вес = " << item.first << ", Ценность = " << item.second << std::endl;

	for (size_t i = 0; i < N; i++)
		free(array[i]);
	free(array);
}