#include <iostream>

using namespace std;
//helper functions used for testing/debugging 
void printArr(int* arr, int size){
	for(int i = 0; i < size; i++){
		cout<<arr[i]<<";";
	}
	cout<<endl;
}
void print2DArr(int** arr, int n, int m){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cout<<arr[i][j]<<";";
		}
		cout<<endl;
	}
	cout<<endl;
}


//a function to calculate m and s for matrux chain order and return it 
int** matrixChainOrder(int* p, int size, int*** sDest){
	int n = size - 1;
	int j, q;
	
	//make new table m[n][n] 
	int** m = new int*[n]; 
	for(int i = 0; i < n; i++){
		*(m + i) = new int[n];
	}
	
	//make new table s[n - 1][n - 1]
	int** s = new int*[n - 1];
	for(int i = 0; i < n - 1; i++){
		*(s + i) = new int[n - 1];
	}
	
	//initialize base cases to zero 
	for(int i = 0; i < n; i++){
		m[i][i] = 0;
	}
	
	//iterate through values of the tables and fill in using the recurrsion 
	for(int l = 1; l < n; l++){
		for(int i = 0; i < n - l; i++){ 
			j = i + l;
			m[i][j] = 2147483647;
			for(int k = i; k < j; k++){
				q = m[i][k] + m[k + 1][j] + (p[i] * p[k + 1] * p[j + 1]);
				if(q < m[i][j]){
					m[i][j] = q;
					s[i][j - 1] = k + 1;  
				}
			}
		}
	}
	
	//return s via pointer
	*sDest = s;
	
	//return m
	return m;
}

int count = 0;

void printOptimalParens(int** s, int i, int j){
	//if i and j are equal print current matrix
	if (i == j){
		cout<<"-"<<count<<"-"<<"A"<<(i - 1);
		count++;
	}else{
		//recursively find order of optimal multiplication
		cout<<"("; 
		printOptimalParens(s, i, s[i - 1][j - 2]);
		printOptimalParens(s, s[i - 1][j - 2] + 1, j);
		cout<<")";
	}
	
}

int main(int argc, char **argv){

	int* dims;
	int numMat;
	int numDims;
	int** m;
	int** s;

	//get number of matrices to multiply 
	cin >> numMat;
	
	//calculate number of dimensions to enter 
	numDims = numMat + 1;
	
	dims = new int[numDims];

	//get the dimenions of the matrices 
	for(int i = 0; i < numDims; i++){
		cin >> dims[i];
	}
	
	//find the optimal order 
	m = matrixChainOrder(dims, numDims, &s);
	
	//print optumum
	cout<<m[0][numMat - 1]<<endl;
	
	//print optimal order 
	printOptimalParens(s, 1, numMat);
	cout<<endl;
	
}


