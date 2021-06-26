#include <iostream>

using namespace std;



int crossMaxSubArray(int* list, int low, int mid, int high){
	int leftSum, rightSum, sum;
	sum = 0;
	leftSum = -2147483648;
	//find max sum from left side of midpoint
	for(int i = mid; i >= 0; i--){
		sum = sum + list[i];
		if(sum > leftSum){
			leftSum = sum;
		}
	}
	rightSum = -2147483648;
	sum = 0;
	//find max sum from right side of midpoint
	for(int i = (mid + 1); i <= high; i++){
		sum = sum + list[i];
		if(sum > rightSum){
			rightSum = sum; 
		}	
	}
	//return left and right midpoint added together for the 
	//total cross Subarray sum	
	return (rightSum + leftSum);	

}


int maxSubArray(int* list, int low, int high){
	//base case: if list size is 1, return value of the list 
	if(low == high){
		return list[low];
	}
	else{
		//calculate midpoint
		int mid = (low + high) / 2;

		int leftSum, rightSum, crossSum;

		//run max subArray on left and right sub arrays
		leftSum = maxSubArray(list, low, mid);
		rightSum = maxSubArray(list, (mid + 1), high);

		//calculate sum of max cross subArray
		crossSum = crossMaxSubArray(list, low, mid, high);

		//return max sum from left right and cross 
		if(leftSum >= rightSum && leftSum >= crossSum){
			return leftSum;
		}else if(rightSum >= leftSum && rightSum >= crossSum){
			return rightSum;
		}else{
			return crossSum;
		}
	}	

}

int main(int argc, char **argv){

	int* sequence;
	int size;

	//get size of the array 
	cin >> size;
	sequence = new int[size];

	//get numbers to sort
	for(int i = 0; i < size; i++){
		cin >> sequence[i];
	}
	
	//create variables for maxSubArray
	int low = 0;
	int high = size - 1;
	int maxSubArraySum;
	
	//get max subArray sum and print
	maxSubArraySum = maxSubArray(sequence, low, high);
	cout<<maxSubArraySum;

}