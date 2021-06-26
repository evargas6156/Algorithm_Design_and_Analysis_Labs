#include <iostream>
#include <queue> 
#include <string>

using namespace std;

//a structure creating the nodes for the huffman tree 
struct Node {
	//member for storing frequency 
	int freq;
	
	//member for storing the string that frequency corresponds to
	std::string  string;
	
	//member for storing pointer to left and right nodes
	Node* left;
	Node* right;

	//constructor for building a node with a frequency  
	Node(int num, std::string currString){
		freq = num;
		right = NULL;
		left = NULL;
		string = currString;
	}
	
};

//a function object to create min priority queue of nodes with priority based on frequency member
class nodeComparison
{ 
public: 
    int operator() (Node* n1, Node* n2) 
    { 
		//check if frequeny of node 1 is greater than node 2
        return n1->freq >n2->freq; 
    } 
}; 

//a function to copy values from the temporary origin array to the results table named codes 
void copyToTable(int origin[], int*** codes, int row, int size){
	//for every value in the origin array save it in the corresponding space in codes 
	for(int i = 0; i < size - 1; i++){
		(*codes)[row][i] = origin[i];
	}
	//note the end of that row by saving -1, since all values are to be either 0 or 1
	(*codes)[row][size - 1] = -1;
}	

//a function to traverse the huffman tree and save the codes for each letter to the reults table, codes 
void getHuffCode(Node* tree, int code[], int curr, int*** codes){
	
	//if the left pointer is not null traverse it recursively, save 0 to the code array
	if(tree->left != NULL){
		code[curr] = 0;
		getHuffCode(tree->left, code, curr + 1, codes);
	}
	
	//if the right pointer is not null traverse it recursively, save 1 to the code array
	if(tree->right != NULL){
		code[curr] = 1;
		getHuffCode(tree->right, code, curr + 1, codes);
	}
	
	//if the node is a leaf node, save the temp code array to the codes table, since it is the code of a character 
	if( (tree->left == NULL) && (tree->right == NULL) ){
		*((*codes) + (tree->string[0] - 65)) = new int[curr + 1];
		copyToTable(code, codes, (tree->string[0] - 65), curr + 1);
	}
	
}

//a function to build and print the codes of a huffman tree 
void HuffmanTreeBuilder(int* freq, int numFreq){
	//create a new min priority queue and fill it with nodes with frequencies A-F
	priority_queue <Node*, vector<Node*>, nodeComparison> queue; 
	string temp = "A";
	for(int i = 0; i < numFreq; i++){
		temp[0] = (char)(65 + i);
		queue.push(new Node(freq[i], temp));
	}
	
	Node* x;
	Node* y;
	Node* z;
	int currFreq;
	string currString;
	for(int i = 0; i < (numFreq - 1); i++){
		//find two lowest values and store into x and y, remove those from the queue 
		x = queue.top();
		queue.pop();
		y = queue.top();
		queue.pop();
		
		//calculate frequency  and string of new node 
		currFreq = x->freq + y->freq;
		currString = x->string + y->string;
		
		//create new node z with currFreq and currString
		z = new Node(currFreq, currString);
		
		//set z left and right to x and y
		z->left = x;
		z->right = y;
		
		//add z to the queue 
		queue.push(z);
		
		
	}
	
	//create the temporary code array and the final code table 
	int tempCode[numFreq - 1];
	int** codes = new int*[numFreq];
	
	//traverse the tree andsave the codes to the table 
	getHuffCode(queue.top(), tempCode, 0, &codes);
	
	
	//print the codes for each letter in alphabetical order 
	int j;
	for(int i = 0; i < numFreq; i++){
		j = 0;
		cout<<(char)(i + 65)<<":";
		while(codes[i][j] != -1){
			cout<<codes[i][j];
			j++;
		}
		cout<<endl;
	}
	
	
}

int main(int argc, char **argv){

	int* frequencies;
	int const numFrequencies = 6;
	int** code;
	
	frequencies = new int[numFrequencies];

	//get the dimenions of the matrices 
	for(int i = 0; i < numFrequencies; i++){
		cin >> frequencies[i];
	}
	
	//create the Huffman Tree and print the codes 
    HuffmanTreeBuilder(frequencies, numFrequencies);
	
	
	
   
}

