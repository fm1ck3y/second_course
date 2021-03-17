#include <iostream>

// функция сравнения на минимальный элемент
template <typename T>
T Min(T el1, T el2)
{
	if (el1 < el2)
		return el1;
	return el2;
}

// функция расчета минимального колечство операции
int* Solve(const int N, int *Op)
{
	Op = new int[N];
	Op[0] = 0;
	for (int i = 1; i <= N; i++)
	{
		Op[i] = Op[i - 1] + 1; 
		for (int j = 2; j <= i - 1; j++)
		{
			Op[i] = Min(Op[i],Op[j] + Op[i - j] + 1);
//            Если это было умножение, тогда сомножителями являются
//            натуральные степени числа k, которые в сумме дают n.
//          // Если последней операцией являлось возведение в степень, то
			if (i % j == 0) 
				Op[i] = Min(Op[i],Op[i / j] + j - 1);
		}
	}
	return Op;
}

int main()
{
	const int N = 15;
	int* Op = new int[N];
	Op = Solve(N,Op);
	for (int i = 1; i < N; i++)
	{
		std::cout << "i = " << i+1 << " >> " << Op[i] << std::endl;
	}
	return 0;
}
