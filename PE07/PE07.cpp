/* LAB Programming Exercise 7 - Graph Traversal
	Submitted by: MARK ANDRAE A. SIJERA
	
	- this program performs Depth-First Search (DFS) and Breadth-First Search (BFS) on
	predefined graphs.
*/
#include <iostream>
#include <queue> // for queue
#include <vector> // for vector

using namespace std;

typedef vector< vector<int> > GRAPH; // use GRAPH as alias for 2d vector

// functions
void connect( GRAPH&, int, int ); // function to 'connect' nodes of the graph
void completeDFS( int, string, int, int[], GRAPH ); // func to perform DFS on selected graph
void completeBFS( int, string, int, int[], GRAPH ); // BFS on selected graph
bool targetDFS( char, int, string, int, int[], GRAPH, bool* ); // perform DFS on graph until target char is reached
bool targetBFS( char, int, string, int, int[], GRAPH ); // perform BFS on graph until target char is reached
	
int main() {
	// initialize graphs
	/*
		graphs are represented as 2d vectors/adjacency matrices
		
			- first index determines which node it is ( 0 - A, 1 - B, etc)
			- second index represents its connections with other nodes
	*/
	
	// graph 1
	// create 2d 8x8 vector with all values initialized at 0
	GRAPH A( 8, vector<int>( 8, 0 ) );
	string stringA = "ABCDEFGH"; // string to store character assigned to each node/index
	int sizeA = stringA.length(); // holds number of nodes in graph 1
	// connections between nodes in graph 1 are configured here
	connect(A, 0, 1 ); // A - B
	connect(A, 0, 3 ); // A - D
	connect(A, 0, 6 ); // A - G
	connect(A, 1, 4 ); // B - E
	connect(A, 1, 5 ); // B - F
	connect(A, 2, 5 ); // C - F
	connect(A, 2, 7 ); // C - H
	connect(A, 3, 5 ); // D - F
	connect(A, 4, 6 ); // E - G
	// graph 1 end
	
	// graph 2
	// create 2d 8x8 vector with all values initialized at 0
	GRAPH B( 12, vector<int>( 12, 0 ) );
	string stringB = "abcdefghijkl"; // string to store character assigned to each node/index
	int sizeB =stringB.length(); // holds number of nodes in graph 1
	// connections between nodes in graph 2 are configured here
	connect(B, 0, 2 ); // a - c
	connect(B, 0, 3 ); // a - d
	connect(B, 0, 4 ); // a - e
	connect(B, 0, 5 ); // a - f
	connect(B, 0, 10 ); // a - k
	connect(B, 1, 2 ); // b - c
	connect(B, 2, 3 ); // c - d
	connect(B, 2, 6 ); // c - g
	connect(B, 3, 4 ); // d - e
	connect(B, 3, 7 ); // d - h
	connect(B, 4, 8 ); // e - i
	connect(B, 5, 9 ); // f - j
	connect(B, 6, 7 ); // g - h
	connect(B, 6, 11 ); // g - l
	connect(B, 7, 8 ); // h - i
	connect(B, 8, 9 ); // i - j
	connect(B, 10, 11 ); // k - l
	// graph 2 end
	
	// start program
	while (1) {
		// program menu
		cout << "GRAPH TRAVERSAL MENU\n\n";
		cout << "[1] Perform Depth First Traversal\n";
		cout << "[2] Perform Breadth First Traversal\n";
		cout << "[3] Search Graph using DFS\n";
		cout << "[4] Search Graph using BFS\n";
		cout << "[0] Exit";
		cout << "\n\nChoice: ";
		
		int c;
		cin >> c;
		
		switch( c ) {
			// when user chooses to do complete DFS/BFS on a graph
			case 1: case 2:
				while ( 1 ) {
					// ask user to choose which graph to perform action on
					cout << "\n\tWhich graph do you want to traverse?";
					cout << "\n\t[1] Graph 1";
					cout << "\n\t[2] Graph 2";
					cout << "\n\n\tChoice: ";
					
					int ch;
					cin >> ch;
					
					switch( ch ) {
						case 1: {
							// display 'DFS' or 'BFS' depending on the user's choice in main menu
							cout << "\n\tGraph 1 " << ( ( c == 1 ) ? "D" : "B" ) << "FS: ";
							// create a temporary array that would store the visit states of nodes in graph A
							// 0 - unvisited, 1 - visited
							int visitedA[sizeA] = { 0 };
							
							// do DFS or BFS on graph A depending on user's choice in main menu
							if ( c == 1	) completeDFS( 0, stringA, sizeA, visitedA, A);
							else completeBFS( 0, stringA, sizeA, visitedA, A);
							break;
						}
						
						case 2: {
							// display 'DFS' or 'BFS' depending on the user's choice in main menu
							cout << "\n\tGraph 2 " << ( ( c == 1 ) ? "D" : "B" ) << "FS: ";
							// create a temporary array that would store the visit states of nodes in graph B
							// 0 - unvisited, 1 - visited
							int visitedB[sizeB] = { 0 };
							
							// do DFS or BFS on graph B depending on user's choice in main menu
							if ( c == 1 ) completeDFS( 0, stringB, sizeB, visitedB, B);
							else completeBFS( 0, stringB, sizeB, visitedB, B);
							break;
						}
						
						// prompt user when inputting invalid choice
						default:
							cout << "\n\tInvalid input.\n\n";
							continue;
					}
					
					cout << "\n\n";
					break; // break from infinite loop
				}
			break;
			
			// when user chooses to do DFS/BFS until a target char
			case 3: case 4:
				while ( 1 ) {
					// ask user to choose which graph to perform action on
					cout << "\n\tWhich node do you want to search?";
					cout << "\n\tChoice: ";
				
					char targ;
					cin >> targ;
					
					cout << "\n\tWhich graph do you want to traverse?";
					cout << "\n\t[1] Graph 1";
					cout << "\n\t[2] Graph 2";
					cout << "\n\n\tChoice: ";
					
					int ch;
					cin >> ch;
					
					bool result;
					switch( ch ) {
						case 1: {
							// display 'DFS' or 'BFS' depending on the user's choice in main menu
							cout << "\n\tGraph 1 " << ( ( c == 3 ) ? "D" : "B" ) << "FS search path: ";
							// create a temporary array that would store the visit states of nodes in graph A
							// 0 - unvisited, 1 - visited
							int visitedA[sizeA] = { 0 };
							
							// do DFS/BFS and save the result in variable 'result'
							if ( c == 3 ) {
								// create a temporary boolean that will tell targetDFS when to stop recurring
								bool res = false;
								result = targetDFS( targ, 0, stringA, sizeA, visitedA, A, &res );
							}
							else result = targetBFS( targ, 0, stringA, sizeA, visitedA, A );
							
							// display DFS/BFS result
							if ( result ) cout << "\n\tTarget " << targ << " was found in the graph.";
							else cout << "\n\tTarget " << targ << " was NOT found in the graph.";
							break;
						}
						
						case 2: {
							// display 'DFS' or 'BFS' depending on the user's choice in main menu
							cout << "\n\tGraph 2 " << ( ( c == 3 ) ? "D" : "B" ) << "FS search path: ";
							// create a temporary array that would store the visit states of nodes in graph B
							// 0 - unvisited, 1 - visited
							int visitedB[sizeB] = { 0 };
							
							// do DFS/BFS and save the result in variable 'result'
							if ( c == 3 ) {
								// create a temporary boolean that will tell targetDFS when to stop recurring
								bool res = false;
								result = targetDFS( targ, 0, stringB, sizeB, visitedB, B, &res );
							}
							else result = targetBFS( targ, 0, stringB, sizeB, visitedB, B );
							
							// display DFS/BFS result
							if ( result ) cout << "\n\tTarget " << targ << " was found in the graph.";
							else cout << "\n\tTarget " << targ << " was NOT found in the graph.";
							break;
						}
						
						// prompt user when inputting invalid choice
						default:
							cout << "\n\tInvalid input.\n\n";
							continue;
					}
					
					cout << "\n\n";
					break; // break from infinite loop
				}
			break;
			
			// user chooses to exit
			case 0:
				cout << "\n\tProgram terminated.\n";
				return 0;
			
			// user chooses invalid choice
			default:
				cout << "\n\tInvalid input.\n\n";
				continue;
		}
	}
	
	return 0;
}

// this function is used to easily configure connected nodes in the adjacency matrix
/*
	parameters:
	GRAPH &x - the selected graph
	int a - source node/index
	int b - target node/index
*/
void connect( GRAPH &x, int a, int b ) {
	// set the index and its mirror in the adjacency matrix to 1 ( connected)
	x[a][b] = x[b][a] = 1;
}

// this function performs a complete DFS on the selected graph
/*
	parameters:
	int start - indicates the index to start the DFS on
	string str - string with the character representations of the indices
	int len - the number of elements in the graph/string
	int vis[] - array of the visit states of each node
	GRAPH adj - graph to perform the DFS on
*/
void completeDFS( int start, string str, int len, int vis[], GRAPH adj ) {
	// print the character representation of current index ( 0 - A, 1 - B, etc)
	cout << str[start] << " ";
	// mark the node as visited
	vis[start] = 1;
	
	// search through the adjacency matrix for an unvisited connected node and recur into it
	for ( int i = 0; i < len; i++ )
		if ( adj[start][i] == 1 && vis[i] != 1 )
			completeDFS( i, str, len, vis, adj );
}

// this function performs a complete BFS on the selected graph
/*
	parameters:
	int start - indicates the index to start the BFS on
	string str - string with the character representations of the indices
	int len - the number of elements in the graph/string
	int vis[] - array of the visit states of each node
	GRAPH adj - graph to perform the BFS on
*/
void completeBFS( int start, string str, int len, int vis[], GRAPH adj ) {
	// create a queue and push the current index into it
	queue<int> q;
	q.push( start );
	// mark the current index as visited
	vis[start] = 1;
	
	// while queue is not empty, do the following actions
	while( !q.empty() ) {
		// temporarily store the front of the queue and pop it from the queue
		int top = q.front();
		q.pop();
		
		// print it
		cout << str[top] << " ";
		
		// search through connections of the node until an existing unvisited connection is found
		// if there is, add that node to the queue and mark its index as visited
		for ( int i = 0; i < len; i++ ) {
			if ( adj[top][i] == 1 && !vis[i] ) {
				q.push( i );
				vis[i] = 1;
			}
		}
	}
}

// this function performs a complete BFS on the selected graph
/*
	parameters:
	char c - target character to be searched
	int start - indicates the index to start the BFS on
	string str - string with the character representations of the indices
	int len - the number of elements in the graph/string
	int vis[] - array of the visit states of each node
	GRAPH adj - graph to perform the BFS on
	bool *res - boolean pointer to the variable that tells this function when to stop recurring
*/
bool targetDFS( char c, int start, string str, int len, int vis[], GRAPH adj, bool *res ) {
	// prevent any more recursion from being done if a match is found
	if ( *res ) return true;
	
	// print the character representation of current index ( 0 - A, 1 - B, etc)
	cout << str[start] << " ";
	// mark the node as visited
	vis[start] = 1;
	
	// if a match is found, set res to true and immediately finish function/current recursion
	if ( str[start] == c ) {
		*res = true;
		return res;
	}
	
	// search through the adjacency matrix for an unvisited connected node and recur into it
	for ( int i = 0; i < len; i++ )
		if ( adj[start][i] == 1 && vis[i] != 1 )
			targetDFS( c, i, str, len, vis, adj, res );
	
	// return result of res
	return *res;
}

// this function performs a complete BFS on the selected graph
/*
	parameters:
	char c - target character to be searched
	int start - indicates the index to start the BFS on
	string str - string with the character representations of the indices
	int len - the number of elements in the graph/string
	int vis[] - array of the visit states of each node
	GRAPH adj - graph to perform the BFS on
*/
bool targetBFS( char c, int start, string str, int len, int vis[], GRAPH adj ) {
	// create a queue and push the current index into it
	queue<int> q;
	q.push( start );
	// mark the current index as visited
	vis[start] = 1;
	
	// while queue is not empty, do the following actions
	while( !q.empty() ) {
		// temporarily store the front of the queue and pop it from the queue
		int top = q.front();
		q.pop();
		
		// print it
		cout << str[top] << " ";
		
		// if a match is found, immediate escape the function and tell user of the result
		if ( str[top] == c )
			return true;
		
		// search through connections of the node until an existing unvisited connection is found
		// if there is, add that node to the queue and mark its index as visited
		for ( int i = 0; i < len; i++ ) {
			if ( adj[top][i] == 1 && !vis[i] ) {
				q.push( i );
				vis[i] = 1;
			}
		}
	}
	
	// if the BFS finishes, false is returned: no match was found
	return false;
}
