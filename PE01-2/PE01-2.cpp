// =======================================
// Singly-linked List
// 		- this program allows the user to create a singly linked list.
// A singly linked list is a list where each node is connected to another
// node (called the next node). Traversing though a singly linked list
// can only be done in one direction (from first node to last).
//
// programmed by: Justine Rome Ardepuela
// =======================================
#include <iostream>

using namespace std;

// include the class header and implementation to be used in this program.
#include "PE01-2_Interface.h"
#include "PE01-2_Implementation.cpp"

int main() {
	// program title and author
	cout << "SINGLY-LINKED LIST IMPLEMENTATION OF LIST\nProgrammed by: Justine Rome Ardepuela\n\n";
	
	// create the list
	// its members are initialized in the constructor
	SLList slist;
	
	// call the menu function of the class to allow the user to interact with the list
	slist.menu();
    
    return 0; // return zero and end the program
}
