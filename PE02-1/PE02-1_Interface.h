#ifndef SLLIST_H
#define SLLIST_H

// declaration of class member functions and member variables
class stack {
	public:
		stack();
		
		void menu();
		void add(); // add kitchenware	
		void wash(); // wash kitchenware
		void getTop();
		void washAll();
			
		void PUSH( string x );
		string POP();
		string TOP();
		bool FULL();
		bool EMPTY();
		void MAKENULL();
		
	private:
		ArrayList arrlist;
		int listSize;
		int maxSize;
};

#endif
