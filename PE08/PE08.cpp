/*
	Authors :
		Dela Cruz, Jessa
		Limpag, Hanna Mae
		Sijera, Mark Andrae
	
	This program is tasked to build a minimum spanning tree using using Kruskal's Algorithm
*/
#include <iostream>
#include <algorithm> // for sort
#include <fstream> // for file handling
#include <vector> // for vector
using namespace std;

struct edge {
	int src; // aka node 1
	int dst; // aka node 2
	int cost; // cost of edge
	
	// constructor for the edge	
	edge( int s, int d, int c ) {
		src = s;
		dst = d;
		cost = c;
	}
};

struct subset {
	int parent;
	int rank;
};

// function declarations
void loadFile( string&, int* );
	int getNodeCount( ifstream&, int );
	
int buildMST( vector<edge>, int*, int, vector<edge>& );
	bool compEdge( edge, edge );
	int findSet( vector<subset>&, int );
	void unionSet( vector<subset>&, int, int );

void displayMST( vector<edge>, int );

int main() {
	// essential variables
	ifstream FILE; // file containing graph information
	string fileName; // stores the target file's name in
	vector<edge> edgeVect; // vector comprising of the edges in the graph - each contains two 'nodes' and the edge cost
	vector<edge> MST; // output of Kruskal's algorithm
	int mstCost = 0; // total cost of the MST created by the program
	int nodeCount = 0; // number of nodes in the 
	bool determine; // boolean to determine if an MST has been created for current file
	
	while( 1 ) {
		cout << "Minimum Spanning Tree Solver Using Kruskal's Algorithm\n";
		cout << "[1] Load graph\n";
		cout << "[2] Build MST\n";
		cout << "[3] Display MST\n";
		cout << "[0] Exit\n\nChoice: ";
		
		int c;
		cin >> c;

		switch( c ) {
			case 1: {
				// function to open file
				loadFile( fileName, &nodeCount );	
				
				// if user chose not to load file, the program proceeds to reiterate loop
				if ( fileName == "" ) continue;		 
				FILE.open( fileName.c_str() );
				if ( FILE.is_open() ) {
					cout << "\n\tFile \"" << fileName << "\" successfully opened.\n\n";
					
					// get how many edges
					int e;
					FILE >> e;
					
					// counting the number of nodes of the loaded graph
					// if the file is not a predetermined graph, the program will scan the file
					if ( nodeCount == 0 )				
						nodeCount = getNodeCount( FILE, e ); 
					
					// display graph information
					cout << "\tNumber of vertices: " << nodeCount;
					cout << "\n\tNumber of edges: " << e << "\n\n";
					
					// clear edge vector
					edgeVect.clear();
					FILE.seekg( FILE.beg ); // go back to beginning of file
					
					int y, z, w;
					FILE >> y; // pass line with number of edges
					
					// save the edges to a vector
					for ( int i = 0; i < e; i++ ) {
						FILE >> y >> z >> w;
						
						// create new edge and save it to vector
						edge temp( y, z, w );
						edgeVect.push_back( temp );
					}
				} else // if file wasn't found
					cout << "\n\tUnable to open \"" << fileName << "\".\n\n";				
				
				// MST hasn't been built for current graph
				determine = false;
				FILE.close();
			}
			break;
			
			case 2:
				FILE.open( fileName.c_str() );
				
				//if there is no loaded graph
				if ( !FILE.is_open() ) {
					cout << "\n\tNo graph is loaded.\n\n";
					FILE.close();
					continue; // reiterate loop
				}
				
				// if MST isn't built yet
				if ( !determine ) // build MST
					buildMST( edgeVect, &mstCost, nodeCount, MST );
				else {
					cout << "\n\tMST was already built for this graph.\n\n";
					FILE.close();
					continue;
				}
				
				// MST has been built for file
				determine = true;
				FILE.close();
			break;
			
			case 3:
				FILE.open( fileName.c_str() );
				
				// if there is no loaded graph
				if ( !FILE.is_open() ) {
					cout << "\n\tNo graph is loaded.\n\n";
					FILE.close();
					continue; // reiterate loop
				}
				
				// if MST isn't built yet
				if ( !determine )
					cout << "\n\tMST isn't built yet for current graph.\n\n";
				else
					displayMST( MST, mstCost );
				
				FILE.close();
			break;
			
			case 0:
				cout << "\n\tProgram terminated.\n\n";
				return 0;
			
			default:
				cout << "\n\tInvalid input.\n\n";
				continue;
		}
	}
	
	return 0;
}

//function to choose the input file  
void loadFile( string &out, int* n ) {
	// note: files are assumed to follow the same format:
	// 1st line contains number of edges
	// 1st node is 0 and last node is n - 1
	// line 2 to 2 + number of edges contains edge information with v1 v2 cost arranged in order
	// starting node in last line is ignored in kruskal's algorithm
	while( 1 ) {
		cout << "\n\tWhich graph do you want to load?";
		cout << "\n\t[1] Graph 1";
		cout << "\n\t[2] Graph 2";
		cout << "\n\t[3] Input file name ( *.in )";
		cout << "\n\t[0] Cancel\n\n\tChoice: ";
		
		int c;
		cin >> c;
		
		switch( c ) {
			case 1:
				out = "PE08_Graph1.in";
				*n = 10;
			break;
			
			case 2:
				out = "PE08_Graph2.in";
				*n = 6;
			break;
			
			//lets the user to input the file name 
			case 3: {
				*n = 0;
				cout << "\n\tInput name of file to load: ";
				cin >> out;
				
				string s = out.substr( out.length() - 3, out.length() - 1 );
				
				//automatically put a file name extension 
				if ( s != ".in" )
					out += ".in";
				
			break;
			}
			
			case 0:
				out = "";
				cout << "\n\tCancelled.\n\n";
				return;
				
			default:
				cout << "\n\tInvalid input.\n\n";
				continue;
		}
		
		return;
	}
}

// function to get the number of nodes
int getNodeCount( ifstream &f, int e ) {
	int n = 0;
	// read every line in the file e times
	for ( int i = 0; i < e; i++ ) {
		int a, b, w;
		f >> a >> b >> w;
		
		if ( a + 1 > n ) n = a + 1;
		if ( b + 1 > n ) n = b + 1;
	}
	
	return n;
}


int buildMST( vector<edge> edgeList, int *cost, int nodeCount, vector<edge> &MST ) {
	// reset cost
	*cost = 0;
	// clear MST
	MST.clear();
	
	// sort the vector of edges in the graph
	sort( edgeList.begin(), edgeList.end(), compEdge );
	
	// create a vector of subsets and initialize its values ( to be used in checking for cycles in graph )
	vector<subset> subs( nodeCount );
	for ( int i = 0; i < subs.size(); i++ ) {
		subs[i].parent = i;
		subs[i].rank = 0;
	}
	
	int n = 0, i = 0;
	// MST consists of n - 1 edges
	// while number of edges is less than n - 1, and edges are not exhausted yet
	while( n < nodeCount - 1 && i < edgeList.size() ) {
		// check if the 1st node belongs in the same subset as the 2nd node
		int a = findSet( subs, edgeList[i].src );
		int b = findSet( subs, edgeList[i].dst );
		
		// if they aren't in the same subset, that means a cycle isn't formed
		if ( a != b ) {
			// add edge to MST and increment cost then union the sets both nodes belong to
			MST.push_back( edgeList[i] );
			*cost += edgeList[i].cost;
			unionSet( subs, a, b );
			++n;
		}
		
		++i; // move to next edge
	}
	
	cout << "\n\tThe MST has been built.\n\n";
}

// comparator function used to sort the vector of edges by their cost
bool compEdge( edge a, edge b ) {
	return ( a.cost < b.cost );
}

// Union-Find Disjoint Sets ( UFDS ) operations

// find the parent of a vertex
int findSet( vector<subset> &subs, int i ) {
	if ( subs[i].parent != i )
		subs[i].parent = findSet( subs, subs[i].parent );
		
	return subs[i].parent;
}

// perform union operation between two subsets
void unionSet( vector<subset> &subs, int a, int b ) {
	int i = findSet( subs, a );
	int j = findSet( subs, b );
	
	// Attach smaller rank tree under root of high
	// rank tree (Union by Rank)
    if ( subs[i].rank < subs[j].rank )
	    subs[i].parent = j;
    else if ( subs[i].rank > subs[j].rank )
		subs[j].parent = i;
			
	// If ranks are same, then make one as root and
	// increment its rank by one
    else {
		subs[j].parent = i;
		subs[i].rank++;
	}
}

void displayMST( vector<edge> MST, int totalCost ) {
	cout << "\n\tMinimum Spanning Tree: ( Vertices ) - Cost";
	for( int i = 0 ; i < MST.size() ; i++ )
		cout << "\n\t( " << MST[i].src << ", " << MST[i].dst << " ) - " << MST[i].cost;
		
	cout << "\n\n\tTotal cost of MST: " << totalCost << "\n\n";
}
