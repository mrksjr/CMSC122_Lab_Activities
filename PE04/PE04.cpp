#include <iostream>
#include <stack>
using namespace std;

#include "PE04_ClassDefinition.h"
#include "PE04_ClassFunctions.cpp"

void menu();

void insertItem( tree* );
void deleteItem( tree* );
void searchItem( tree );
void findMax( tree );
void findMin( tree );
void findSucc( tree );
void findPred( tree );
void display( tree );

int main() {
	tree TREE;
	int choice;
	
	while (1) {
		menu();
		cin >> choice;
		
		switch ( choice ) {
			case 1: insertItem( &TREE );
			break;
			
			case 2: deleteItem( &TREE );
			break;
			
			case 3: searchItem( TREE );
			break;
			
			case 4: findMax( TREE );
			break;
		
			case 5: findMin( TREE );
			break;
			
			case 6: findSucc( TREE );
			break;
			
			case 7: findPred( TREE );				
			break;
			
			case 8: display( TREE );
			break;
			
			case 0:
				cout << "\n\n\tProgram Terminated.\n\n";
				return 0;
			
			default:
				cout << "\n\tInvalid input.\n\n";
				continue;
		}
	}
	
	return 0;
}

void menu() { // function to display menu
	cout << "MENU\n\n";
	cout << "[1] Insert item\n";
	cout << "[2] Delete item\n";
	cout << "[3] Search item\n";
	cout << "[4] Find maximum\n";
	cout << "[5] Find minimum\n";
	cout << "[6] Find successor\n";
	cout << "[7] Find predecessor\n";
	cout << "[8] Display tree\n";
	cout << "[0] Exit\n\n";
	cout << "Choice: ";
}

void insertItem( tree* TREE ) { // function to insert
	int n;
	
	// ask user for input
	cout << "\n\tChoose number to be inserted: ";
	cin >> n;
	
	// call tree function to create and place a new node into the tree
	TREE->insertNode( TREE->ROOT, n );
}

void deleteItem( tree* TREE ) {
	// prompt user that tree is empty
	if ( TREE->ROOT == NULL ) {
		cout << "\n\tThe tree is empty!\n\n";
		return;
	}
	
	int n;
	// ask user for input
	cout << "\n\tChoose number to be deleted: ";
	cin >> n;
	
	// call tree function to delete desired value from tree
	// return value determines the result of the deletion call
	node* temp = TREE->deleteNode( TREE->ROOT, n );
	
	// the root is null or the value does no exist in the tree
	if ( temp == NULL )
		cout << "\n\tThe value does not exist.\n\n";
	// after deleting the value, search the tree again. if the value is still found in the tree,
	// that means that the value had multiple instances
	else if ( TREE->search( TREE->ROOT, n ) != NULL )
		cout << "\n\tThe deleted value has multiple instances. Count: " << temp->count << "\n\n";
	// value was deleted normally from the tree ( includes deleting node with 1, 2, or 0 children )
	else
		cout << "\n\tThe value " << n << " has been deleted from the tree.\n\n";
}

void searchItem( tree TREE ) {
	// prompt user that tree is empty
	if ( TREE.ROOT == NULL ) {
		cout << "\n\tThe tree is empty!\n\n";
		return;
	}
	
	int n;
	// ask user for input
	cout << "\n\tChoose number to search: ";
	cin >> n;
	
	// call tree function to look target value
	// return value determines result of search
	node* temp = TREE.search( TREE.ROOT, n );
	
	// value exists in the tree
	if ( temp )
		cout << "\n\tThe value " << temp->data << " exists in the tree with count " << temp->count << ".\n\n";
	// value does not exist
	else
		cout << "\n\tThe value does not exist.\n\n";
}

void findMax( tree TREE ) {
	// prompt user that tree is empty
	if ( TREE.ROOT == NULL ) {
		cout << "\n\tThe tree is empty!\n\n";
		return;
	}
	
	// call tree function to find maximum value in tree
	node* temp = TREE.findMax( TREE.ROOT );

	cout << "\n\tThe maximum value found in the tree is " << temp->data << ".\n\n";
}

void findMin( tree TREE ) {
	// prompt user that tree is empty
	if ( TREE.ROOT == NULL ) {
		cout << "\n\tThe tree is empty!\n\n";
		return;
	}
	
	// call tree function to find minimum value in tree
	node* temp = TREE.findMin( TREE.ROOT );
	
	cout << "\n\tThe minimum value found in the tree is " << temp->data << ".\n\n";
}

void findSucc( tree TREE ) {
	// prompt user that tree is empty
	if ( TREE.ROOT == NULL ) {
		cout << "\n\tThe tree is empty!\n\n";
		return;
	}
	
	int n;
	// ask user for input
	cout << "\n\tChoose number to search: ";
	cin >> n;
	
	// search for value in the tree
	node* temp = TREE.search( TREE.ROOT, n );
	
	// if it exists, look for its successor
	if ( temp ) {
		// call tree function to find the successor of the target value
		node* temp2 = TREE.findSucc( temp );
		
		// target has a successor
		if ( temp2 )
			cout << "\n\tThe successor of the value " << temp->data << " is " << temp2->data << ".\n\n";
		else
			cout << "\n\tThe value does not have a successor.\n\n";
	}
	else
		cout << "\n\tThe value does not exist.\n\n";
}

void findPred( tree TREE ) {
	// prompt user that tree is empty
	if ( TREE.ROOT == NULL ) {
		cout << "\n\tThe tree is empty!\n\n";
		return;
	}
	
	int n;
	// ask user for input
	cout << "\n\tChoose number to search: ";
	cin >> n;
	
	// search for value in the tree
	node* temp = TREE.search( TREE.ROOT, n );
	
	// if it exists, look for its predecessor
	if ( temp ) {
		// call tree function to find predecessor of the target value
		node* temp2 = TREE.findPred( temp );
		
		// target has a predecessor
		if ( temp2 )
			cout << "\n\tThe predecessor of the value " << temp->data << " is " << temp2->data << ".\n\n";
		else
			cout << "\n\tThe value does not have a predecessor.\n\n";
	}
	else
		cout << "\n\tThe value does not exist.\n\n";
}

void display( tree TREE ) {
	// prompt user that tree is empty
	if ( TREE.ROOT == NULL ) {
		cout << "\n\tThe tree is empty!\n\n";
		return;
	}
	
	// print the tree according to each traversal algorithms
	cout << "\n\tPREORDER: ";
	TREE.preOrder();
	cout << "\n\tINORDER: ";
	TREE.inOrder();
	cout << "\n\tPOSTORDER: ";
	TREE.postOrder();
}
