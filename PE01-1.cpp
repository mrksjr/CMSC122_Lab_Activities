// =======================================
// Array Implementation of Linked Lists (PE01-1)
// 		- this program simulates a linked list by using an array instead of pointers.
//
// programmed by: Christian Vincent Binobo
// =======================================
#include <iostream>

// MAXLISTSIZE value determines list fixed size
#define MAXLISTSIZE 50

using namespace std;

// include the class header and implementation to be used in this program.
#include "PE01-1_Interface.h"
#include "PE01-1_Implementation.cpp"

int main(){
	// program title and author
	cout << "ARRAY IMPLEMENTATION OF LIST\nProgrammed by: Christian Vincent Binobo\n\n";
	
	// create the list
	// its members are initialized in the constructor
	ArrayList List;
	
	// call the menu function of the class to allow the user to interact with the list
	List.Menu();
		
	return 0;
}


