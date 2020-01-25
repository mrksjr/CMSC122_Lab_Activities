#ifndef TREE_H
#define TREE_H

struct node {
	int data; // stores the value of the node
	int count; // stores the count/instances of the node
	
	node* left; // stores the left child of the node
	node* right; // stores the right child of the node
};

class tree {
	// member functions
	public:
		tree();
		
		node* insertNode( node*, int );
			node* newNode( int );
		node* deleteNode( node*, int );
		node* search( node*, int );
		node* findMax( node* );
		node* findMin( node* );
		node* findSucc( node* );
		node* findPred( node* );
		void display( int );
			void preOrder();
			void inOrder();
			void postOrder();
		
		// member variables
		node* ROOT; // stores the root of the tree
};

#endif
