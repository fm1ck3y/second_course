#include <iostream>
#include <cstring>
#include <chrono> 
#include <fstream>

using namespace std;
using namespace std::chrono; 

static int CountComparison = 0; // количество операций сравнения
static int CountPermutation = 0; // количество операций перестановки элементов массива
ofstream output("output.txt"); // файл для вывода итога исследования функций

// простой вывод массива
void PrintArray(int* array, int length)
{
   for (int i = 0 ; i < length; i++){
      output << array[i] << "\t";
   }
   output << endl;
}

// сортировка выборкой
int* SelectionSort(int* arr, int length)
{
   int* array = new int[length]; 
   memcpy(array,arr,length * sizeof(int)); // создание копии массива
   for (int i = 0; i < length; i++)
   {
      int index = i; int min = array[i];
      for (int j = i ; j < length; j++)
      {
         CountComparison++;
	      if (array[j] < min)
         {
	         index = j; 
            min = array[j];
	      }
      }
      CountPermutation++;
      swap(array[i],array[index]);
   }
   output << "Sorting array by SelectionSort." << endl;
   return array;
}

// сортировка вставками
int* InsertionSort(int* arr, int length)
{
   int* array = new int[length];
   memcpy(array,arr,length * sizeof(int));
   for (int i = 1 ; i < length; i++)
   {
      int temp_i = i;
      CountComparison++;
      while (temp_i > 0 && array[temp_i] < array[temp_i-1]){
         CountComparison++;
         CountPermutation++;
         swap(array[temp_i-1],array[temp_i]);
	      temp_i--;
      }
   }

   output << "Sorting array by InstertionSort." << endl;
   return array;
}

// сортировка пузырьком
int* BubbleSort(int* arr, int length)
{
   int* array = new int[length];
   memcpy(array,arr,length * sizeof(int));
   for (int i = 0 ; i < length-1; i++)
   {
      for (int j = 0 ; j < length-i-1; j++)
	   {
         CountComparison++;
	      if (array[j] > array[j+1])
	      {
            CountPermutation++;
            swap(array[j],array[j+1]);
         }
	   }
   }
   
   output << "Sorting array by BubbleSort." << endl;
   return array;
}

// сортировка Шелла
int* ShellSort(int* arr, int length){
   int* array = new int[length];
   memcpy(array,arr,length * sizeof(int));
   int* h = new int [3] {5,2,1}; // длина шагов
   for (int i = 0 ; i < 3; i++)
   {
      for(int m = 0; m < h[i]; m++)
      {
         for (int j = m; j < length; j+=h[i])
         {
            int min = array[j]; int index = j;
            for (int k = j+h[i]; k < length; k+=h[i]){
               CountComparison++;
               if (array[k] < min){
                  min = array[k];
                  index = k;
               }
            }
            CountPermutation++;
            array[index] = array[j];
            array[j] = min;
         }
      }
   }
   output << "Sorting array by ShellSort." << endl;
   return array;
}

// сортировка бинарными вставками
int* BinaryInstertionSort(int* arr, int length)
{
   int* array = new int[length];
   memcpy(array,arr,length * sizeof(int));
   for (int i = 1 ; i < length; i++)
   {
      // бинарный поиск 
      int key = array[i]; 
      int l = 0; int r = i; 
      while(l < r){
         int mid = l + (r - l) /2;
         CountComparison++;
         if (key < array[mid])
            r = mid;
         else
            l = mid +1;
      }
      for (int j = i ; j >= l+1; j--){
         CountPermutation++;
         array[j] = array[j-1];
      }
      array[l] = key;
   }
   output << "Sorting array by BinaryInstertionSort." << endl;
   return array;
}

// Шейкер сортировка
int* ShakerSort(int* arr, int length)
{
   int* array = new int[length];
   memcpy(array,arr,length * sizeof(int));
   int l = 0; int r = length-1; // левая и правая граница
   bool permutation = true; // переменная для проверки наличия операции перестановки за проход
   while (l < r && permutation) 
   {
      permutation = false;
      for(int i = l; i < r; i ++)
      {
         CountComparison++;
         if (array[i] > array[i+1])
         {
            CountPermutation++;
            swap(array[i],array[i+1]);
            permutation = true;
         }
      }
      r--;
      for (int i = r; i >= l; i--)
      {
         CountComparison++;
         if (array[i] > array[i+1])
         {
            CountPermutation++;
            swap(array[i],array[i+1]);
            permutation = true;
         }
      }
      l++;
   }
   output << "Sorting array by ShakerSort." << endl;
   return array;
}

// функция исследования функций сортировки
// в качестве первого параметра передаётся функция, которая будет сортировать алгоритм
void FunctionStudy (int* (*function)(int* arr, int length) ,int* array,int length_array)
{
   auto start = high_resolution_clock::now(); // начало выполнения функции (время)
   int* sort_array = function(array,length_array); 
   auto stop = high_resolution_clock::now(); // конец выполнения функции (время)
   PrintArray(sort_array,length_array);
   auto duration = duration_cast<microseconds>(stop - start); 
   output << "Time taken function:\t" << duration.count() << " microsecond" << endl;
   output << "Comprasion count in function:\t" << CountComparison << endl;
   output << "Permutation count in function:\t" << CountPermutation << endl << endl;
   CountComparison = 0;
   CountPermutation = 0;
   delete[] sort_array; // очистка памяти от сортированного масива
}

int main()
{
   const int length = 15; // длина массива (неизменная)
   
   // идет генерация массивов и вызова для них разных способов сортировки
   // первый массив - рандомный, второй массив упорядоченный возрастанием, третий убыванием

   output << "------------------------random array------------------------------------" << endl;
   int* array = new int[length];
   for (int i = 0 ; i < length; i++)
      array[i] = rand() % 1000;
   output << "Default array" << endl;
   PrintArray(array,length);
   output << endl;
   FunctionStudy(SelectionSort,array,length);
   FunctionStudy(InsertionSort,array,length);
   FunctionStudy(BubbleSort,array,length);\
   FunctionStudy(ShellSort,array,length);
   FunctionStudy(BinaryInstertionSort,array,length);
   FunctionStudy(ShakerSort,array,length);
   // -------------------------------------------------------------------
   output << "------------------------increasing array------------------------------------" << endl;
   array = new int[length];
   for (int i = 0 ; i < length; i++)
      array[i] = i*2; 
   output << "Default array" << endl;
   PrintArray(array,length);
   output << endl;
   FunctionStudy(SelectionSort,array,length);
   FunctionStudy(InsertionSort,array,length);
   FunctionStudy(BubbleSort,array,length);
   FunctionStudy(ShellSort,array,length);
   FunctionStudy(BinaryInstertionSort,array,length);
   FunctionStudy(ShakerSort,array,length);
   // -------------------------------------------------------------------
   output << "------------------------decreasing array------------------------------------" << endl;
   array = new int[length];
   for (int i = 0 ; i < length; i++)
      array[i] = i*-2; 
   output << "Default array" << endl;
   PrintArray(array,length);
   output << endl;
   FunctionStudy(SelectionSort,array,length);
   FunctionStudy(InsertionSort,array,length);
   FunctionStudy(BubbleSort,array,length);
   FunctionStudy(ShellSort,array,length);
   FunctionStudy(BinaryInstertionSort,array,length);
   FunctionStudy(ShakerSort,array,length);
   // -------------------------------------------------------------------
   output.close();
   delete[] array;
   return 1;
}
