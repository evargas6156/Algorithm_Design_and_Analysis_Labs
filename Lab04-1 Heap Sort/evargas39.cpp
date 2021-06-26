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

//a function that turns subtree rooted at current into a max heap
void maxHeapify(int* sequence, int current, int heapSize){
	int leftIndex, rightIndex, largest;
	
	//get left and right node index
	leftIndex = (2 * current) + 1;
	rightIndex =(2 * current) + 2;
	
	//find largest value of subtree
	if(leftIndex < heapSize && sequence[leftIndex] > sequence[current]){
		largest = leftIndex;
	}else{
		largest = current;
	}if(rightIndex < heapSize && sequence[rightIndex] > sequence[largest]){
		largest = rightIndex;
 	}
	//if the largest is not the subroot then swap and max heapify again 
	if(largest != current){
		swap(sequence, current, largest);
		printArr(sequence, heapSize);
		cout<<endl;
		maxHeapify(sequence, largest, heapSize);
		
	}


}


// a function to build a max heap
void buildMaxHeap(int* sequence, int size){
	int heapSize = size;
	//run max Heapify on the elements of the equence to make a max heap
	for(int i = ((size - 1)/2); i >= 0; i--){
		maxHeapify(sequence, i, heapSize);
		
	}

}

//sorts given sequence 
void heapSort(int* sequence, int size){
	int heapSize = size;
	buildMaxHeap(sequence, size);
	for(int i = (size - 1); i > 0; i--){
		swap(sequence, 0, i);
		heapSize--;
		maxHeapify(sequence, 0, heapSize);
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
	
	buildMaxHeap(list, size);
	//sort list using heapsort
	//heapSort(list, size);

	//print sorted list
    printArr(list, size);
}