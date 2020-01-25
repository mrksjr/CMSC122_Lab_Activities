tree::tree() {
	// initialize ROOT node as null since tree is empty
	ROOT = NULL;
}
		
node* tree::insertNode( node* node, int x ) {
	// if ROOT is null/tree is empty, create a new node and set it as root
	if ( ROOT == NULL ) {
		ROOT = newNode( x );
		
		cout << "\n\tThe value " << ROOT->data << " is the ROOT of the tree.\n\n";
		return ROOT;
	}
	
	// if node is a non-root empty node, create a new node for it
	if ( node == NULL ) {
		node = newNode( x );
		
		cout << "\n\tThe value " << node->data << " has been added to the tree. Count: " << node->count << "\n\n";	
		return node;
	}
	
	// if value already exists in the tree, increase its count
	if ( node->data == x ) {
		node->count++;
		cout << "\n\tThe value " << node->data << " has a duplicate in the tree. Count: " << node->count << "\n\n";
	}
	// for these two conditions, recur through the tree to find where to insert the node
	// if value is less than current node, recur to the left child, otherwise to the right child
	else if ( x < node->data )
		node->left = insertNode( node->left, x );
	else if ( x > node->data )
		node->right = insertNode( node->right, x );
			
	return node;
}

node* tree::newNode( int x ) {
	// allocate space for new node
	node* newNode = new node;
		
	// initialize node data
	newNode->data = x;
	newNode->count = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

node* tree::deleteNode( node* root, int target ) {
	// base case: root is null OR target does not exist in the tree
	if ( root == NULL || search( root, target ) == NULL ) {
		return root;
	}
	
	// if the target is smaller than the root's value, then it lies in the left subtree
	if ( target < root->data )
		root->left = deleteNode( root->left, target );
	// if the target is smaller than the root's value, then it lies in the right subtree
	else if ( target > root->data )
		root->right = deleteNode( root->right, target );
	// if the target is equal to the root, then delete
	else {
		// if there is more than 1 instance of the node, decrement its count
		if ( root->count > 1 ) {
			root->count--;
		}
		else {
			// node with only one or no child
			if ( root->left == NULL ) {
				node* temp = root->right;
				
				if ( root == ROOT )
					ROOT = root->right;
									
				delete root;
				return temp;
			} else if ( root->right == NULL ) {
				node* temp = root->left;				
	
				if ( root == ROOT )
					ROOT = root->left;
				
				delete root;
				return temp;
			} else {
				// node with two children - get the successor
				node* temp = findMin( root->right );
				// copy the successor's content to the current node
				root->data = temp->data;
				// delete the successor
				root->right = deleteNode( root->right, temp->data );

			}
		}
	}
	
	return root;
}

node* tree::search( node* root, int target ) {
	// base case: root is null or target is at root
	if ( root == NULL || root->data == target )
		return root;
		
	// target is greater than root value
	if ( root->data < target )
		return search( root->right, target );
	
	// target is less than root value
	return search( root->left, target );
}

node* tree::findMax( node* root ) {
	node* temp = root;
	
	// root is null
	if ( temp == NULL )
		return NULL;
	else {
		// traverse to the rightmost node in the tree
		while ( temp->right != NULL )
			temp = temp->right;
		
		return temp;
	}
}

node* tree::findMin( node* root ) {
	node* temp = root;
	
	// root is null
	if ( temp == NULL )
		return NULL;
	else {
		// traverse to the leftmost node in the tree
		while ( temp->left != NULL )
			temp = temp->left;
		
		return temp;
	}
}

node* tree::findSucc( node* root ) {
	node* temp = root->right;
	
	// find the minimum of the root's right subtree
	return findMin( temp );
}

node* tree::findPred( node* root ) {
	node* temp = root->left;
	
	// find the maximum of the root's left subtree
	return findMax( temp );
}

void tree::preOrder() {
	// ROOT -> LEFT -> RIGHT
	
	// create empty stack and push root to it
	stack<node*> nodeStack;
	nodeStack.push( ROOT );
	
	// pop all items one by one
	while ( nodeStack.empty() == false ) {
		// print the value
		node* top = nodeStack.top();
		cout << top->data << " ";
		nodeStack.pop();
		
		//	push its right child
		if ( top->right )
			nodeStack.push( top->right );
		//	push its left child
		if ( top->left )
			nodeStack.push( top->left );
		// right child is pushed first so that the left is processed first since this is a stack
	}
	
	cout << "\n";
}

void tree::inOrder() {
	// RIGHT -> ROOT -> LEFT
	
	// create empty stack and push root to it
	stack<node*> nodeStack;
	node* temp = ROOT;
	
	// while stack isn't empty or temp is not null
	while ( temp != NULL || nodeStack.empty() == false ) {
		// go to the leftmost node in the subtree of the current node
		while ( temp ) {
			nodeStack.push( temp );
			temp = temp->left;
		}
		
		// pop the top of the stack and print it
		temp = nodeStack.top();
		nodeStack.pop();
	
		cout << temp->data << " ";
		
		// go to the right child of the current node
		temp = temp->right;
	}
	
	cout << "\n";
}

void tree::postOrder() {
	// LEFT -> RIGHT -> ROOT
	
	// create 2 stacks and push root to the 1st stack
	// the 2nd stack will be used to print the postorder result
	stack<node*> stack1, stack2;
	stack1.push( ROOT );
	
	node* temp;
	
	// while 1st stack isn't empty
	while ( !stack1.empty() ) {
		// pop it from 1st stack and push it to 2nd stack
 		temp = stack1.top();
 		stack1.pop();
 		stack2.push( temp );
 		
 		// if node has a left child, push it to 1st stack
 		if ( temp->left )
 			stack1.push( temp->left );
 		// if node has a right child, push it to 1st stack
 		if ( temp->right )
 			stack1.push( temp->right );
	}
	
	// while 2nd stack isnt empty, pop and print every node in it
	while ( !stack2.empty() ) {
		temp = stack2.top();
		stack2.pop();
	
		cout << temp->data << " ";
	}
	
	cout << "\n";
}
