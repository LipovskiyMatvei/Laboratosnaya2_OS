#include <vector>
#include <iostream>
#include <windows.h>
#include "struct.h"
using namespace std;

void min_max_sync(Data* data) {
	if (data->size == 0) return;

	data->min = data->arr[0];
	data->max = data->arr[0];

	for (int i = 0; i < data->size; i++) {
		if (data->arr[i] > data->max) data->max = data->arr[i];
		if (data->arr[i] < data->min) data->min = data->arr[i];
	}
}


void average_sync(Data* data) {
	if (data->size == 0) {
		data->average = 0;
		return;
	}

	double sum = 0;
	for (int i = 0; i < data->size; i++) {
		sum += data->arr[i];
	}
	data->average = sum / data->size;
}


void runSimpleTests() {
	cout << "Running Simple Tests" << endl;

	
	int test1[] = { 1, 2, 3, 4, 5 };
	Data data1 = { test1, 5, 0, 0, 0 };

	min_max_sync(&data1);
	average_sync(&data1);

	if (data1.min == 1 && data1.max == 5 && data1.average == 3.0) {
		cout << "Test 1 Passed" << endl;
	}
	else {
		cout << "Test 1 Fialed" << endl;
	}

	
	int test2[] = { -1, 0, 1 };
	Data data2 = { test2, 3, 0, 0, 0 };

	min_max_sync(&data2);
	average_sync(&data2);

	if (data2.min == -1 && data2.max == 1 && data2.average == 0.0) {
		cout << "Test 2 Passed" << endl;
	}
	else {
		cout << "Test 2 Failed" << endl;
	}

	
	int test3[] = { 5 };
	Data data3 = { test3, 1, 0, 0, 0 };

	min_max_sync(&data3);
	average_sync(&data3);

	if (data3.min == 5 && data3.max == 5 && data3.average == 5.0) {
		cout << "Test 3 Passed" << endl;
	}
	else {
		cout << "Test 3 Failed" << endl;
	}
}


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
 

	runSimpleTests();

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

