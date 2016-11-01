//
// Created by Amandrew on 11/13/15.
//

#ifndef REPSELECT_REPLACESELECTION_H
#define REPSELECT_REPLACESELECTION_H


#include "DualHeap.h"

#include <iostream>
#include <cstdlib>
#include <vector>

class replaceSelection {

public:
    vector < vector < int > > Runs;
    vector <int> *input;

    replaceSelection(vector < int > *input,int size, bool MinHeap);
    void process();
private:
    int currentRun;
    int inputIndex;
    DualHeap DHeap;


};


#endif //REPSELECT_REPLACESELECTION_H
