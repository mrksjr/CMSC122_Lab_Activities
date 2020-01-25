#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

#define MSIZE 269
#define INF numeric_limits<float>::max()
using namespace std;

struct segment {
	float weight;
	string label;
	
	segment( float w, string str ) {
		weight = w;
		label = str;
	}
};

typedef vector< vector< segment > > MATRIX;

void buildMatrixFromFile( MATRIX& );
int getStartingNode( MATRIX& );

float dijkstra( MATRIX, vector<float>&, vector<int>&, int, int );
	int getMinDistance( vector<bool>, vector<float> );
	void displayPath( MATRIX, vector<int>, int, int );
void computeTaxiFare( float );

int main() {
	MATRIX M( MSIZE, vector<segment>( MSIZE, segment( INF, "" ) ) );
	vector<float> WEIGHT;
	vector<int> PATH;
	
	buildMatrixFromFile( M );
	
	int previousStart = -1;
	float totalDistance;
	
	while ( 1 ) {
		cout << "Please input your starting location:";
		int vertexA = getStartingNode( M );
		
		cout << "\nPlease input your destination:";
		int vertexB = getStartingNode( M );
		
		if ( previousStart != vertexA )
			totalDistance = dijkstra( M, WEIGHT, PATH, vertexA, vertexB );
		else
			totalDistance = WEIGHT[vertexB];
			
		displayPath( M, PATH, vertexA, vertexB );
		computeTaxiFare( totalDistance );
		
		previousStart = vertexA;
		
		cout << "\n\nWould you like to use the program again? (Y/N)\n";
		cout << "Choice: ";
		string c;
		cin >> c;
		
		if ( c == "Y" || c == "y" ) {
			cout << "\n\n";
			continue;
		}
		else if ( c == "N" || c == "n" )
			cout << "\n\tThank you for your patronage.";
		else
			cout << "\n\tInvalid input. Terminating.";
		
		break;
	}
	
	return 0;
}

void buildMatrixFromFile( MATRIX &M ) {
	ifstream FILE;
	FILE.open( "PE_Bonus_RoadNetwork.in" );
	
	int a, b;
	float w;
	string str;
	int max = 0;
	while ( !FILE.eof() ) {
		FILE >> a >> b >> w >> str;
		
		--a; --b; // reduce node numbers by 1 to be used as vector indices (starts at 0)

		segment S( w, str );
		M[a][b] = M[b][a] = S;
	}

	FILE.close();
}

int getStartingNode( MATRIX &M ) {
	int n = M.size();
	
	while ( 1 ) {
		cout << "\n\t> ";
		string s;
		cin >> s;
		
		for ( int i = 0; i < n; ++i ) {
			for ( int j = 0; j < n; ++j ) {
				if ( s == M[i][j].label )
					return i;
			}
		}
		
		cout << "\tLocation was not found; please input again.\n";
	}
}


float dijkstra( MATRIX M, vector<float> &dist, vector<int> &PATH, int a, int b ) {
	PATH.clear(), dist.clear();
	PATH.resize( MSIZE, -1 );
	dist.resize( MSIZE, INF );
	
	vector<bool> visited( MSIZE, false );
	
	if ( a > b ) swap( a, b ); // swap values of a and b if a is larger than b
	dist[a] = 0; // set distance of vertex A to itself to 0
	PATH[a] = -1; // set path to vertex A as 0
	
	for ( int c = 0; c < MSIZE - 1; ++c ) {
		int min = getMinDistance( visited, dist );
		
		visited[min] = true;
		for ( int i = 0; i < MSIZE; ++i ) {
			// vertex isn't visited
			// edge between current vertex and the adjacent vertex is not INF
			// distance of adjacent vertex to vertex A is not INF
			// distance from vertex A to adjacent vertex through the current vertex is smaller than
			//	the distance from vertex A to adjacent vertex
			if ( !visited[i] && M[min][i].weight <= INF && dist[min] <= INF && dist[min] + M[min][i].weight < dist[i] ) {
				PATH[i] = min; // set the current vertex as the path to this adjacent vertex
				dist[i]	= dist[min] + M[min][i].weight;
			}
		}
	}
	
	return dist[b]; // return weight of shortest path from vertex A to vertex B
}

int getMinDistance( vector<bool> vis, vector<float> dist ) {
	float min = INF;
	int index;
	
	for ( int i = 0; i < MSIZE; ++i ) {
		if ( !vis[i] && dist[i] <= min )
			min = dist[i], index = i;
	}
	
	return index;
}

void displayPath( MATRIX M, vector<int> P, int a, int b ) {
	bool noSwap = true;
	if ( a > b ) {
		swap( a, b ), noSwap = false;
	}
	
	vector<int> directPath;
	int x = b;
	while ( x != -1 ) {
		if ( noSwap ) // if a < b, add paths in reverse
			directPath.insert( directPath.begin(), x );
		else // add paths in order
			directPath.push_back( x );
			
		x = P[x];
	}
	
	int n = directPath.size() - 1;
	cout << "\n\tPath taken by taxi (/segments traversed):";
	for ( int i = 0; i < n; ++i ) {
		// get 2 vertices from path
		int vertexA = directPath[i];
		int vertexB = directPath[i + 1];
		
		if ( i % 3 == 0 ) cout << "\n\t";
		
		cout << setw(25) << left << M[vertexA][vertexB].label;
		if ( i < n - 1) cout << " -> ";
	}
	cout << "\n\n";
}

void computeTaxiFare( float distanceTravelled ) {
	int travelSpeed = 40;
	int flagdown = 40;
	float farePerMin = 2.5;
	int farePerKm = 13;
	float travelTime = ( distanceTravelled / travelSpeed ) * 60; // convert travel time in hours to minutes
	
	cout << "\tDistance travelled: " << fixed << setprecision(2) << distanceTravelled << " km";
	cout << "\n\tTravel time: " << travelTime << " minutes";
	
	// fractional part is discarded only in distance travelled
	float fare = flagdown + ( farePerKm * (int)distanceTravelled ) + ( farePerMin * travelTime );
	cout << "\n\tTotal Fare: P" << fare;
}
