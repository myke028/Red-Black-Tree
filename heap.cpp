#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

/*
Code by Michael Yan, 2/21/2020
This code runs a heap algorithm where the user can choose to input a series of numbers
from a file or manually. The numbers will be used to construct a tree of numbers in
numerical order.
*/

void heapify(int heaparray[], int &heapsize, int current){ //wikipedia heapsort pseudo algorithm
    int parent = current; //node parent of child starts as equal to current index
    int left = 2 * current + 1; //left child of node is index * 2
    int right = 2 * current + 2; //right child of node is index * 2 + 1
	
    if(heaparray[left] > heaparray[parent] && left < heapsize){ //check if left child is larger than parent
        parent = left; //left is now the parent
	}
    if(heaparray[right] > heaparray[parent] && right < heapsize){ //check if right child is larger than the new parent
        parent = right;  //right is now the parent
	}
    // If largest is not root 
    if(parent != current){
        swap(heaparray[current], heaparray[parent]); //swap these two index values
  
        // Recursively heapify the affected sub-tree 
        heapify(heaparray, heapsize, parent); //recursion with parent as current index
    }
}



void buildHeap(int heaparray[], int &heapsize){ //construct the actual heap from array
    int startIndex = (heapsize/2)-1; //index of last node that has children
    for(int current = startIndex; current >= 0; current--){ //backwards iteration from startIndex
        heapify(heaparray, heapsize, current); //call heap algorithm
    }
}



void printHeap(int heaparray[], int &heapsize, int x, int current){ //print the heap
	
	//left and right index have been translated into +1 in order to manipulate, dont have to worry about zero
	
	int left = 2*current;
	int right = 2*current+1;
	if(right <= heapsize){
	  printHeap(heaparray, heapsize, x+1, right); //call recursively to get to the bottom rightmost node to print first
	}
	
	//now current is at the end of the end of the array because right is beyond the heap
	
	int actualindex = x; //keep track of the true array index
	
	while (x > 0){
	  cout << "   "; //space for formatting
	  x--;
	}
	
	cout << heaparray[current-1] << endl; //print the element out
	//cout << heaparray[actualindex] << endl;
	
	if (left <= heapsize){
		//heapify(heaparray, heapsize, current-1);
		printHeap(heaparray, heapsize, actualindex+1, left);
	}
	
}



void deleteSort(int heaparray[], int orderarray[], int &heapsize, int y){ //delete and sequentialize method
	int z = 0;
	
	while(y > 0){ //keep running until heap is empty
		int move;
		move = heaparray[0]; //get the root of the heap
		heaparray[0] = heaparray[heapsize-1]; //get the smallest/last element, this overrides the (previously) largest
		cout << heaparray[0];
		heapsize--; //shrink the heap size as element is essentially deleted
		orderarray[z] = move; //store the root to the new array via MAX HEAP
		z++;
		
		//heapify(heaparray, heapsize, startIndex);
		buildHeap(heaparray, heapsize); //call a resort of the modified heap to put the next largest at the root
		
		cout << endl;
		for(int t = 0; t < heapsize-1; t++){ //print heap array each time to show delete
			cout << heaparray[t] << " ";
		}
		y--;
	}
	
}



int main(){
	
	cout << "Would you like to enter numbers in the console or enter via txt file? \nType 'manual' or 'file': "; //how would the user like to input
	char methodinput[50];
	cin.getline(methodinput, 50);
	
	int v; //give heap array a dynamic size
	
	int inputarr[1000]; //initialize input outside for use later
	
	if(strcmp(methodinput, "manual") == 0){ //if user would like to enter values in the console
		cout << "\nNOTE: Any non-numerical characters will be treated as a zero int value. Any floats will be rounded down." << endl;
		cout << "Type 'stop' when you are finished." << endl;
		
		int i = 0; //acts as iterator as well as counter for allocated array size
		
		bool inputting = true;
		
		while(inputting == true){ //keep entering numbers
			char token[10];
			cin.getline(token, 10);
			
			if(strcmp(token, "stop") == 0){ //stop taking input
				inputting = false;
			}
			
			inputarr[i] = atoi(token); //convert the input token into an int for storing
			i++; //array size grows each time a token is added
		}
		
		v = i-1; //discard the 'stop' token
		
	}
	
	
	else if(strcmp(methodinput, "file") == 0){ //if the user would like to enter values from a file
		cout << "Type the file name (include the .txt extension): ";
		char* filename = new char[100];
		cin.getline(filename, 100);
		
		ifstream inFile; //file input
		inFile.open(filename);
		
		int inputToken;
		int count = 0;
		int i;
		
		while(inFile >> inputToken){ //input tokens from file into input array
			inputarr[count] = inputToken;
			count++;
			i++;
		}
		
		v = i-1; //don't discard anything
		
	}
	
	int heaparray[v]; //initialize the array that all the methods will be modifying
	
	for(int r = 0; r < v; r++){ //fill the heap "master array" with the input
		heaparray[r] = inputarr[r];
	}
	
  
    int heapsize = sizeof(heaparray) / sizeof(heaparray[0]);
	int newHeapsize; //don't declare yet
  
    buildHeap(heaparray, heapsize); //construct the heap using heapify algorithm



	
	int orderarray[v]; //initialize output array
	
	
	
	
	
	cout << "\nHeap array: ";
	for(int t = 0; t < heapsize; t++){ //print heap array
		cout << heaparray[t] << " ";
	}
	cout << " Size: " << heapsize;
	
	cout << "\n\nTree:\n" << endl;
    printHeap(heaparray, heapsize, 0, 1); //print heap as a tree using the constructed heap array
	
	
	
	
	cout << "\nHeap array:" << endl;
	for(int t = 0; t < heapsize-1; t++){ //print heap array before deletesort
		cout << heaparray[t] << " ";
	}
	//cout << " Size: " << heapsize;
	
	
	deleteSort(heaparray, orderarray, heapsize, heapsize); //call delete and sort method
	
	cout << endl;
	cout << "Sequenced (max) list:" << endl;
	
	for(int t = 0; t < v; t++){ //for loop: heapsize is zero so use v
		cout << orderarray[t] << " ";
	}
	
	
    return 0; 
} 