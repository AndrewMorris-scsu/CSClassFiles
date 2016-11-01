#include <iostream>
#include <iomanip>
#include "string.h"
#include "Block.h"
using namespace std;

int main()
{
    string inputString;
    int inputInt;
    Record record;

    //int blockSize = BS;
    //int key = KY;
    int order = 6;
    int i = 0;

    ifstream infile("HappyTest.dat");
    ofstream outfile("test.txt", std::fstream::in | std::fstream::out);

    

    while(!infile.eof())
    {
        //block counter
         Block block(false, true, i);

        //for each space in the block, put a record in
        //or 3/4 or whatever
        for (float j = 0; j < (order - 1) * .75; j++)
        {
            infile >> inputString;
            record.Last = inputString;

            infile >> inputString;
            record.First = inputString;

            infile >> inputInt;
            record.ID1 = inputInt;

            infile >> inputInt;
            record.ID2 = inputInt;

            block.putRecord(record);

            //eat vertical bar
            infile >> inputString;

            //check for end of file
            if (infile.eof())
                break;
        }
        if (infile.eof()) {
            block.setRight(-9999);
        }
        else {
            block.setRight(i+1);
        }

        if (i == 0 ) {
            block.setLeft(-9999);
        }
        else {
            block.setLeft(i-1);
        }

        if (block.getLeft() == -1) {
            cout << "This works... " << endl;
        }

        block.setParent(i*20);
        
        block.writeBlock(outfile);
        i++;
    }
    return 0;
    
}
