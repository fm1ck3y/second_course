#include <iostream>
#include <cstring>
#include <chrono> 

using namespace std;
using namespace std::chrono; 

static int CountComparison = 0; // количество операций сравнения
static int CountPermutation = 0; // количество операций перестановки элементов массива

// простой вывод массива
void PrintArray(int* array, int length)
{
   for (int i = 0 ; i < length; i++){
      cout << array[i] << "\t";
   }
   cout << endl;
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
      int tmp = array[index];
      array[index] = array[i];
      array[i] = tmp;
   }
   cout << "Sorting array by SelectionSort." << endl;
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
	      int tmp = array[temp_i];
	      array[temp_i] = array[temp_i-1];
	      array[temp_i-1] = tmp;
	      temp_i--;
      }
   }

   cout << "Sorting array by InstertionSort." << endl;
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
	         int tmp = array[j];
	         array[j] = array[j+1];
            array[j+1] = tmp;	       
         }
	   }
   }
   
   cout << "Sorting array by BubbleSort." << endl;
   return array;
}

int* ShellSort(int* arr, int length){
   int* array = new int[length];
   memcpy(array,arr,length * sizeof(int));
   int* h = new int [3] {5,2,1};
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
   cout << "Sorting array by ShellSort." << endl;
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
   cout << "Time taken function:\t" << duration.count() << " microsecond" << endl;
   cout << "Comprasion count in function:\t" << CountComparison << endl;
   cout << "Permutation count in function:\t" << CountPermutation << endl << endl;
   CountComparison = 0;
   CountPermutation = 0;
   delete[] sort_array; // очистка памяти от сортированного масива
}

int main()
{
   const int length = 15; // длина массива (неизменная)
   
   //------------------------ random array ------------------------------
   int* array = new int[length];
   for (int i = 0 ; i < length; i++)
      array[i] = rand() % 1000;
   cout << "Default array" << endl;
   PrintArray(array,length);
   cout << endl;
   FunctionStudy(SelectionSort,array,length);
   FunctionStudy(InsertionSort,array,length);
   FunctionStudy(BubbleSort,array,length);\
   FunctionStudy(ShellSort,array,length);
   // -------------------------------------------------------------------

   //------------------------ increasing array --------------------------
   array = new int[length];
   for (int i = 0 ; i < length; i++)
      array[i] = i*2; 
   cout << "Default array" << endl;
   PrintArray(array,length);
   cout << endl;
   FunctionStudy(SelectionSort,array,length);
   FunctionStudy(InsertionSort,array,length);
   FunctionStudy(BubbleSort,array,length);
   FunctionStudy(ShellSort,array,length);
   // -------------------------------------------------------------------

   //------------------------ decreasing array --------------------------
   array = new int[length];
   for (int i = 0 ; i < length; i++)
      array[i] = i*-2; 
   cout << "Default array" << endl;
   PrintArray(array,length);
   cout << endl;
   FunctionStudy(SelectionSort,array,length);
   FunctionStudy(InsertionSort,array,length);
   FunctionStudy(BubbleSort,array,length);
   FunctionStudy(ShellSort,array,length);
   // -------------------------------------------------------------------
   delete[] array;
   return 1;
}
