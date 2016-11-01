//
// Created by Amandrew on 11/13/15.
//

#include "DualHeap.h"

DualHeap::DualHeap(int size)
: leftHeap(&Vec, true, false), rightHeap(&Vec, true, true)
{
    Vec.resize(size+2);
    leftHeap.setRoot();
    rightHeap.setRoot();
    leftActive = true;

}

int DualHeap::popCurrent(){
    int poppedVal=0;

    if (leftActive) {
        poppedVal = leftHeap.pop();
    }
    else {
        poppedVal = rightHeap.pop();
    }
    if (poppedVal == -1) {
        cout << "ISSUE WITH POPPING CURRENT HEAP!!! returned -1" << endl;
        cout << "Issue was with popping " << ((leftActive)? "Left Heap" : "Right Heap" ) << endl;
    }
    else {
        cout << "Popped current heap successfully.. " << endl;
    }
    return poppedVal;
}

int DualHeap::pushCurrent(int value) {
    int status;
    if (leftActive) {
        status = leftHeap.insertAddSize(value);
    }
    else {
        status = rightHeap.insertAddSize(value);
    }

    if (status == -1) {
        cout << "Error: 'Push to current heap' MSG->vector full" << endl;
        return -1; //ERROR
    }
    else {
        return 0; //OK
    }
}

int DualHeap::pushPending(int value) {
    int status;
    if (leftActive) {
        rightHeap.insertAddSize(value);
    }
    else {
        leftHeap.insertAddSize(value);
    }
    if (status == -1) {
        cout << "Error: 'Push to pending heap' MSG->vector full" << endl;
        return -1; //ERROR
    }
    else {
        return 0; //OK
    }
}

void DualHeap::PrintVector() {
    for (int i = 0; i < Vec.size(); ++i) {
        cout << " " << Vec.at(i);
    }
    cout << endl;
}

void DualHeap::switchHeaps() {
    leftActive = !leftActive;
    cout << " SWITCHING HEAPS [" << ((leftActive)? "Left" : "Right" ) << "] is now active." << endl;
}

int DualHeap::currentHeapSize() {
    int size;
    if (leftActive) {
        size = leftHeap.size();
    }
    else {
        size = rightHeap.size();
    }
    return size;
}