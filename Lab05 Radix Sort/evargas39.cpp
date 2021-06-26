#include <iostream>

using namespace std;

//function to print out contents of a 2D array ; separated 
void print2DArr(int** list, int num, int size){
	for(int i = 0; i < num; i++){
		for(int j = 0; j < size; j++){
			cout<<list[i][j]<<";";
			if(j == (size - 1)){
			cout<<endl;	
			}
		}
	}
}

void printArr(int* list, int size){
	for(int i = 0; i < size; i++){
		cout<<list[i]<<";";
		if(i == (size - 1)){
			cout<<endl;		
		}
	}
}


//countingSort modified to sort vectors by their ith digit 
int** countingSort(int** vectors, int digit, int numVectors, int k){
	//declare new variables for counting and the solution
	int* c = new int[k];
	int** answer = new int*[numVectors];
	
	//initialize counting array to zero
	for(int i = 0; i < k; i ++){
		c[i] = 0;
	}
	
	//count the number of elements that match the value of the counting array index
	for(int i = 0; i < numVectors; i++){
		c[(vectors[i][digit])]++;
		answer[i] = new int[10];
	}
	
	//add the counting array so that c[i] contains number of elements <= i
	for(int i = 1; i < k; i++){
		c[i] = c[i] + c[i - 1];
	}

	//move the ith vector into its correct spot based on the counting array
	for(int i = (numVectors - 1); i >= 0; i--){
		answer[c[vectors[i][digit]] - 1] = vectors[i];
		c[(vectors[i][digit])]--;
	}
	
	return answer;
}

int** radixSort(int** vectors, int numDigits, int numVectors, int max){
	int k = max + 1;
	int** answer;
	//run countingSort on each digit of the vectors
	for(int i = (numDigits - 1); i >= 0; i--){
		answer = countingSort(vectors, i, numVectors, k);
		vectors = answer;
	}
	return answer;
}

int main(int argc, char **argv){

	int** vectors;
	int numVec;
	int const vecSize = 10;
	int maxNum = -2147483648;

	//get the numer of vectors to sort 
	cin >> numVec;
	
	//initialize vector of pointers 
	vectors = new int*[numVec];

	//get numbers to sort and find the max number entered 
	for(int i = 0; i < numVec; i++){
		//initialize vector of ints that makes up the rows
		vectors[i] = new int[vecSize];
		for(int j = 0; j < vecSize; j++){
			cin >> vectors[i][j];
			if(vectors[i][j] > maxNum){
				maxNum = vectors[i][j];
			}
		}
	}
	
	//sort vectors using radix sort, assuming all elements are positive
	vectors = radixSort(vectors, vecSize, numVec, maxNum);
	
	//print sorted vectors 
	print2DArr(vectors, numVec, vecSize);
	
}