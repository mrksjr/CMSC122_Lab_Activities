DLList::DLList() {
	// initialize the class's member variables
	head = NULL; // head points to nothing
	tail = NULL; // tail points to nothing
	listSize = 0; // list has 0 nodes
	
	/* Example <- comment this line to add preset values to list
		addAtPos( 1, 99 );
		addAtPos( 2, 99 );
		addAtPos( 1, 99 );
		addAtPos( 3, 99 );
		addAtPos( 4, 99 );
		addAtPos( 5, 99 );
		addAtPos( 2, 99 );
		addAtPos( 3, 99 );
		addAtPos( 1, 99 );
		listSize = 9;
		displayList();
//	*/
}

void DLList::displayMenu() {
	while (1) {
		int choice; // stores the user's choice when using the menu
		
		cout << "List MENU:	" << endl;
		cout << "[1] Add Element" << endl;
		cout << "[2] Delete Element" << endl;
		cout << "[3] Display List" << endl;
		cout << "[4] Sort List" << endl;
		cout << "[5] Delete List" << endl;
		cout << "[0] Exit Program" << endl;
		
		cout << "\n\tWhat would you like to do?\n\tChoice: ";
		cin >> choice;
		
		// using switch control structure to match the user's choice and the corresponding action
		switch( choice ) {
			case 1: addElement(); break;
			case 2: deleteElement(); break;
			case 3: displayList(); break;
			case 4: sortList(); break;
			case 5: deleteList(); break;
			
			case 0:
				cout << "\n\n\tProgram terminated.\n";
				return; // return the program flow to the main function, thus ending it
				
			// prevent erroneous inputs
			default:
				cout << "\tInvalid input.\n\n";
				continue;
		}
	}
}

void DLList::addElement() {
	int x;
	cout << "\n\tPlease enter the element to be added: ";
	cin >> x;
	
	while (1) {
		int choice;
		
		cout << "\n\tWhere to add the element?" << endl;
		cout << "\t[1] Start of the list" << endl;
		cout << "\t[2] End of the list" << endl;
		cout << "\t[3] Specific position\n\tChoice: ";
		cin >> choice;
		
		switch ( choice ) {
			case 1: // adding element to the start of the list
				addStart( x );
			break;
			
			case 2: // adding element to the end of the list
				addEnd( x );
			break;
			
			case 3:
				int pos;
				displayList(); // display list to make it easier for user
				cout << "\tAt which position do you want the element?\n\tChoice: ";
				cin >> pos;
				
				addAtPos( x, pos );
			break;
			
			// prevent erroneous inputs
			default:
				cout << "\tInvalid input.\n\n";
				continue;
		}
		
		break;
	}
	
	listSize++; // increase list size since a node was added
}

	void DLList::addStart( int x ) {
		if ( head == NULL ) { // adding to an empty list
			head = new Node;
			
			head->data = x;
			head->next = NULL;
			head->prev = NULL;
			
			tail = head;
		}
		else { // adding a new node before the head
			Node* temp = new Node; // create a temporary node
	
			temp->data = x;
			temp->next = head; // place the new node before the head
			temp->prev = NULL;
	
			head->prev = temp; // set current head's prev to point to new node
			head = temp; // set the new node as new head of the list
		}
		
		cout << "\n\tElement " << x << " was added to the start of the list.\n\n";
	}
	
	void DLList::addEnd( int x ) {
		if ( head == NULL ) { // adding to an empty list
			head = new Node;
			
			head->data = x;
			head->next = NULL;
			head->prev = NULL;
			
			tail = head;
		}
		else { // adding a new node after the tail
			Node *temp = new Node;
			
			temp->data = x;
			temp->prev = tail; // place the node after the list
			temp->next = NULL;
			
			tail->next = temp; // set current tail's next to point to new node
				
			tail = temp; // set the new node as new tail of the list
		}
		
		cout << "\n\tElement " << x << " was added to the end of the list.\n\n";	
	}
	
	void DLList::addAtPos( int x, int p ) {	
		/* Selecting a currently occupied position causes the inserted node to be placed
		to that position and the replaced node to be shifted after the inserted node. */
		int pos = p;
		
		if ( head == NULL ) { // adding to an empty list
			head = new Node;
			
			head->data = x;
			head->next = NULL;
			head->prev = NULL;
			
			tail = head;
			pos = 0;
		}
		else {
			Node *temp = new Node;
			temp->data = x;
			
			if ( pos >= 0 && pos <= listSize ) { // selected position is in range of head-tail
				Node *current = head;
				
				while ( current->next != NULL && pos != 0 ) {
					// scan the list
					current = current->next;
					pos--;
				}
				
				// place the node into the list by connecting it the its adjacent node
				temp->next = current;
				temp->prev = current->prev;
				
				// condition is added to prevent accessing a non-existent prev pointer of a NULL address.
				if ( current->prev != NULL ) {
					current->prev->next = temp;
					current->prev = temp;
				}
				
				// set the new node to either head or tail depending on its location
				if ( temp->prev == NULL )
					head = temp;
				if ( temp->next == NULL )
					tail = temp;	
			
				pos = p;
			}
			else { // user input exceeded the bounds of the list so the node is placed at the tail of the end
				pos = listSize;
				// place new node at the end of the list
				temp->next = NULL;
				temp->prev = tail;
				
				// set the new node to be the new tail
				tail->next = temp;
				tail = temp;
				
				cout << "\n\tChosen position does not exist. Element is added to the end of the list instead.";
			}
		}
		
		cout << "\n\tElement " << x << " was added to position " << pos << ".\n\n";
	}


void DLList::deleteElement() {
	// prompt user if list is empty
	if ( head == NULL ) {
		cout << "\n\tList is empty!\n\n";
		return;
	}
	
	int x;
	cout << "\n\tEnter the element to be deleted: ";
	cin >> x;
	
	// create a temporary array to store the positions of target element
	int index[listSize];
	int xCount = locateElement( x, index ); // and find the indices if any exist
	
	if ( xCount == 0 ) // element is not found in the list
		cout << "\n\tThe list contains no such element.\n\n";
	else if ( xCount == 1 ) { // if the element is unique, it is deleted right away
		Node* temp = head;
		
		while ( temp->data != x )
			temp = temp->next;
		
		if ( temp->prev == NULL )
			head = temp->next;
		if ( temp->next == NULL )
			tail = temp->prev;
		
		if ( temp->prev != NULL )
			temp->prev->next = temp->next;
		if ( temp->next != NULL )
			temp->next->prev = temp->prev;
		
		delete temp;
		
		cout << "\n\tThe element " << x << ", which is at position " << index[0] << ", has been deleted.\n\n";
	}	
	else { // multiple instances of the element is found
		cout << "\n\tThe element " << x << " occurs at the following positions: ";
		for ( int i = 0; i < xCount; i++ )
			cout << index[i] << " ";
			
		int pos;
		while (1) { // ask user to choose which position would be deleted
			cout << "\n\tWhich position to delete?\n\tChoice: ";
			cin >> pos;
			
			int valid = 0;
			
			// search the array of indices to check if the chosen position is valid
			for ( int i = 0; i < xCount; i++ )
				if ( pos == index[i] ) {
					valid = 1;
					break;
				}
			
			// prevent erroneous inputs
			if ( !valid ) {
				cout << "\n\tInvalid input.";
				continue;
			}
			
			break;
		}
		
		int pos2 = pos; // stores pos value to be used in the output text later
		Node* temp = head; // used to select a node in the list when traversing it
		
		// traverse through the list until the pos counter is exhausted.
		while ( pos != 0 ) {
			temp = temp->next;
			pos--;
		}
		
		// if the deleted node is a head/tail, set its next/previous node to be the new head/tail.
		if ( temp->prev == NULL )
			head = temp->next;
		if ( temp->next == NULL )
			tail = temp->prev;
		
		// disconnect the node from its adjacent nodes in the list
		if ( temp->next != NULL )
			temp->next->prev = temp->prev;
		if ( temp->prev != NULL )
			temp->prev->next = temp->next;
		
		// free the memory pointed at by temp
		delete temp;
		
		cout << "\n\tThe element " << x << " at position " << pos2 << " has been deleted.\n\n";
	}
	
	listSize--; // reduce the list size since a node was removed.
}

	int DLList::locateElement( int target, int out[] ) {
		Node *temp = head;
		int targIndex = 0;
		int pos = 0;
		
		// search the list for nodes that match the target value
		// if a match is found, its corresponding index is saved to the array
		while ( temp != NULL ) {
			if ( temp->data == target ) {
				out[pos] = targIndex;
				pos++;
			}
			
			temp = temp->next;
			targIndex++;
		}
		
		return pos;
	}
	
void DLList::displayList() const {
	// prompt user if list is empty
	if ( head == NULL) {
		cout << "\n\tList is empty!\n\n";
		return;
	}

	Node *temp = head;
	int i = 0;
	
	// display the position and values of each node
	cout << "\n\tList elements:" << endl;
	while ( temp != NULL ) {
		cout << "\t[" << i << "] " << temp->data << endl;
		// traverse the list
		temp = temp->next;
		i++;
	}
	
	cout << endl;
}

void DLList::sortList() {
	// prompt user that list is empty
	if ( head == NULL) {
		cout << "\n\tList is empty!\n\n";
		return;
	}
	
	int choice;
	
	// ask user which order of sorting will be used
	while (1) {
		cout << "\n\tWhich way would you want to sort the list?" << endl;
		cout << "\t[1] Ascending order" << endl;
		cout << "\t[2] Descending order\n\tChoice: ";
		cin >> choice;
		
		// prevent erroneous inputs
		if ( choice != 1 && choice != 2 ) {
			cout << "\n\tInvalid input.";
			continue;
		}
		
		break;
	}
	
	Node *currentNode = head, *nextNode;
	
	// ASCENDING ORDER
	// traverse through the list by comparing each
	// node value to the values of the nodes after it.
	while ( currentNode->next != NULL ) {
		nextNode = currentNode->next;
		
		if ( choice == 1 ) {
			while ( nextNode != NULL ) {
				//	 if the current node is greater than the node it is being compared to, swap their values
				if ( currentNode->data > nextNode->data ) {
					int temp = currentNode->data;
					currentNode->data = nextNode->data;
					nextNode->data = temp;
				}
				
				nextNode = nextNode->next;
			}
		}
		// DESCENDING ORDER
		// traverse through the list by comparing each
		// node value to the values of the nodes after it.
		else { 
			while ( nextNode != NULL ) {
				//	 if the current node is lesser than the node it is being compared to, swap their values
				if ( currentNode->data < nextNode->data ) {
					int temp = currentNode->data;
					currentNode->data = nextNode->data;
					nextNode->data = temp;
				}
				
				nextNode = nextNode->next;
			}
		}
			
		currentNode = currentNode->next;
	}
	
	// print ASCENDING or DESCENDING depending on the user's choice
	cout << "\n\tThe list has been sorted in " << ( choice == 1 ? "A" : "DE" ) << "SCENDING order.\n";
	displayList();
	// display the list to show the modified list to the user
}

void DLList::deleteList() {
	// prompt user that list is empty
	if ( head == NULL ) {
		cout << "\n\tList is empty!\n\n";
		return;
	}
	
	Node *temp = head;
	Node *nextNode;
	
	// traverse through the list and delete/free each node one by one
	while ( temp != NULL ) {
		nextNode = temp->next;
		delete temp;
		temp = nextNode;
	}
	
	// set the head and tail pointers to point at nothing
	head = tail = NULL;
	
	cout << "\n\tThe list has been emptied!\n\n";
}
