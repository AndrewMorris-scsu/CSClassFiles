//
// Created by Amandrew on 11/13/15.
//

#include "replaceSelection.h"

#include <iostream>
#include <cstdlib>
#include <assert.h>

int main () {
    srand((unsigned int) time(NULL));
    int size = 0;
    int memSize = 0;
    vector<int> Input;

    cout << "How big should the input 'File' be?:";
    cin >> size;

    cout << "How much 'Memory' is left? (slots in vector for dual heap):";
    cin >> memSize;

    cout << "Resizing Input Vector..." << endl;
    Input.resize(size);

    cout << "resized to " << Input.size() << endl;
    sleep(1);
        /* This loop initializes inputs to create 1 run on Min Heap
        for (int i = 1; i < Input.size(); i++) {
            cout << "Pushing " << i << endl;
            Input.at(i) = i;
        }
        */

        /* This loop assigns random values, no expected output*/
        int validityCheck = 0;
        for (int i = 0; i < Input.size(); i++) {
            int random;
            random = rand()%1000 + 1;
            cout << "Pushing " << random << endl;
            Input.at(i) = random;

        }



    replaceSelection Test(&Input, memSize, true);
    Test.process();

    for (int i = 0; i < Test.Runs.size(); i++) {
        for (int j = 0; j < Test.Runs.at(i).size(); j++) {
            cout << " " << Test.Runs.at(i).at(j);
            ++validityCheck;
        }
        cout << endl;
    }
    assert(validityCheck == Input.size());

    /*
    int TheSize;

    cout << "Please input the size of the Dual heap you would like, must be greater than 4." << endl;
    cin >> TheSize;

    DualHeap Test(TheSize);

    for (int i = 0; i < Test.Vec.size()-2; i++) {
        Test.pushCurrent(rand()%20 +1);
    }
    Test.PrintVector();

    cout << Test.popCurrent() << endl;
    Test.pushPending(500);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(500);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(500);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(500);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(500);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(500);

    Test.PrintVector();

    Test.switchHeaps();

    cout << Test.popCurrent() << endl;
    Test.pushPending(100);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(100);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(100);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(100);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(100);

    Test.PrintVector();
    cout << Test.popCurrent() << endl;
    Test.pushPending(100);

    Test.PrintVector();

    Test.PrintVector();

    cout << Test.popCurrent() << endl;
    cout << Test.popCurrent() << endl;
    cout << Test.popCurrent() << endl;

    Test.PrintVector();

    cout << "Switching Heaps!" << endl;
    Test.switchHeaps();

    cout << Test.popCurrent() << endl;
    cout << Test.popCurrent() << endl;
    cout << Test.popCurrent() << endl;

    Test.PrintVector();
*/
    return 0;
}