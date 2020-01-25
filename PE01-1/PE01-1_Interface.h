#ifndef ARRAYLIST_H
#define ARRAYLIST_H

// declaration of class member functions and member variables
class ArrayList{
	public:
		ArrayList();
		void Menu();
		
		void AddElement();
		void DeleteElement();
		void DisplayList() const;
		void SortMenu();
			void Ascending();
			void Descending();
		void DeleteList();
			
	private:
		int list[MAXLISTSIZE];
			// integer array list contains the array of integers
		int lastIndex;
			// lastIndex marks the last index of a 'node' in the list/array.
		
};

#endif
