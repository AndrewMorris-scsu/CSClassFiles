//
// Created by Amandrew on 11/13/15.
//

#ifndef REPSELECT_DUALHEAP_H
#define REPSELECT_DUALHEAP_H

#include "Heap.h"
#include <iostream>
#include <cstdlib>
#include <vector>

class DualHeap {

public:
    vector < int > Vec;
    DualHeap(int);
    int popCurrent();
    int pushCurrent(int value);
    int pushPending(int value);
    void PrintVector();
    void switchHeaps();
    int currentHeapSize();
private:
    Heap leftHeap;
    Heap rightHeap;
    bool leftActive;

};


#endif //REPSELECT_DUALHEAP_H
