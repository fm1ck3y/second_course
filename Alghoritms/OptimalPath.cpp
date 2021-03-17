#include <iostream>
#include <fstream>
#define N  5

// функция чтения матрицы
void read_matrix(int16_t A[N][N])
{
	std::ifstream f("matrix.txt");
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
			f >> A[i][j];
}


// функция сравнения на минимальный элемент
template <typename T>
T min(T el1, T el2)
{
	if (el1 < el2)
		return el1;
	return el2;
}

int main(void)
{
    // основная матрица - A 
	int16_t(*A)[N] = new int16_t[N][N];
    // вспомогательная матрица D
	int16_t(*D)[N] = new int16_t[N][N];
	read_matrix(A);

    // производим копирование матрицы
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			D[i][j] = A[i][j];
		}
	}
    
    // формула для вычисления значений в вершинах 
	for (size_t i = 1; i < N; i++)
	{
		D[i - 1][i - 1] = min(D[i][i - 1] + A[i - 1][i - 1], D[i - 1][i] + A[i - 1][i]);
	}

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
			std::cout << D[i][j] << "\t";
		std::cout << std::endl;
	}
}
