#include <iostream>

using namespace std;

//a function to print an array separated by ;
void printArr(int* sequence, int size){
	for(int i = 0; i < size; i++){
		cout<<sequence[i]<<";";
	}
}


void merge(int* sequence, int start, int middle, int end){

	// determine sizes for left and right arrays
	int sizeLeft, sizeRight;
	sizeLeft = middle - start + 1;
	sizeRight= end - middle;

	//declare and initialize left and right arrays with an extra length than that determined above 
	int* left;
	int* right;
	left = new int[(sizeLeft + 1)]; 
	right = new int[(sizeRight + 1)];

	//set last index of arrays to maximum possible integer, to signal the end of the array
	left[sizeLeft] = 2147483647;
	right[sizeRight] = 2147483647;

	//populate left and right arrays with corresponding values
	for(int i = 0; i < sizeLeft; i++){
		left[i] = sequence[start + i];   
	}
	for(int j = 0; j < sizeRight; j++){
		right[j] = sequence[middle + j + 1];     
	}

	
	//place left and right values back into the sequence in sorted order
	int l = 0;
	int r = 0;
	for(int k = start; k < (end + 1); k++){
		if(left[l] <= right[r]){
			sequence[k] = left[l];
			l = l + 1;
		}
		else {
			sequence[k] = right[r];
			r = r + 1;	
		}
	}
	

	//delete left and right arrays to prevent memory leaks
	delete [] left;
	delete [] right;

}


void mergeSort(int* sequence, int start, int end){
	//only execute if statement if size is greater than 1 
	if(start < end){
		//determine where to cut array in two 
		int middle = (start + end)/2;
		

		//apply merge sort again on the left and right subarrays
		mergeSort(sequence, start, middle);
		mergeSort(sequence, (middle + 1), end);

		//merge results together in sorted order 
		merge(sequence, start, middle, end);
	}

}



int main(int argc, char **argv){

	int* list;
	int size;
	
	//get number of elements to be sorted 
	cin >> 	size;
	list = new int[size];

	//get elements to be sorted 
	for(int i = 0; i < size; i++){
		cin >> list[i];
	}


	//create variables needed for merge sort
	int start, end; 
	start = 0;
	end = size - 1;
	
	//run merge sort on the sequence
	mergeSort(list, start, end);

	//print the sorted sequence 
	printArr(list, size);


}





