Queue::Queue() {
	// call initialization function for queue
	INIT();
}

void Queue::INIT() {
	// initialize front and rear pointers
	front = NULL;
	rear = NULL;
}

bool Queue::EMPTY() {
	return front == NULL;
}

node* Queue::FRONT() {
	return front;
}

void  Queue::ENQUEUE(string o, string n) {
	// create new node
	node* temp = new node;
	temp->name = n;
	temp->order = o;
	temp->next = NULL;
	
	// set new node as front and rear if queue is empty
	if( EMPTY() ) {
		rear = temp;
		front = temp;
		return;
	}
	
	// else add new node at end of list
	rear->next = temp;
	rear = temp;
}

node* Queue::DEQUEUE() {
	// return NULL if queue is empty
	if( EMPTY() )
		return NULL;
	
	// create a copy of FRONT node
	node* temp = new node;
	temp->next = front->next;
	temp->order = front->order;
	temp->name = front->name;
	
	// create a pointer to hold current front
	node* temp2 = front;
	// set new front
	front = front->next;
	
	// delete previous front and return copy
	delete temp2;
	return temp;
}
