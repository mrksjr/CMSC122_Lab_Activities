stack::stack() {
	// initialize the class's member variables
	top = NULL;
	listSize = 0; // arrlist has 0 nodes
	maxSize = 5;
}

// =======================================================================
// PROGRAM FUNCTIONS
// =======================================================================

void stack::menu() {
	while(1) {
		int ch; // stores the user's choice when using the menu
        cout << "Kitchen Washing Machine";
        cout << "\n[1] Add Kitchenware\n[2] Wash Kitchenware\n[3] Top Kitchenware\n[4] Wash all\n[0] Exit\n";
       	cout << "\n\tWhat would you like to do?\n\tChoice: ";
		cin >> ch;
        
		// using switch control structure to match the user's choice and the corresponding action
        switch( ch ) {
	        case 1:
				add(); 
			break;
			
	        case 2:
				wash();
			break;
	        
			case 3:
				getTop();
			break;
	        
			case 4:
				washAll();
			break;
	        	
	        case 0:
				cout << "\n\tWashing session ended.\n";
	            return; // return the program flow to the main function, thus ending it
	            
			// prevent erroneous inputs
	        default:
	        	cout << "\n\tInvalid input\n\n";
	        	continue;
        }
    }
}

void stack::add() {
	if ( FULL() ) {
		cout << "\n\tThe STACK is FULL. Cannot add kitchenware\n\n";
		return;
	}
	
	string kw;
	cout << "\n\tWhich kitchenware would you like to be washed?\n\tChoice: ";
	cin >> kw;
	
	PUSH( kw );
	
	listSize++; // increase the size of the stack
	cout << "\n\tKitchenware \"" << kw << "\" was added to the stack.\n\n";
}

void stack::wash() {
	// prompt user that arrlist is empty
    if( EMPTY() ) {
        cout<<"\n\tThe STACK is EMPTY. No more kitchenware to wash.\n\n";
        return;
    }
    
    string s = POP();
	cout << "\n\t" << s << " is being washed\n\n";
	
    listSize--; // reduce stack size since it an item was removed
}

void stack::getTop() {
	if( EMPTY() ) {
        cout<<"\n\tThe STACK is EMPTY. No kitchenware to wash.\n\n";
        return;
    }
    
    string s = TOP();
    cout << "\n\t" << s << " is next to be washed.\n\n";
}

void stack::washAll() {
	if( EMPTY() ) {
        cout<<"\n\tThe STACK is EMPTY. No more kitchenware to wash.\n\n";
        return;
    }
    
    MAKENULL();
    
	cout << "\n\tAll the kitchenware has been washed.\n\n";
}

	
// =======================================================================
// STACK FUNCTIONS
// =======================================================================

void stack::PUSH( string x ) {
	Node* temp = new Node;
	
	temp->data = x;
	temp->next = top;
	top = temp;
}

string stack::POP() {
	Node* temp = top;
	string s = top->data;
	top = top->next;
	
	delete temp;
	
	return s;
}

string stack::TOP() {
	return top->data;
}

bool stack::FULL() {
	return listSize == maxSize;
}

bool stack::EMPTY() {
	return top == NULL;
}
	
void stack::MAKENULL() {
    while ( !EMPTY() ) {
    	wash();
	}
}
