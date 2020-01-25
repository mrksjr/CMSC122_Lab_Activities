#include <iostream>
using namespace std;

struct node{
	node *next;
	string order;
	string name;
};

#include "PE03-Class.h"
#include "PE03-ClassFunctions.cpp"

int menu();
void addperson( Queue* );
void serve( Queue* );
void next( Queue* );
void close( Queue* );
	
int main() {
	Queue line;
	
	while(1) {
		// display menu and ask for user input
		int choice = menu();
		
		switch( choice ) {
			case 1: addperson( &line ); break;
			case 2: serve( &line ); break;
			case 3: next( &line ); break;
			case 4: close( &line ); break;
			
			case 0:
				cout << "\n\n\tProgram terminated.";
				return 0;
		}
	}
}

int menu() {
	int choice;
	
	while (1) {
		cout << "CHING CHONG STORE Menu:"
			<< "\n\n[1] Fall in line"
			<< "\n[2] Serve Order"
			<< "\n[3] Next order"
			<< "\n[4] Closing Time"
			<< "\n[0] Exit"
			<< "\n\n\tEnter choice: ";
			
		cin >> choice;
		
		// prevent invalid inputs
		if ( choice < 0 || choice > 4 ) {
			cout << "\n\tInvalid input!\n\n";
			continue;
		}
		
		break;
	}
	
	return choice;
}

void addperson( Queue* line ) {
	string name, order;
	
	// ask user for customer's name
	cout << "\n\tEnter customer's name: ";
	cin >> name;
	// ask user for customer's order
	cout << "\tEnter order: ";
	cin >> order;
	
	// add customer and order to queue
	line->ENQUEUE( order, name );
	
	cout << "\n\t" << name << " fell in line with order " << order << ".\n\n";
}

void serve( Queue* line ) {
	if ( line->EMPTY() ) { // alert user that queue is empty
		cout<<"\n\tThe QUEUE is EMPTY. No orders to serve.\n\n";
		return;
	}
	
	// call DEQUEUE function of line and save it to a temporary pointer
	node* current = line->DEQUEUE();
	
	cout << "\n\tNow serving "<< current->order << " to customer " << current->name << ".\n\n";
}

void next( Queue* line ) {
	if ( line->EMPTY() ) { // alert user that queue is empty
		cout<<"\n\tThe QUEUE is EMPTY. No order to serve.\n\n";
		return;
	}
	
	// get front node of line and point it to a temporary pointer
	node* next = line->FRONT();
	
	cout << "\n\tNext order: "<< next->order << " of customer "<< next->name << ".\n\n";
}

void close( Queue* line ) {
	if ( line->EMPTY() ) { // alert user that queue is empty
		cout<<"\n\tThe QUEUE is EMPTY. No order to serve.\n\n";
		return;
	}
	
	// serve everything in the queue until it is empty
	while( !line->EMPTY() )
		serve( line );
	
	cout << "\n\tAll the orders have been served.\n\n";
}
