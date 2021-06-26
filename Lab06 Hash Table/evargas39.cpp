#include <iostream>

using namespace std;


void output();
void InsertKey();
void deleteKey();

//Node structure for linked list nodes usd for chaining collisions
struct Node {
	//member for storing data
	int data;
	//member for storing pointer to next node
	Node* next;

	//constructor for building a node with a number stored 
	Node(int num){
		data = num;
		next = NULL;
	}
	
};

//structure for hashtable, stores size of table as well
struct HashTable{
	//member for storing size of table
	int size;
	//member for storing array of linked lists, which makes up the hash function
	Node** table;
	
	//construtor for building a hash table of size num
	HashTable(int num){
		size = num;
		table = new Node*[num];
		for(int i = 0; i < num; i++){
			//initialize each index to NULL
			table[i] = NULL;
		}
	}
};

int searchKey(HashTable* hashTable, int key, bool output);

//hash function using function h(k) = k mod m, returns corresponding hash index.
int hashFunct(HashTable* table, int key){
	int index = key % table->size;
	return index;
}

//a function to output the table 
void output(HashTable* hashTable){
	
	Node* temp;
	//iterate over every table index and print out the linked lists
	for(int i = 0; i < hashTable->size; i++){
		cout<<i<<":";
		temp = hashTable->table[i];
		//iterates through each linked list until the end, printing the data 
		while(temp != NULL){
			cout<<temp->data<<"->";
			temp = temp->next;
		}
		cout<<";"<<endl;
	}

}

//a function to insert a key into the table 
void insertKey(HashTable* hashTable, int key){
	
	//get the table index to look in using the hash function
	int index = hashFunct(hashTable, key);
	
	//if the index is null then simply add a node to it
	if(hashTable->table[index] == NULL){
		hashTable->table[index] = new Node(key);
	}
	//if the index has a collision, insert the new node at the start of the list 
	else{
		Node* temp = hashTable->table[index];
		hashTable->table[index] = new Node(key);
		hashTable->table[index]->next = temp;
	}
	
}

//a function to delete a key from the table 
void deleteKey(HashTable* hashTable, Node** current, int key){
	
	//get hash function and list index to determine if the key to be deleted exists
	int hashIndex = hashFunct(hashTable, key);
	int listIndex = searchKey(hashTable, key, false);
	Node* temp;
	
	//if the key does not exist in the list, print delete failed
	if(listIndex < 0){
		cout<<key<<":DELETE_FAILED;"<<endl;
	}
	//if the current node holds the desired key, then delete it by making its pointer point to the next node
	else if((*current)->data == key){
		*current = (*current)->next;
		cout<<key<<":DELETED;"<<endl;
	}
	//if the key is not at the current node then call deleteKey again with the node pointer increented to the next 
	else{
		deleteKey(hashTable, &((*current)->next), key);
	}

}

//a function to search for a given key in the table 
int searchKey(HashTable* hashTable, int key, bool output){
	
	int hashIndex, listIndex, i;
	Node* temp;
	i = 0;
	
	//get the hash index from the hash function
	hashIndex = hashFunct(hashTable, key);
	
	//set listIndex negative, indicating it isnt found yet.
	listIndex = -1;
	
	//set temp to the first node of the hash index
	temp = hashTable->table[hashIndex];
	
	//iterate through the list to find the key and its index
	while(temp != NULL){
		if(temp->data == key){
			listIndex = i;
			break;
		}else{
			temp = temp->next;
			i++;
		}
	}
	
	//if output is selected output the result of the search 
	if(output){
		if(listIndex >= 0){
			cout<<key<<":FOUND_AT"<<hashIndex<<","<<listIndex<<";"<<endl;
		}else{
			cout<<key<<":NOT_FOUND;"<<endl;
		}
	}
	
	//return the list index at which the key was found, -1 if not found
	return listIndex;
	
}




int main(int argc, char **argv){

	char userFunction = 'o';
	int hashTableSize = 0;
	int userNumber = 0;
	
	//get hashtable size from user
	cin>>hashTableSize;
	
	//declare and initialize hashtable of given size
	HashTable* table = new HashTable(hashTableSize);
	
	while(userFunction != 'e'){
		
		//get desired char function code from user
		cin>>userFunction;
		
		switch(userFunction){
			//insert case 
			case 'i': 
				//get key to insert 
				cin>>userNumber;
				insertKey(table, userNumber);
				break;
				
			//delete case
			case 'd': 
				//get key to delete 
				cin>>userNumber;
				deleteKey(table, &(table->table[hashFunct(table, userNumber)]),  userNumber);
				break;
				
			//search case
			case 's':
				//get key to search 
				cin>>userNumber;
				searchKey(table, userNumber, true);
				break;
			
			//output case
			case 'o':
				output(table);
				break;
				
			case 'e':
				break;
			
			default:
				cout<<"Invalid function key. Please enter a valid function key!"<<endl;
				break;
				
			
		}
			
	
	}
	
	
}