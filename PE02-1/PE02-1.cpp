#include <iostream>
#define MAXLISTSIZE 10
using namespace std;

// include the class header and implementation to be used in this program.
#include "PE02-1_ArrayList.h"
#include "PE02-1_ArrayList.cpp"
#include "PE02-1_Interface.h"
#include "PE02-1_Implementation.cpp"

int main() {	
	// create the list
	// its members are initialized in the constructor
	stack kitchen;
	
	// call the menu function of the class to allow the user to interact with the list
	kitchen.menu();
    
    return 0; // return zero and end the program
}
