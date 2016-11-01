//
// Created by Amandrew on 11/13/15.
//

#include "replaceSelection.h"

replaceSelection::replaceSelection(vector < int > *input, int size, bool MinHeap)
: DHeap(size) {

    cout << "Initializing ReplaceSelection object.. " << endl;
    this->input = input;

    for (int i = 0; i < size; i++) {

        DHeap.pushCurrent( this->input->at(i) );
        ++this->inputIndex;
        cout << " " << this->input->at(i);
    }
    cout << endl;
    cout << "DualHeap is initialized " << endl;
    DHeap.PrintVector();
}

void replaceSelection::process() {

    int InputSize = input->size();
    int currentRun = 0;
    int popped;
    int inputVal;
    cout << "Processing... " << endl;

    while (inputIndex < InputSize) {
        popped = 0;
        inputVal = 0;

        Runs.resize(currentRun + 1);              //Starting a new run, initialize a new vector.

        //pop current heap
        //cout << "Popped " << popped << "For first val of run [" << currentRun+1 << "]" << endl;
        while (DHeap.currentHeapSize() > 0 && inputIndex < InputSize) {

            popped = DHeap.popCurrent();
            cout << "Writing " << popped << " out to run." << endl;
            Runs.at(currentRun).push_back(popped);  //Place popped value in run
            cout << "finished writing to run, get input value from input index:" << inputIndex << endl;
            inputVal = input->at(inputIndex);
            cout << "Retrieved " << inputVal << " from the input vector" << endl;
            if (inputVal > popped) {

                DHeap.pushCurrent(inputVal);
            }
            else {

                DHeap.pushPending(inputVal);
            }
            inputIndex++;
        }
        if (inputIndex < InputSize) {
            DHeap.switchHeaps();
            ++currentRun;
        }
        cout << "Finished Run " << currentRun+1 << endl;
        DHeap.PrintVector();

        } // End of run

    cout << "Done Processing... " << endl;
    DHeap.PrintVector();
    // Now that the input is done, we need to empty the current Heap
    // in the current run, and then output the rest of the pending heap
    // to another run.
    int leftovers = 0;
    cout << "This is what is left in the vector" << endl;
    DHeap.PrintVector();

    leftovers = DHeap.currentHeapSize(); //Add the rest of the values in the heap to leftovers.

    cout << "Leftovers = " << leftovers << "for run:" << currentRun << endl;

    // Empty out current heap.
    for(int i = 0; i < leftovers; i++) {

        popped = DHeap.popCurrent();
        Runs.at(currentRun).push_back( popped );
    }

    DHeap.switchHeaps();                    //We need to make sure the pending heap
                                            //gets emptied..
    if(DHeap.currentHeapSize() > 0){
        ++currentRun;
        Runs.resize(currentRun + 1);

        leftovers = DHeap.currentHeapSize();

        cout << "There were [" << leftovers << "] elements left in pending heap." << endl;
        cout << currentRun << "is the currentRUN" << endl;
        for(int i = 0; i < leftovers; i++) {

            popped = DHeap.popCurrent();
            Runs.at(currentRun).push_back( popped );
        }
    }
    cout << "Done cleaning up... " << endl;
}


