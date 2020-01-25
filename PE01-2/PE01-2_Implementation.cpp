SLList::SLList() {
	// initialize the class's member variables
	head = NULL; // head points to nothing
	tail = NULL; // tail points to nothing
	listSize = 0; // list has 0 nodes
}

void SLList::menu() {
	while(1) {
		int ch; // stores the user's choice when using the menu
        cout << "List MENU";
        cout << "\n[1] Add Element\n[2] Delete Element\n[3] Display List\n[4] Sort List\n[5] Delete List\n[0] Exit Program\n";
       	cout << "\n\tWhat would you like to do?\n\tChoice: ";
		cin >> ch;
        
		// using switch control structure to match the user's choice and the corresponding action
        switch( ch ) {
	        case 1: insert(); break;
	        
	        case 2: delet(); break;
	        
	        case 3: display(); break;
	        
	        case 4: sort(); break;
	        
	        case 5: deleteList(); break;
	        	
	        case 0:
				cout << "\n\tProgram terminated.\n";
	            return; // return the program flow to the main function, thus ending it
	            
			// prevent erroneous inputs
	        default:
	        	cout << "\n\tInvalid input\n\n";
	        	continue;
        }
    }
}

void SLList::insert() {
	int n;
	cout << "\n\tEnter element to be added: ";
	cin >> n;
	
	while (1) {
		int ch;
		cout << "\n\tWhere to add Element?";
		cout << "\n\t[1] Start of List\n\t[2] End of List\n\t[3] Specific Position";
		cout << "\n\tEnter Your Choice: ";
	    cin >> ch;
		
		Node *temp = new Node;
		temp->data = n;
	    
	    switch( ch )
	    {
	    	case 1: // adding to the start of list
	    		temp->next = head;
	    		head = temp;
	    		
	    		if ( head->next == NULL ) // if head node has no node after it, make tail point at it too
	    			tail = temp;
	    			
				cout << "\n\tElement " << n << " was added to the start of the list.\n\n";
	    	break;
	    	
	    	case 2: // adding to the end of list
	    		temp->next = NULL;
	    		
	    		if ( tail == NULL ) // if list is empty
	    			head = tail = temp;
				else {
					tail->next = temp;
					tail = temp;
				}
				
				cout << "\n\tElement " << n << " was added to the end of the list.\n\n";
			break;
			
			case 3: // add new node to a position/location of choice in the list
				int pos;
				display(); // display the list elements to the user for easier choosing of position
				cout << "\tAt which position do you want the element?\n\tChoice: ";
				cin >> pos;
				
				// adding to an empty list
				if ( head == NULL ) {
					// make the head pointer point to the new node
					head = temp;
					head->next = NULL;
					
					// since it is the only node in the list, it is both head and tail
					tail = head;
					pos = 0;
				}
				else {
					if ( pos >= 0 && pos <= listSize ) { // selected position is in range of head-tail
						Node *current = head; // points to the node currently being utilized
						Node *prevNode = NULL; // points to the 'previous' node
						int p = pos; // holds the pos's value for use at outputting
						
						while ( current->next != NULL && pos != 0 ) {
							// scan the list
							prevNode = current;
							current = current->next;
							pos--;
						}
						
						// connect the new node to the node next to it
						temp->next = current;
						
						// if the previous address is not null, connect the previous node to the new node
						if ( prevNode != NULL )
							prevNode->next = temp;
						
						// if the previous spot in the list is NULL, then new node must be the new head
						if ( prevNode == NULL )
							head = temp;
						// same applies with tail for nodes at the end of the list
						if ( temp->next == NULL )
							tail = temp;	
					
						pos = p;
					}
					else { // user input exceeded the bounds of the list so the node is placed at the tail of the end
						pos = listSize;
						// place new node at the end of the list
						temp->next = NULL;
						
						// set the new node to be the new tail
						tail->next = temp;
						tail = temp;
								
						cout << "\n\tChosen position does not exist. Element is added to the end of the list instead.";
					}
				}
			
				cout << "\n\tElement " << n << " was added to position " << pos << ".\n\n";
			break;
				
			default:
				cout << "\tInvalid input.\n\n";
				continue;					
		}
		
		listSize++;
		break;
	}
}

void SLList::delet() {
	// prompt user that list is empty
    if( head == NULL ) {
        cout<<"\n\tList is empty.\n\n";
        return;
    }
	
	int x;
	cout << "\n\tEnter the element to be deleted: ";
	cin >> x;
	
	// create a temporary array to store the positions of target element
	int index[listSize];
	int xCount = locateElement( x, index ); // and find the indices if any exist
	
	if ( xCount == 0 )
		cout << "\n\tThe list contains no such element.\n\n";
	else if ( xCount == 1 ) { // if the element is unique, it is deleted right away
		Node* temp = head;
		Node* prevNode = NULL;
		
		while ( temp->data != x ) {
			prevNode = temp;
			temp = temp->next;
		}
		
		if ( prevNode == NULL )
			head = temp->next;
		if ( temp->next == NULL )
			tail = prevNode;
		
		if ( prevNode != NULL )
			prevNode->next = temp->next;
		
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
		Node* prevNode = NULL; // used to select the previous node

		// traverse through the list until the pos counter is exhausted.
		while ( pos != 0 ) {
			prevNode = temp;
			temp = temp->next;
			pos--;
		}
		
		// disconnect the node from its adjacent nodes in the list
		// if the deleted node is a head/tail, set its next/previous node to be the new head/tail.
		if ( prevNode == NULL )
			head = temp->next;
		if ( temp->next == NULL )
			tail = prevNode;
		
		// disconnect the node from its adjacent nodes in the list
		if ( prevNode != NULL )
			prevNode->next = temp->next;
		
		// free the memory pointed at by temp
		delete temp;
		
		cout << "\n\tThe element " << x << " at position " << pos2 << " has been deleted.\n\n";
	}
	
	listSize--; // reduce the list size since a node was removed.
}

	int SLList::locateElement( int target, int out[] ) {
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

void SLList::display() const {
	// prompt user that list is empty
	if( head == NULL ) {
        cout<<"\n\tList is empty.\n\n";
        return;
    }
    
	int l = 0;
    Node *temp = head;
    
	// display the position and values of each node
	cout << "\n\tList elements:" << endl;
    while ( temp != NULL ) {
    	cout << "\t[" << l << "] " << temp->data << endl;
    	// traverse the list
        temp = temp->next;	
    	l++;
    }
    
    cout << endl;
}

void SLList::sort() {
	// prompt user that list is empty
	if( head == NULL ) {
        cout<<"\n\tList is empty.\n\n";
        return;
    }
    
	int ch;
	
	// ask user which order of sorting will be used
	while (1) {
		cout << "\n\tWhich way would you want to sort the list?" << endl;
		cout << "\t[1] Ascending order" << endl;
		cout << "\t[2] Descending order\n\tChoice: ";
		cin >> ch;
		
		// prevent erroneous inputs
		if ( ch != 1 && ch != 2 ) {
			cout << "\n\tInvalid input.";
			continue;
		}
		
		break;
	}
	
	Node *nextPtr;
	Node *curPtr;
	int tmp;
	
	curPtr = head;
	
	if ( ch == 1 ) {
	// ASCENDING ORDER
	// traverse through the list by comparing each
	// node value to the values of the nodes after it.
		while( curPtr != NULL ) {
			nextPtr = curPtr->next;
			while( nextPtr != NULL ){
				//	 if the current node is greater than the node it is being compared to, swap their values
				if( curPtr->data > nextPtr->data ) {
					tmp = curPtr->data;
					curPtr->data = nextPtr->data;
					nextPtr->data = tmp;
				}
				nextPtr = nextPtr->next;	
			}
			curPtr = curPtr->next;
		}
		
		cout << "\n\tThe list has been sorted in ASCENDING order.\n\n";
	}
	else {
	// DESCENDING ORDER
	// traverse through the list by comparing each
	// node value to the values of the nodes after it.
		while( curPtr != NULL ) {
			nextPtr = curPtr->next;
			while( nextPtr != NULL ) {
				//	 if the current node is lesser than the node it is being compared to, swap their values
				if( curPtr->data < nextPtr->data ) {
					tmp = curPtr->data;
					curPtr->data = nextPtr->data;
					nextPtr->data = tmp;
				}
				nextPtr = nextPtr->next;	
			}
			curPtr = curPtr->next;
		}
		
		cout << "\n\tThe list has been sorted in DESCENDING order.\n\n";	
	}
}

void SLList::deleteList() {
	// prompt user that list is empty
	if( head == NULL ) {
        cout<<"\n\tList is empty.\n\n";
        return;
    }
    
	Node *cur = head;
	Node *next;
	
	// traverse through the list and free each individual node
	while ( cur != NULL ) {  
	    next = cur->next;  
	    delete cur; 
	    cur = next;  
	}  
	      
	// set the head and tail to point to NULL
	head = tail = NULL;
	
	cout << "\n\nThe list has been emptied!\n\n";    
}
