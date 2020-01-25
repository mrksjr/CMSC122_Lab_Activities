#include <iostream>
#include <stack> // STL for c++ stack
#include <queue> // STL for c++ queue
#define MAXSIZE 50 // determines maximum size of user input array
using namespace std;

struct node {
	int data;
	
	node* left;
	node* right;
};

// Input functions
void getUserInput( int[], int* );
void displayInput( int[], int );

// General tree functions
node* createNode( int );
node* destroyTree( node* );

// Binary Tree functions
node* createTree( int[], int, int, node** );
void displayTree();
	void preOrder( node* );
	void inOrder( node* );
	void postOrder( node* );

// Heap Tree functions
void buildMaxHeap( int[], int );
void maxHeapify( int[], int, int );
void buildMinHeap( int[], int );
void minHeapify( int[], int, int );

void descendingSort( int[], int );
void ascendingSort( int[], int );

// Global Variables
node* BINTREE;

int main() {
	int INPUT[MAXSIZE]; // array INPUT stores the values of the binary tree's nodes
	int INPUTCOUNT = 0; // integer INPUTCOUNT determines the count of values in the array/tree
	BINTREE = NULL; // tree root BINTREE is initialized as a null ptr
	
	int choice;
	
	while(1) {
		// display menu
		cout << "MENU\n\n";
		cout << "[1] Input\n";
		cout << "[2] Display\n";
		cout << "[3] Sort Ascending\n";
		cout << "[4] Sort Descending\n";
		cout << "[0] Exit\n\n";
		cout << "Choice: ";
		cin >> choice;
		
		switch( choice ) {
			case 1:
				// call function to get user input
				getUserInput( INPUT, &INPUTCOUNT );
			break;
			
			case 2: {
				// call function to display the binary tree
				displayTree();
				
				// create a copy of the tree for heap creation
				int COPY[INPUTCOUNT];
				for ( int i = 0; i < INPUTCOUNT; i++ )
					COPY[i] = INPUT[i];
				
				// print max heap
				cout << "\tMax Heap: ";
				buildMaxHeap( COPY, INPUTCOUNT );
				
				for ( int i = 0; i < INPUTCOUNT; i++ )
					cout << COPY[i] << " ";
					
				cout << "\n";
				
				// print min heap
				cout << "\tMin Heap: ";
				buildMinHeap( COPY, INPUTCOUNT );
				
				for ( int i = 0; i < INPUTCOUNT; i++ )
					cout << COPY[i] << " ";
					
				cout << "\n\n";
				break;
			}
			
			case 3: {
				// prevent further execution if binary tree is empty
				if ( BINTREE == NULL ) {
					cout << "\n\tTree is empty!\n\n";
					continue;
				}
				
				// create a copy of input array
				int ASORT[INPUTCOUNT];
				for ( int i = 0; i < INPUTCOUNT; i++ ) {
					ASORT[i] = INPUT[i];
				}
				
				// sort in ascending order and print result
				ascendingSort( ASORT, INPUTCOUNT );
				
				cout << "\n\tAscending Order: ";
				for ( int i = 0; i < INPUTCOUNT; i++ )
					cout << ASORT[i] << " ";
				
				cout << "\n\n";
				break;
			}
			
			case 4: {
				// same stuff as max heap above
				if ( BINTREE == NULL ) {
					cout << "\n\tTree is empty!\n\n";
					continue;
				}
				
				// create a copy of input array
				int DSORT[INPUTCOUNT];
				for ( int i = 0; i < INPUTCOUNT; i++ ) {
					DSORT[i] = INPUT[i];
				}
				
				// sort in descending order and print result
				descendingSort( DSORT, INPUTCOUNT );
				
				cout << "\n\tDescending Order: ";
				for ( int i = 0; i < INPUTCOUNT; i++ )
					cout << DSORT[i] << " ";
				
				cout << "\n\n";
				break;
			}
			
			case 0:
				cout << "\n\tProgram terminated.\n\n";
				return 0;
			
			default:
				cout << "\n\tInvalid input.\n\n";
				continue;
		}
	}
	
	return 0;
}

//==========================================================================================
// INPUT FUNCTIONS
//==========================================================================================

void getUserInput( int arr[], int* count) {
	int choice;
	
	while(1) {
		cout << "\n\tINPUT OPTIONS\n\n";
		cout << "\t[1] Add inputs\n";
		cout << "\t[2] Clear inputs\n";
		cout << "\t[0] Cancel\n";
		cout << "\tChoice: ";
		cin >> choice;
		
		switch( choice ) {
			case 1:
				if ( *count == MAXSIZE ) {
					cout << "\n\tArray is full!\n";
					continue;
				}
				
				// ask user how many values will be added to the array
				cout << "\n\tHow many values would you like to add?\n";
				cout << "\tChoice: ";
				int c;
				cin >> c;
				
				int t;
				t = *count + c;
				// if the additional values count exceed the max size, reduce the input count accordingly
				if ( t > MAXSIZE ) {
					cout << "\n\tInput count exceeded maximum array size. Set to limit.";
					t = MAXSIZE;
				}
				
				// ask user for input
				cout << "\n";
				for ( int i = *count; i < t; i++ ) {
					cout << "\t[" << i << "] Input number >> ";
					cin >> arr[i];
				}
				
				cout << "\n";
				
				// update count of numbers in user input array
				*count = t;
				
				// if the binary tree has contents, destroy the tree
				if ( BINTREE != NULL )
					BINTREE = destroyTree( BINTREE );
				
				// create a new tree
				createTree( arr, 0, *count, &BINTREE );
			break;
			
			case 2:
				// set the count of the array to 0 (thus ignoring all the existing values in the array)
				*count = 0;
				cout << "\n\tInputs cleared.\n\n";
				
				// destroy the binary tree
				BINTREE = destroyTree( BINTREE );
			break;
			
			case 0:
				// if user chooses to cancel inputting
				cout << "\n\tAction cancelled.\n\n";
				return;
			
			default:
				// prevent user from entering invalid choices
				cout << "\n\tInvalid input.\n";
				continue;
		}
		
		break;
	}
	
	// notify user of changes made in the array
	cout << "\tAction completed.\n";
	cout << "\tUpdated ";
	displayInput( arr, *count );
}

// function to display the contents of the array that stores user input
void displayInput( int array[], int count ) {
	cout << "Input Array: ";
	
	if ( count == 0 )
		cout << "Empty."; // array is empty
	else
		for ( int i = 0; i < count; i++ )
			cout << array[i] << " ";
	
	cout << "\n\n";
}

//==========================================================================================
// GENERAL TREE FUNCTIONS
//==========================================================================================

// function used to create a new node
node* createNode( int x ) {
	node* temp = new node;
	
	temp->data = x;
	temp->right = NULL;
	temp->left = NULL;
	
	return temp;
}

// function to delete all nodes of a tree
node* destroyTree( node* root ) {
	if ( root == NULL ) return NULL;
	
	// first delete the children of the parent node
	root->left = destroyTree( root->left );
	root->right = destroyTree( root->right );
	
	// then delete the parent
	delete root;
	// set its value to null
	return NULL;
}

//==========================================================================================
// BINARY TREE FUNCTIONS
//==========================================================================================

// function used to create a tree from the input array
node* createTree( int arr[], int index, int count, node** root ) {
	// if the index of the number does not exceed the maximum count of the array
	if ( index < count ) {
		// create a node for the number
		node* temp = createNode( arr[index] );
		// set it as the root of its own subtree
		*root = temp;
		
		int a = 2 * index + 1;
		int b = 2 * index + 2;
		// if the index of the number is N, then then its left child will be the number at index 2N+1
		(*root)->left = createTree( arr, a, count, &( (*root)->left ) );
		// and its right child will be the number at index 2N+2
		(*root)->right = createTree( arr, b, count, &( (*root)->right ) );
	}
	
	// save the created node as the value of the receiving variable
	return *root;
}

// function to display the contents of the tree
void displayTree() {
	// check if binary tree is empty
	if ( BINTREE == NULL ) {
		cout << "\n\tTree is empty!\n\n";
		return;
	}
	
	// display the binary tree according to preorder, inorder, and postorder transversal algorithms
	cout << "\n\tTREE DISPLAY:\n";
	cout << "\n\tPreorder: ";
	preOrder( BINTREE );
	
	cout << "\tInorder: ";
	inOrder( BINTREE );
	
	cout << "\tPostorder: ";
	postOrder( BINTREE );
	
	cout << "\n";
}

	void preOrder( node* root ) {
		// push root to empty stack
		stack<node*> nodeStack;
		nodeStack.push( root );
		
		// pop all items one by one
		while ( nodeStack.empty() == false ) {
			node* top = nodeStack.top();
			cout << top->data << " ";
			nodeStack.pop();
			
			//	push its right child
			if ( top->right )
				nodeStack.push( top->right );
			//	push its left child
			if ( top->left )
				nodeStack.push( top->left );
			// right child is pushed first so that the left is processed first since this is a stack
		}
		
		cout << "\n";
	}
	
	void inOrder( node* root ) {
		// push root to empty stack
		stack<node*> nodeStack;
		node* temp = root;
		
		// while stack isn't empty or temp is not null
		while ( temp != NULL || nodeStack.empty() == false ) {
			// go to the leftmost node in the subtree of the current node
			while ( temp ) {
				nodeStack.push( temp );
				temp = temp->left;
			}
			
			// pop the top of the stack and print it
			temp = nodeStack.top();
			nodeStack.pop();
		
			cout << temp->data << " ";
			
			// go to the right child of the current node
			temp = temp->right;
		}
		
		cout << "\n";
	}
	
	void postOrder( node* root ) {
		// create 2 stacks and push root to the 1st stack
		// the 2nd stack will be used to print the postorder result
		stack<node*> stack1, stack2;
		stack1.push( root );
		
		node* temp;
		// while 1st stack isn't empty
		while ( !stack1.empty() ) {
			// pop it from 1st stack and push it to 2nd stack
	 		temp = stack1.top();
	 		stack1.pop();
	 		stack2.push( temp );
	 		
	 		// if node has a left child, push it to 1st stack
	 		if ( temp->left )
	 			stack1.push( temp->left );
	 		// if node has a right child, push it to 1st stack
	 		if ( temp->right )
	 			stack1.push( temp->right );
		}
		
		// while 2nd stack isnt empty, pop and print every node in it
		while ( !stack2.empty() ) {
			temp = stack2.top();
			stack2.pop();
		
			cout << temp->data << " ";
		}
		
		cout << "\n";
	}

//==========================================================================================
// MAX HEAP TREE FUNCTIONS
//==========================================================================================

void buildMaxHeap( int ARR[], int n ){
	// start with the last non-leaf node of the tree
	int start = ( n / 2 ) - 1;
	// heapify the array/tree in reverse-level order
	for ( int i = start; i >= 0; i-- )
		maxHeapify( ARR, i, n );
}

void maxHeapify( int ARR[], int i, int n ) {
	int largest = i; // root index of the subtree is i
	int left = 2 * i + 1; // left child index is 2i + 1
	int right = 2 * i + 2; // right child index is 2i + 2
	
	// compare the root value and its left and right child ( if they exist or within array bounds )
	
	if ( left < n && ARR[left] > ARR[largest] )
		largest = left;
		
	if ( right < n && ARR[right] > ARR[largest] )
		largest = right;
		
	// if the largest value isn't the root, swap it with the largest then heapify from the new root
	if ( largest != i ) {
		int temp = ARR[i];
		ARR[i] = ARR[largest];
		ARR[largest] = temp;
		
		maxHeapify( ARR, largest, n );
	}
}

void buildMinHeap( int ARR[], int n ) {	
	// start with the last non-leaf node of the tree
	// heapify the array/tree in reverse-level order
    int start = ( n / 2 ) - 1;
	for ( int i = start; i >= 0; i-- )
		minHeapify( ARR, i, n );
}

void minHeapify(int ARR[], int i, int n) {
	int least = i; // root index of the subtree is i
	int left = 2 * i + 1; // left child index is 2i + 1
	int right = 2 * i + 2; // right child index is 2i + 2
	
	// compare the root value and its left and right child ( if they exist or within array bounds )
	
	if ( left < n && ARR[left] < ARR[least] )
		least = left;
		
	if ( right < n && ARR[right] < ARR[least] )
		least = right;
		
	// if the least value isn't the root, swap it with the least then heapify from the new root
	if ( least != i ) {
		int temp = ARR[i];
		ARR[i] = ARR[least];
		ARR[least] = temp;
		
		minHeapify( ARR, least, n );
	}
}

void ascendingSort( int ARR[], int n ) {
	// build the max heap
	buildMaxHeap( ARR, n );
	
	while ( n != 0 ) {
		// swap the largest value ( element at index 0 ) with the end of the array
		int temp = ARR[0];
		ARR[0] = ARR[n - 1];
		ARR[n - 1] = temp;
		
		// 'reduce' the array size
		// then heapify the array without the sorted elements
		maxHeapify( ARR, 0, --n );
	}
}

void descendingSort( int ARR[], int n ) {
	// build the min heap
	buildMinHeap( ARR, n );
	
	while ( n != 0 ) {
		// swap the smallest value ( element at index 0 ) with the end of the array
		int temp = ARR[0];
		ARR[0] = ARR[n - 1];
		ARR[n - 1] = temp;
		
		// 'reduce' the array size
		// then heapify the array without the sorted elements
		minHeapify( ARR, 0, --n );
	}
}
