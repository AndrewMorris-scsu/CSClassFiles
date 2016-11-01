#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

class Heap {


public:
	vector<int> *Parent;		//Pointer to Parent's vector.
	bool Minimizing;

	Heap( vector<int> *myParent, bool Minimize, bool isfromRight);
	virtual ~Heap();

	int pop();
	int insertAddSize(int value);
	int rootValue();
	void heapGUI(int ParentIndex);
	int size();
	void setRoot();
private:

	bool fromRight;			// True if the heap is the heap to the right.
	int myRoot; 			// A quick access to the real root value for each heap.
	int elements; 			// Number of elements in heap.

	int getIndex(int index);
	bool greaterThan(int value1, int value2);
	bool lesserThan(int value1, int value2);

};
#endif /* HEAP_H_ */

