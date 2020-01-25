#ifndef DLLIST_H
#define DLLIST_H

// doubly linked list node prototype
struct Node {
	int data;
	Node* next;
	Node* prev;
};

// declaration of class member functions and member variables
class DLList {
	public:
		DLList();
		
		void displayMenu();
		
		void addElement();
			void addStart( int );
			void addEnd( int );
			void addAtPos( int, int );
		void deleteElement();
			int locateElement( int, int[] );
		void displayList() const;
		void sortList();
		void deleteList();
		
	private:
		Node* head; // points to the head/first element of the list
		Node* tail; // points to the tail/last element of the list
		int listSize; // keeps track of the list's size
};

#endif
