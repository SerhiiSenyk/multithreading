//13.	Створити масив N елементів.В окремому потоці виконати лінійний пошук заданого елемента.
//Елементи масиву згенерувати випадковим чином за допомогою вбудованих функцій
//Завдання.
//1.	Реалізувати заданий алгоритм в окремому потоці.
//2.	Виконати розпаралелювання заданого алгоритму на 2, 4, 8 потоків.
//3.	Реалізувати можливість зміни пріоритету певного потоку.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <time.h>
#define _RAND_MAX_ 10
using namespace std;
typedef unsigned int uint;
void randArray(int *array, const uint size_of_array);
void displayArray(int *array, const uint size_of_array);
DWORD WINAPI functionThread(LPVOID lpParam);
struct Sparametrs{
	uint leftIndex;
	uint rightIndex;
	int iKey;
	int *Index;//Якщо -1 то не знайдено
};
//Thread *arrayThreades = NULL; 
HANDLE *handles = NULL;
int *mas = NULL;
uint *size_of_array = NULL;
int main()
{	
	uint size = 100;
	size_of_array = &size;
	mas = new int[*size_of_array];
	randArray(mas,*size_of_array);
	uint Threads;
	int key;
	cout << "Enter number thread : ";
	cin >> Threads;
	cout << "Enter key : ";
	cin >> key;
	Sparametrs *param = new Sparametrs[Threads];
	displayArray(mas, *size_of_array);
	uint lenghtSegment = *size_of_array / Threads;
	handles = new HANDLE[Threads];
	DWORD *IDs = new DWORD[Threads];
	for (int i = 0; i < Threads; ++i) {
		param[i].leftIndex = i*lenghtSegment;
		param[i].rightIndex = param[i].leftIndex + lenghtSegment;
		param[i].iKey = key;
		handles[i] = CreateThread(NULL, 0, functionThread, param + i, 0, &IDs[i]);
	}
	for (int i = 0; i < Threads; ++i)
		cout << (param[i].Index) << endl;;
	
	delete[] mas;
	delete[] param;
	system("Pause");
	return 0;
}
void randArray(int *array, const uint size_of_array)
{
	srand(time(0));
	for (int i = 0; i < size_of_array; ++i) {
		array[i] = rand() % _RAND_MAX_;
	}
	return;
}

void displayArray(int *array, const uint size_of_array)
{
	for (int i = 0; i < size_of_array; ++i){
		cout << array[i] << "\t";
    }
	cout << endl;
	return;
}

DWORD WINAPI functionThread(LPVOID lpParam)
{
	Sparametrs param = (*(Sparametrs*)lpParam);
	
	return 0;
}

int linearSearch(int iKey, const uint left,const uint right)
{
	for (int i = left; i < right; ++i)
	{
		if (iKey == mas[i])
			return i;
	}
	return -1;
}

//clock_t t1;
//t1 = clock();
//cout << linearSearch(10, array, ) << endl;
//t1 = clock() - t1;
//printf("Time = %lf seconds\n", ((double)t1) / CLOCKS_PER_SEC);
