#include <iostream>

using namespace std;

//function to print out contents of an array ; separated 
void printArr(int* list, int size){
	for(int i = 0; i < size; i++){
		cout<<list[i]<<";";
		if(i == (size - 1)){
			cout<<endl;		
		}
	}
}


void insertionSort(int* list, int length){
	//outer loop iterates through unsorted elements 
	for(int j = 1; j < length; j++){
		int curr = list[j];
		int i = j - 1;
		//inner while loop finds correct place to insert current
		//element into the sorted subarray
		while(i > -1 && list[i] > curr){
			list[i + 1] = list[i];
			i = i-1;
		}
		list[i + 1] = curr;
		//call to print the contents of the sorted subarray
		printArr(list, j + 1);
	}

}


int main(int argc, char **argv){

	int* unsortedList;
	int size;

	//get size of the array 
	cin >> size;
	unsortedList = new int[size];

	//get numbers to sort
	for(int i = 0; i < size; i++){
		cin >> unsortedList[i];
	}
	
	insertionSort(unsortedList, size);

}