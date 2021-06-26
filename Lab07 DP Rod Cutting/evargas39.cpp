#include <iostream>

using namespace std;


int* extendedBottomUpCutRod(int* p, int n, int** sDest){
	int* r = new int[n + 1];
	int* s = new int[n];
	//set the initial revenue to zero
	r[0] = 0;
	int q;
	
	for(int j = 1; j <= n; j++){
		q = -2147483648;
		for(int i = 0; i < j; i++){
			if(q < (p[i] + r[j - i - 1])){  
				q = p[i] + r[j - i - 1];   
				s[j - 1] = i + 1;
			}
		}
		
		r[j] = q; 
	}
	*sDest = s;
	return r;
}


void printCutRodSelection(int* p, int n){
	int* r; 
	int* s;
	int end = -1;
	
	//find the solutions using the bottom up approach
	r = extendedBottomUpCutRod(p, n, (&s));
	
	//print out the optimum r[n]
	cout<<r[n]<<endl;
	
	//output cuts while the rod length is still greater than 0
	while(n > 0){
		//print the current place to cut
		cout<<s[n - 1]<<" ";
		//decrease rod length by the current cut made 
		n = n - s[n - 1];
	}
	//print -1 when the solution is done printing
	cout<<end<<endl;
	
}



int main(int argc, char **argv){

	int* prices;
	int size;

	//get size of the array 
	cin >> size;
	prices = new int[size];

	//get numbers to sort
	for(int i = 0; i < size; i++){
		cin >> prices[i];
	}
	
	//run the print solution function which will find the solution and print it
	printCutRodSelection(prices, size);
	
}