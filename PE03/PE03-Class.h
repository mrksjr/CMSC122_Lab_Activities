#ifndef QUEUE_H
#define QUEUE_H

class Queue{
	public:
		Queue();
		
		void INIT();
		bool EMPTY();
		node* FRONT();
		void ENQUEUE(string, string);
		node* DEQUEUE();
		
	private:
		node *front;
		node *rear;
};

#endif
