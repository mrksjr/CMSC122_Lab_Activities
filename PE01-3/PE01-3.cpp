// =======================================
// Doubly linked List Implementation of List (PE01-3)
// 		- this program allows the user to create a doubly linked list.
// A doubly linked list is a list where each node is connected to two
// other nodes (called the next and previous nodes) and therefore allows
// traversing back and forth in the list.
//
// programmed by: Mark Andrae Sijera
// =======================================
#include <iostream>

using namespace std;

// include the class header and implementation to be used in this program.
#include "PE01-3_Interface.h"
#include "PE01-3_Implementation.cpp"

int main() {
	// program title and author
	cout << "DOUBLY LINKED LIST IMPLEMENTATION OF LIST\nProgrammed by: Mark Andrae Sijera" << endl << endl;
	
	// create the list
	// its members are initialized in the constructor
	DLList dlist;
	
	// call the menu function of the class to allow the user to interact with the list
	dlist.displayMenu();
	
	return 0; // return zero and end the program
}
