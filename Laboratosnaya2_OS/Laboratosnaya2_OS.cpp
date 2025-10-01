#include <vector>
#include <iostream>
#include <windows.h>
#include "struct.h"
using namespace std;


void enterArr(int* array, int n) {

	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		array[i] = k;
	}
	cout << endl;

}


void printArr(int *array, int size) {


	
	for (int i = 0; i < size; i++) {

		cout << array[i] << " ";
	}


	cout << endl;
}



DWORD WINAPI min_max(LPVOID iNum) {
	Data* data = (Data*)iNum;

	data->min = data->arr[0];
	data->max = data->arr[0];


	for (int i = 0; i < data->size; i++) {

		if (data->arr[i] >= data->max) data->max = data->arr[i];
		Sleep(7);

		if (data->arr[i] <= data->min) data->min = data->arr[i];
		Sleep(7);


	}


	cout << "Min: " << data->min << ", Max: " << data->max << endl;
	

	return 0;
}

DWORD WINAPI average(LPVOID iNum) {
	Data* data = (Data*)iNum;

	double sum = 0;

	for (int i = 0; i < data->size; i++) {

		sum += data->arr[i];
		Sleep(12);

	}
	data->average = sum / data->size;
	cout << "Average: " << data->average << endl;
	return 0;
}





int main(){
 

	int n;
	cout << "Enter size and numbers of array: ";
	cin >> n;
	int* array = new int[n];

	enterArr(array, n);

	printArr(array, n);




	Data data;          
	data.arr = array;    
	data.size = n;


	HANDLE hMinMax = CreateThread(NULL, 0, min_max, &data, 0, NULL);
	HANDLE hAverage = CreateThread(NULL, 0, average, &data, 0, NULL);


	WaitForSingleObject(hMinMax, INFINITE);
	WaitForSingleObject(hAverage, INFINITE);



	

	CloseHandle(hMinMax);
	CloseHandle(hAverage);




	
	for (int i = 0; i < n; i++) {
		if (array[i] == data.min || array[i] == data.max) {
			array[i] = data.average;
		}
	}

	
	cout << "Changed array: ";
	printArr(array, n);

	delete [] array;

}

