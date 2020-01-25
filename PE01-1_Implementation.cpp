// =======================================
// class ArrayList Implementation
// =======================================
ArrayList::ArrayList()
{
	// initialize lastIndex as -1.
	// -1 means that the list does not use any index in list array
	lastIndex = -1;
}

void ArrayList::Menu()
{
	// using an infinite while loop to endlessly run the menu unless the user chooses to terminate the program
	while (1)
	{
		// variable used to store the user's choices
		int select;
		
		cout << "List MENU:\n"
		<< "[1] Add Element\n" 
		<< "[2] Delete Element\n"
		<< "[3] Display List\n" 
		<< "[4] Sort List\n" 
		<< "[5] Delete List\n" 
		<< "[0] Exit Program\n";
		
		cout << "\n\tWhat would you like to do?\n\tChoice: ";
		cin >> select;
		
		// using switch to call the different functions for the program
		switch (select) 
		{
			case 1: AddElement(); break;
			case 2: DeleteElement(); break;
			case 3: DisplayList(); break;
			case 4: SortMenu(); break;
			case 5: DeleteList(); break;
			
			case 0:
				cout << "\n\n\tProgram terminated.\n";
				return; // returns the program flow to the main function, ending the program
			
			default:
				cout << "\tInvalid input.\n\n";
				continue; // reruns the loop to allow user to input a correct choice
		}
	}
}

void ArrayList::AddElement()
{
	// prompt the user that list is full if lastIndex is equal to the last index in the array which is array size - 1
	if(lastIndex == MAXLISTSIZE-1)
	{
		cout << "\n\tError! List is full.\n\n";
		return;
	}
	
	int element;
	cout << "\n\tPlease enter the element to be added: ";
	cin >> element;
	
	while (1)
	{
		int select;
		cout << "\n\tWhere to add the element?" << endl;
		cout << "\t[1] Start of the list" << endl;
		cout << "\t[2] End of the list" << endl;
		cout << "\t[3] Specific position\n\tChoice: ";
		
		cin >> select;
		
		switch (select)
		{
			// select == 1: user chose to add the new element to the Start of the List
			case 1:	
				if(lastIndex == -1) // list is empty
				{
					list[0] = element; // add the element to the index 0
					lastIndex = 0; // set lastIndex to index 0
				}
				else // push existing elements to add new element at index 0
				{
					// starting from the lastIndex, move all 'nodes' until index 0 by one index backward.
					lastIndex++;
					for( int a = lastIndex; a > 0 ; a--)
						list[a] = list[a-1];
					
					// store the element in the first index/index 0 of the array
					list[0] = element;
				}
				
				cout << "\n\tElement " << element << " was added to the start of the list.\n\n";
			break;
			
			// select == 2: user chose to add the new element to the End of the List	
			case 2:
				// increment lastIndex then save the element to the new index
				lastIndex++;
				list[lastIndex] = element;
				
				cout << "\n\tElement " << element << " was added to the end of the list.\n\n";
			break;
				
			case 3:	// Add to a Specific Position
				int position;
				DisplayList(); // display the entire list to make it easier for the user to choose which
								// position to place their new 'node'
				cout << "\tAt which position do you want the element?\n\tChoice: ";
				cin >> position;

//				SORCERY	- the "if" loop
//				if(position < 0)
//				{
//					do{
//						cout << "\n\tInvalid position";
//					}while(position < 0);
//				}

				if (position < 0 || position > lastIndex) // chosen position in out of list bounds
				{
					list[++lastIndex] = element;
					position = lastIndex;
					cout << "\n\tChosen position does not exist. Element is added to the end of the list instead.";
				}
				else // chosen position is valid
				{
					lastIndex++;
					for(int a = lastIndex; a > position ; a--) // push elements after the chosen position
						list[a] = list[a-1];

					list[position] = element;
				}
				
				cout << "\n\tElement " << element << " was added to position " << position << ".\n\n";
			break;
			
			default:
				cout << "\tInvalid input.\n\n";
				continue;
		}
		
		break;
	}
}

void ArrayList::DeleteElement() {
	// prompt the user that list is empty since lastIndex does not point to an existing index (-1)
	if (lastIndex == -1)
	{
		cout << "\n\tList is empty!\n\n";
		return;
	}
	
	int position; // stores the position/index of the node to be deleted
	int count = 0; // stores the frequency of the target element in the list
	int element; // stores the value of the node to be deleted
	
	// prompt user input
	cout << "\n\tEnter the element to be deleted: ";
	cin >> element;
	
	// scan through the list to determine the frequency of the target node
	for(int a = 0; a <= lastIndex; a++)
	{
		if(list[a] == element)
			count++;
	}
	
	if(count == 1) // If element is unique, delete it right away
	{
		// run through the list again to find and delete target element
		for(int a = 0; a <= lastIndex; a++)
		{
			// if the element if found, store its position/index and break the loop
			if(list[a] == element)
			{
				position = a;
				break;
			}
		}
		
		// shift all the elements to fill the 'empty' index left by the deleted 'node'
		for(int a = position; a < lastIndex; a++)
			list[a] = list[a+1];
		
		// decrement lastIndex since one 'node' was removed
		lastIndex--;

		cout << "\n\tThe element " << element << ", which is at position " << position << ", has been deleted.\n\n";
	}
	else if(count > 1) // If there are multiple instances of the element
	{
		cout << "\n\tThe element " << element << " occurs at the following positions: ";
		
		// create a temporary array with size equal to frequency of the chosen element
		int temp[count] = {-1};
		int p = 0; // used to determine the index of an index in the temp array. indexception.
		
		// run through the array list and save the positions of the chosen element to a temp array
		for(int a = 0; a <= lastIndex; a++) 
		{
			// if a match is found, print it and save its index to the temp array then increment p.
			if(list[a] == element)
			{
				cout << a << " ";
				temp[p++] = a;
			}
		}
		
		// ask user to choose which instance of the target value will be deleted
		while (1)
		{
			cout << "\n\tWhich position to delete?\n\tChoice: ";
			cin >> position;
			
			int valid = 0;
			
			// check if chosen position is in the temp array
			for (int a = 0; a <= p; a++)
				if (position == temp[a])
					valid = 1;
			
			// prevent erroneous or invalid choices
			if (!valid)
			{
				cout << "\n\tInvalid input.";
				continue;
			}
			
			break;
		}
		
		// shift the elements after the deleted element
		for(int a = position; a < lastIndex; a++)
			list[a] = list[a+1];
		// reduce lastIndex since a 'node' was removed	
		lastIndex--;
		
		cout << "\n\tThe element " << element << ", which is at position " << position <<  " has been deleted.\n\n";	
	}
	else // prompt user that element was not found
		cout << "\n\tThe list contains no such element.\n\n";
}

void ArrayList::DisplayList() const
{
	// prompt user that list is empty if lastIndex doesn't 'point' to an index in the list array
	if(lastIndex == -1)
    cout<<"\n\tList is empty.\n\n";
	else
	{
		// traverse through the list and print the elements one by one
		cout << "\n\tList elements:" << endl;
		for(int a = 0; a <= lastIndex; a++)
		{
			cout << "\t[" << a << "] " << list[a] << endl;;
		}
		
		cout << endl;
	}
}

void ArrayList::SortMenu()
{
	// prompt user that list is empty
	if (lastIndex == -1) {
		cout << "\n\tList is empty!\n\n";
		return;
	}
	
	while (1)
	{
		// ask user which order of sorting will be done
		int select;
		cout << "\n\tWhich way would you want to sort the list?" << endl;
		cout << "\t[1] Ascending order" << endl;
		cout << "\t[2] Descending order\n\tChoice: ";
		cin>> select;
		
		switch (select)
		{
			case 1: Ascending(); break;
			case 2: Descending(); break;
			
			// prevent erroneous/invalid inputs
			default:
				cout << "\tInvalid input.\n\n";
				continue;
		}
		
		// output ASCENDING or DESCENDING depending on user's choice
		cout << "\n\tThe list has been sorted in " << ( select == 1 ? "A" : "DE" ) << "SCENDING order.\n\n";
		break;
	}
}

void ArrayList::Ascending()
{
	// sorts the list in ascending order
	// traverse through the list and compares each value
	// to the other values after it.
	
	// if the current value in the parent loop is greater than the value it is compared to, they will be swapped.
	for(int a = 0; a < lastIndex; a++)
	{
		for(int b = a+1; b <= lastIndex; b++)
		{
			if(list[a] > list[b])
			{
                int temp =  list[a];
                list[a] = list[b];
                list[b] = temp;
            }
		}
	}
}

void ArrayList::Descending()
{
	// sorts the list in descending order
	// traverse through the list and compares each value
	// to the other values after it.
	
	// if the current value in the parent loop is lesser than the value it is compared to, they will be swapped.
	for(int a = 0; a <= lastIndex; a++)
	{
		for(int b = a+1; b <= lastIndex; b++)
		{
			if(list[a] < list[b])
			{
                int temp =  list[a];
                list[a] = list[b];
                list[b] = temp;
            }
		}
	}
}

void ArrayList::DeleteList()
{
	// prompt user that list is empty
	if(lastIndex == -1)
		cout << "\n\tList is empty!\n\n";
	else
	{
		// simply set the lastIndex to -1
		
		// setting the list values to 0 can still be done but it will occupy space like
		// the uninitialized or unoccupied indices of the list/array with dummy/random values
		lastIndex = -1;
		
		cout << "\n\tThe list has been emptied!\n\n";
	}
}
