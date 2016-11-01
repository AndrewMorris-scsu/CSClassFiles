#include "Heap.h"
#include <cassert>
using namespace std;

Heap::Heap(vector<int> *myParent, bool Minimize, bool isfromRight ) {
cout << "Starting Heap Constructor" << endl;
	Minimizing = Minimize;
	this->Parent = myParent;
	this->fromRight = isfromRight;
	this->elements = 0;

	cout << ((Minimizing)? "Is minimizing" : "NOT Minimizing" ) << endl;
	cout << "Parent address = " << &myParent << endl;
	cout << "I point to :" << &this->Parent << endl;
	cout << ((this->fromRight)? "From Right" : "From Left") << endl;
}

Heap::~Heap() {
}

int Heap::insertAddSize(int value) {
	bool sorted = false;

	int myRealIndex = 0;
	int parentRealIndex = 0;
	int myRelativeIndex = 0;
	int parentRelativeIndex = 0;

	++elements;
	if(elements > Parent->size() - 2) {
		cout << "VECTOR IS FULL... "; //ERROR
		--elements;
		return -1;
	}

	if(elements == 1) {				//If the heap is empty, initialize
		Parent->at(myRoot) = value;
		return (0);
	} else {
		myRelativeIndex = elements;
		myRealIndex = getIndex(myRelativeIndex);
		Parent->at(myRealIndex) = value;
	}

	while(!sorted) {
		/*
		 * Now that we have inserted the value into the last leaf we must
		 * Percolate the value up the heap.
		 */
		if( myRealIndex == myRoot ) {
			cout << endl << Parent->at(myRealIndex) << " is the new root." << endl;
			sorted = true;
		} else {
			parentRelativeIndex = myRelativeIndex/2;
			if (parentRelativeIndex == 0) {cout << "You fucked up... ";}
			parentRealIndex = getIndex(parentRelativeIndex);

			if( lesserThan(Parent->at(myRealIndex), Parent->at(parentRealIndex)) ) {
				/*swap current value with parent */
				int temp;
				//cout << "Swapping " << Parent->at(myRealIndex) << " with "
				//		<< Parent->at(parentRealIndex) << endl;
				temp = Parent->at(myRealIndex);
				Parent->at(myRealIndex) = Parent->at(parentRealIndex);
				Parent->at(parentRealIndex) = temp;
				//Set myRealtive and Real indices to Parents;
				myRealIndex = parentRealIndex;
				myRelativeIndex = parentRelativeIndex;

			} else {
				sorted = true;
			}
		}
	}
	return 0; //OK
}

//getIndex return the relative index for each heap to the actual index in
//in the vector.
int Heap::getIndex(int index) {
	int realIndex;
	if(fromRight) {
		int lastIndex = myRoot + 1;
		realIndex = lastIndex - index;
	}
	else {
		realIndex = index;
	}
	//cout << "Passed in index =" << index << "\nOutput Index =" << realIndex << endl;
    if(realIndex < 0 || realIndex > Parent->size()-2) {
        cout << "ILLEGAL INDEX RETURNED BY getIndex...\n";
    }
	return realIndex;
}

int Heap::pop() {

	int rootVal;
	int myRealIndex, myRelativeIndex;
	int leftChildRelative, rightChildRelative, leftReal, rightReal;

	bool comments = false;

	bool sorted = false;
	if (elements == 0) {
		return -1;
	}

	rootVal = Parent->at(myRoot);//capture root value to return to user.
	if (comments) { cout << "The root value is " << rootValue() << endl; }
	Parent->at(myRoot) = Parent->at(getIndex(elements));
	if (comments) { cout << "Inserting " << Parent->at(getIndex(elements)) << " as the root\n"; }
	Parent->at(getIndex(elements)) = -1;

	--elements;                    //Decrease size of heap
	if (elements == 0) {
		return rootVal;
	}

	myRealIndex = myRoot;

	myRelativeIndex = 1; // Root.
	assert(getIndex(1) == myRoot);

	leftChildRelative = myRelativeIndex * 2;
	rightChildRelative = myRelativeIndex * 2 + 1;

	leftReal = getIndex(leftChildRelative);
	rightReal = getIndex(rightChildRelative);

	if(comments) {
	cout << "My Real Index is :" << myRealIndex << endl;
	cout << "My Relative Index is :" << myRelativeIndex << endl;
	cout << "My Left Child Relative index is :" << leftChildRelative << endl;
	cout << "My Right Child Relative index is :" << rightChildRelative << endl;
	cout << "Left child real index is:" << leftReal << endl;
	cout << "Right child real index is:" << rightReal << endl;
	}

	while(!sorted) {
		int leastRelativeChild, leastReal ;

        if ( leftChildRelative > elements) {
					// Child is now the last element in the heap.
            //cout << "Leaving Pop Function... " << endl;
            return rootVal;
		}
		//Get the Least Child
/*        cout << "Getting Least Child**********" << endl;
        cout << "Right Child = " << Parent->at(rightReal) << endl;
        cout << "Left Child = " << Parent->at(leftReal) << endl;
        cout << "*****************************" << endl;
*/
         if( lesserThan( Parent->at(rightReal), Parent->at(leftReal))
				&& rightChildRelative <= elements) {
            assert(Parent->at(rightReal) < Parent->at(leftReal));
            leastRelativeChild = rightChildRelative;
			leastReal = rightReal;
		}
		else { //left child is last child || left is least
            assert(Parent->at(leftReal) <= Parent->at(rightReal) || rightChildRelative > elements);
            leastRelativeChild = leftChildRelative;
			leastReal = leftReal;
		}
/*
        cout << "Least Child Real index is:" << leastReal << endl;
        cout << "Least Child Relative Index is:" << leastRelativeChild << endl;
        cout << "Least Child Value is:" << Parent->at(leastReal) << endl;
*/
		if( lesserThan(Parent->at(leastReal),Parent->at(myRealIndex)) ) {
			/*
            cout << "Need to swap with child!" << endl;
            cout << "Swap " << Parent->at(myRealIndex) << " with " << Parent->at(leastReal) << endl;
            */
			assert(Parent->at(leastReal) < Parent->at(myRealIndex));
			int temp = Parent->at(myRealIndex);
			Parent->at(myRealIndex) = Parent->at(leastReal);
			Parent->at(leastReal) = temp;
            /*
			cout << "Did it swap??????" << endl;
            cout << "Swap " << Parent->at(myRealIndex) << " with " << Parent->at(leastReal) << endl;
			*/
			myRealIndex = leastReal;
			myRelativeIndex = leastRelativeChild;

			leftChildRelative = myRelativeIndex*2;
			rightChildRelative = myRelativeIndex*2 + 1;

			leftReal = getIndex(leftChildRelative);
			rightReal = getIndex(rightChildRelative);
			/*
            cout << "My new real:" << myRealIndex << ", My Relative Index:" << myRelativeIndex << endl;
            cout << "New Left Real:" << leftReal << ", Left Relative:" << leftChildRelative << endl;
            cout << "New Right Real:" << rightReal << ", Right Relative:" << rightChildRelative << endl;
            */
        }
		else { //heap is in order
			sorted = true;
		}
    }

	return rootVal;
}

bool Heap::greaterThan(int value1, int value2) {
	if (value1 == value2) {
		return false;
	}
	else {
		return ((Minimizing && value1 > value2 )? true : false );
	}
}
bool Heap::lesserThan(int value1, int value2) {
	if (value1 == value2) {
        return false;
	}
	else {
		return ((Minimizing && value1 < value2 )? true : false );
	}
}

int Heap::rootValue() {return Parent->at(myRoot);}

void Heap::heapGUI(int ParentIndex) {
	int left, right;
	left = 2*ParentIndex;
	right = 2*ParentIndex +1;

	if (left > elements) {
		return;
	}

    cout << "Parent ="<< Parent->at( getIndex(ParentIndex) )
	    	<< " LeftChild =" << Parent->at( getIndex(left) ) ;
    if (right <= elements) {
        cout << " RightChild =" << Parent->at( getIndex(right) ) << endl;
    }
        heapGUI(left);
    heapGUI(right);
}
int Heap::size() {
	return elements;
}
void Heap::setRoot() {
    this->myRoot = ((this->fromRight)? Parent->size()-2 : 1 );
}