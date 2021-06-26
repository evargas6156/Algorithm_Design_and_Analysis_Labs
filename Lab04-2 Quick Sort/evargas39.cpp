#include <iostream>

using namespace std;

//function to print out contents of an array ; separated 
void printArr(int* list, int size){
	for(int i = 0; i < size; i++){
		cout<<list[i]<<";";
		if(i == (size - 1)){
			//cout<<endl;		
		}
	}
}

//a function to swap array elements at index a and b 
void swap(int* arr, int a, int b){
	int temp; 
	temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

//a function that partitions an array non-randomly using the last index
int normPartition(int* sequence, int startIndex, int endIndex){
	//get the value at the end of the array
	int endVal = sequence[endIndex];
	
	//create variable to store partition index
	int i = startIndex - 1;
	
	//for each value less than the end value, swap it with i and j
	for(int j = startIndex; j < endIndex; j++){
		if(sequence[j] <= endVal){
			i++;
			swap(sequence, i, j);
		}
		
	}
	//swap the final value to the position where everything less than is on left
	swap(sequence, (i + 1), endIndex);
	//return final position of pivot value 
	return (i + 1);
}

//function to partition an array randomly
int randomPartition(int* sequence, int startIndex, int endIndex){
	//select random index within the range of the array bounds
	int i = (rand() % ((endIndex - startIndex) + 1) + startIndex);
	
	//swap the element at the random index with the last index element
	swap(sequence, i, endIndex);
	
	//run normal parition now that the random element is at the end of the array
	int temp = normPartition(sequence, startIndex, endIndex);
	return temp;
}

//sorts input array using random quicksort method
void randQuickSort(int* sequence, int start, int end){
	//if the size of the array isnt 1, partition and run quicksort on left and 
	//right side of parition
	if (start < end){
		//find partition randomly
		int pivot = randomPartition(sequence, start, end);
		
		//run quicksort for left side of pivot 
		randQuickSort(sequence, start, (pivot - 1));
		
		//run quicksort for right side of pivot 
		randQuickSort(sequence, (pivot + 1), end);
	}
	
}




int main(int argc, char **argv){

	int* list;
	int size;

	//get size of the array 
	cin >> size;
	list = new int[size];

	//get numbers to sort
	for(int i = 0; i < size; i++){
		cin >> list[i];
	}
	
	//create variables for quicksort
	int start = 0;
	int end = size - 1;
	
	//sort list using quicksort
	randQuickSort(list, start, end);

	//print sorted list
	printArr(list, size);
}