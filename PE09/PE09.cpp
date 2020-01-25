/*

	PE09 - Sorting
	
	Dela Cruz, Jessa
	Limpag, Hanna Mae
	Sijera, Mark Andrae
	
	A program that implements three specified sorting algorithms and use each to sort
	an array of numbers. The sorting algorithms are SELECTION, MERGE, and RADIX

*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// functions
void inputArray( vector<int>& );
void displayVect( vector<int> );
void getExecTime( clock_t, clock_t );

void selectionSort( vector<int>& );
void mergeSort( vector<int>&, int, int );
	void sortSubarrays( vector<int>&, int, int, int );
void radixSort( vector<int>& );
	int getDigitCount( int, int );

int main() {
	srand( time( NULL ) );
	vector<int> input;
	clock_t start, end;
	
	while ( 1 ) {
		cout << "Sorting Demonstration ( Ascending )";
		cout << "\n[1] Input array";
		cout << "\n[2] Display array";
		cout << "\n[3] Sort: SELECTION";
		cout << "\n[4] Sort: MERGE";
		cout << "\n[5] Sort: RADIX";
		cout << "\n[0] Exit\nChoice: ";
		
		int c;
		cin >> c;
		
		switch ( c ) {
			case 1:
				inputArray( input );
			break;
			
			case 2:
				if ( input.empty() ) {
					cout << "\n\tThe input array is empty!\n\n";
					continue;
				}
				
				cout << "\n\tOriginal input array: ";
				displayVect( input );
				cout << "\n\n";
			break;
			
			case 3: {
				if ( input.empty() ) {
					cout << "\n\tThe input array is empty!\n\n";
					continue;
				}
				
				cout << "\n\tSelection Sort\n\n\t";
				displayVect( input );
				cout << "\n\n";
				
				vector<int> selectionCopy = input;
				start = clock();
				selectionSort( selectionCopy );
				end = clock();
				
				cout << "\n\tSorted array: ";
				displayVect( selectionCopy );
				
				getExecTime( start, end );
				
				cout << "\n\n";
				break;
			}
			
			case 4: {
				if ( input.empty() ) {
					cout << "\n\tThe input array is empty!\n\n";
					continue;
				}
				
				cout << "\n\tMerge Sort\n\n\t";
				displayVect( input );
				cout << "\n\n";
				
				vector<int> mergeCopy = input;
				start = clock();
				mergeSort( mergeCopy, 0, mergeCopy.size() - 1 );
				end = clock();
				
				cout << "\tSorted array: ";
				displayVect( mergeCopy );
				
				getExecTime( start, end );
				
				cout << "\n\n";
				break;
			}
			
			case 5: {
				if ( input.empty() ) {
					cout << "\n\tThe input array is empty!\n\n";
					continue;
				}
				
				cout << "\n\tRadix Sort\n\n\t";
				displayVect( input );
				cout << "\n\n";
				
				vector<int> radixCopy = input;
				start = clock();
				radixSort( radixCopy );
				end = clock();
				
				cout << "\tSorted array: ";
				displayVect( radixCopy );
				
				getExecTime( start, end );
				
				cout << "\n\n";
				break;
			}
			
			case 0:
				cout << "\n\tProgram terminated.\n";
				return 0;
			break;
			
			default:
				cout << "\n\tInvalid input.\n\n";
				continue;
			break;
		}
	}
	
	return 0;
}

void inputArray( vector<int> &vect ) {
	vect.clear();
	
	int c;
	while ( 1 ) {
		cout << "\n\tHow many elements do you want in the array?";
		cout << "\n\t( Negative number to generate N random inputs )\n\tN = ";
		cin >> c;
		
		if ( c == 0 ) {
			cout << "\n\tNumber of elements cannot be zero.\n";
			continue;
		}
		
		break;
	}
	
	int n;
	if ( c > 0 ) {
		cout << "\n\tInput the numbers:\n";
		for ( int i = 0; i < c; ++i ) {
			cout << "\t[" << i << "] >> ";
			cin >> n;
			vect.push_back( n );
		}
	} else {
		c = -c;
		cout << "\n\t" << c << " random inputs were generated.\n";
		for ( int i = 0; i < c; ++i ) {
			n = ( rand() % 1000 );
			if ( rand() % 2 ) n = -n;
			vect.push_back( n );
		}
	}
	
	cout << "\n\tInputs complete.\n\n";
}

void displayVect( vector<int> vect ) {
	int n = vect.size();
	for ( int i = 0; i < n; ++i )
		cout << vect[i] << " ";
}

void getExecTime( clock_t c1, clock_t c2 ) {
	double e = (double)( c2 - c1 ) / (double)1000 ;
	cout << "\n\tExecution time: " << e << "s";
}

void selectionSort( vector<int> &vect ) {
	int n = vect.size();
	int sortedSize = n - 1;
	int min;
	
	for ( int i = 0 ; i < sortedSize ; ++i ) {
		// set number at current index as mininmum
		int min = vect[i];
		int pos = i;
		
		// traverse through the unsorted portion of the array to find the smallest number
		for ( int j = i + 1 ; j < n ; ++j ) {
			if ( min > vect[j] ) {
				min = vect[j];
			//save the position value of min to be used for swapping
				pos = j;
			}
		}
		
		// swap number at current index and new min
		if ( vect[i] != vect[pos] ) {
			int temp;
			temp = vect[i];
			vect[i] = vect[pos];
			vect[pos] = temp;
			
			cout << "\t";
			for ( int j = 0; j < vect.size(); ++j ) {
				if ( j == i || j == pos )
					cout << "[" << vect[j] << "] ";
				else
					cout << vect[j] << " ";
			}
			cout << endl;
		}
	}//end of 1st for loop
}

void mergeSort( vector<int> &vect, int L, int R ) {
	if ( R > L ) {
		int m = ( L + R ) / 2;
		
		mergeSort( vect, L, m ); // right sub-array
		mergeSort( vect, m + 1, R );// left sub-array
		sortSubarrays( vect, L, m, R );
		
		cout << "\t";
		displayVect( vect );
		cout << "\n\n";
	}
}

void sortSubarrays( vector<int> &vect, int L, int m, int R ) {
	vector<int> left, right;
	
	for ( int i = L; i <= m; ++i )
		left.push_back( vect[i] );
	
	cout << "\tLeft: ";
	displayVect( left );
	cout << "\n";
		
	for ( int i = m + 1; i <= R; ++i )
		right.push_back( vect[i] );
		
	cout << "\tRight: ";
	displayVect( right );
	cout << "\n";
	
	int a = left.size();
	int b = right.size();
	int i = L, j = 0, k = 0;
	while ( j < a && k < b ) {
		if ( left[j] <= right[k] )
			vect[i++] = left[j++];
		else
			vect[i++] = right[k++];
	}
	
	while ( j < a )
		vect[i++] = left[j++];
		
	while ( k < b )
		vect[i++] = right[k++];
		
}

void radixSort( vector<int> &vect ) {
	vector< vector<int> > radix( 10, vector<int>() );
	int n = vect.size();
	
	// get number of digits from the max and min values
	int max = vect[0];
	int min = max;
	for ( int i = 0; i < n; ++i ) {
		if ( max < vect[i] ) max = vect[i];
		if ( min > vect[i] ) min = vect[i];
	}
	
	int digitCount = getDigitCount( min, max );
	
	// get every digit of every number and place them in the corresponding radix
	int div = 1; // start at ones value
	int radixSize = 10;
	for ( int i = 0; i <= digitCount; ++i ) { // add one last pass to sort numbers by their sign
		for ( int j = 0; j < n; ++j ) {
			int digit = vect[j];
			if ( i < digitCount ) { // passes 0 to ( digitCount - 1 )
				// remove the processed digits from the number by dividing it with the divisor
				if ( vect[j] < 0 ) // negate negative numbers
					digit = -digit / div;
				else
					digit /= div;
				radix[digit % 10].push_back( vect[j] );
			} else { // last pass
				// reduce iteration count when adding radix elements to vect
				radixSize = 2;
				if ( digit < 0 )
					radix[0].push_back( vect[j] );
				else
					radix[1].push_back( vect[j] ); 
			}
		}
		
		// add partially sorted elements back to vect
		vect.clear();
		for ( int j = 0; j < radixSize; ++j ) {
			vector<int>::iterator k = radix[j].begin();
			int l = 0;
			// while end of radix is not reached
			while ( k != radix[j].end() ) {
				if ( radixSize == 10 || radix[j][l] >= 0 ) // add to end of vect
					vect.push_back( radix[j][l] );
				else if ( radix[j][l] < 0 ) // insert at beginning of vect if negative
					vect.insert( vect.begin(), radix[j][l] );
				
				++l;
				++k;
			}
		}
		
		// print then reset radix subarrays
		cout << "\tPass " << i + 1 << "\n";
		for ( int j = 0; j < radixSize; ++j ) {
			cout << "\t[" << j << "] ";
			displayVect( radix[j] );
			cout << "\n";
			radix[j].clear();
		}
		div *= 10; // increase divisor to evaluate digit to the left of current digit in next iteration
		
		cout << "\n\t";
		displayVect( vect );
		cout << "\n\n";
	}
}

int getDigitCount( int a, int b ) {
	if ( a < 0 ) a = -a;
	if ( b < 0 ) b = -b;
	
	int max = a;
	if ( a < b ) max = b;
	
	int i = 0;
	do {
		max /= 10;
		i++;
	} while ( max > 0 );
		
	return i;
}
