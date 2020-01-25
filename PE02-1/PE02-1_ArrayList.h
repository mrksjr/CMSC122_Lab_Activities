#ifndef ARRAYLIST_H
#define ARRAYLIST_H

// declaration of class member functions and member variables
class ArrayList{
	public:
		ArrayList();
		void Menu();
		
		void AddElement( string x );
		void DeleteElement();
			
		string list[MAXLISTSIZE];
		int lastIndex;
};

#endif
