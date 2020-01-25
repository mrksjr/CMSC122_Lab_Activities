#ifndef SLLIST_H
#define SLLIST_H

// singly linked list node prototype
struct Node {
	int data;
	Node *next;
};

// declaration of class member functions and member variables
class SLList {
	public:
		SLList();
		
		void menu();
		void insert();
		void delet();
			int locateElement( int, int[] );
		void display() const;
		void sort();
		void deleteList();
		
	private:
		Node *head; // points to the head/first element of the list
		Node *tail; // points to the tail/last element of the list
		int listSize; // keeps track of the list's size
	
};

#endif
