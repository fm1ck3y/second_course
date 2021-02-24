#include <iostream>
#include <fstream>
#define N  5


void read_matrix(int16_t A[N][N])
{
	std::ifstream f("matrix.txt");
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
			f >> A[i][j];
}

template <typename T>
T max(T el1, T el2)
{
	if (el1 > el2)
		return el1;
	return el2;
}


int main(void)
{
	int16_t(*A)[N] = new int16_t[N][N];
	int16_t(*D)[N] = new int16_t[N][N];
	read_matrix(A);
	for (size_t i = 0; i < N; i++)
	{ // зануление левого дополнительного
		D[i][0] = 0; // столбца матрицы
		for (size_t j = 1; j <= N; j++)
			D[i][j] = A[i][j - 1]; // копирование
	}
	for (size_t i = 1; i < N; i++)
		for (size_t j = 1; j <= N; j++)
			D[i][j] = D[i][j] + max(D[i - 1][j - 1], D[i - 1][j]);

	int16_t max = D[N - 1][0];
	for (size_t i = 0; i < N; i++)
		if (max < D[N - 1][i])
			max = D[N - 1][i];

	std::cout << "MAX = " << max << std::endl;
}
