///extract keys and positions from record file to key and position file.
///sort the record file from the key and position file.

#ifndef FILEOP
#define FILEOP
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "Block.h"
using namespace std;
void extractKeys(string inputfile,string outputfile, int Key){
	int NAMESIZE=80;

    char InputFileName[NAMESIZE + 1];
    char OutputFileName[NAMESIZE + 1];
    ifstream infile;
    ofstream outfile;
    streampos position;
    int ID1, ID2;
    string Last, First;
    strncpy(InputFileName, inputfile.c_str(), sizeof(InputFileName));
	InputFileName[sizeof(InputFileName) - 1] = 0;
	strncpy(OutputFileName, outputfile.c_str(), sizeof(OutputFileName));
	OutputFileName[sizeof(OutputFileName) - 1] = 0;
    infile.open(InputFileName);
    outfile.open(OutputFileName);
    cout<<"file read, inputfile/outputfile:"<<InputFileName<<" "<<OutputFileName<<endl;
    //Process File
    position = infile.tellg();

    infile >> Last >> First >> ID1 >> ID2;
    cout<<"last, first, id1, id2:"<<Last<<" "<<First<<" "<<ID1<<" "<<ID2;
    // While !eof file
    int ReadabilityCounter = 0;
    while ( !infile.eof() ) {

        cout << position << " " << Last << " " << First;
        cout << " " << ID1 << " " << ID2 << endl;

        //if first letter of last name == '*', skip
        //else output "Position Key "
        if (Last.at(0) == '*') {
            cout << "Deleted record, did not output" << endl;
            cout << position << " " << Last << " " << First;
            cout << " " << ID1 << " " << ID2 << endl;
        } else {

            outfile << position; //Regardless of case, we need the position.
            switch (Key){
                case 1: { //Last Name Key
                outfile << " " << Last << " ";
                    break;
                }
                case 2: { // First name Key
                outfile << " " << First << " ";
                    break;
                }
                case 3: { // ID1 Key
                outfile << " " << ID1 << " ";
                    break;
                }
                case 4: { //ID2 Key
                outfile << " " << ID2 << " ";
                    break;
                }

            }
            //Simply creates line breaks for every 10 records
            //for readability                       //
            ++ReadabilityCounter;                   //
            if ( (ReadabilityCounter % 10) == 0) {  //
                outfile << endl;                    //
            }                                       //
            //****************************************
        }


        //get new record;
        //get current position
        infile.ignore(3, '\n');
        position = infile.tellg();
        //Read in line, assign values
        infile >> Last >> First >> ID1 >> ID2;


    }
}


void rewriteRecordFromKey(string originalrecordfile, string keyfile){
	int NAMESIZE=80;
    char RecordName[NAMESIZE + 1];
    strncpy(RecordName, originalrecordfile.c_str(), sizeof(RecordName));
	RecordName[sizeof(RecordName) - 1] = 0;
    char KeyName[NAMESIZE + 1];
    strncpy(KeyName, keyfile.c_str(), sizeof(KeyName));
	KeyName[sizeof(KeyName) - 1] = 0;
    char renameTemp[NAMESIZE + 1];
    strncpy(renameTemp, ("sorted"+originalrecordfile).c_str(), sizeof(renameTemp));
    char TempName[] = "temp.dat";


    int oldRecordPos;

    string garbage; // The key value does not matter, we know the positions
                    // of the records in the file. Upon building B+ tree, extracting
                    // the key values will be trivial.

    fstream RecordFile;
    fstream KeyFile;
    fstream tempFile;

    Record record;
    /**
     * Open the files needed for the rewriting operations
     */
    RecordFile.open(RecordName, std::fstream::in | std::fstream::out);
    KeyFile.open(KeyName, std::fstream::in);
    tempFile.open(TempName, std::fstream::out);

    //Initialize the first read from the KeyFile.
    KeyFile >> oldRecordPos >> garbage;
    RecordFile.seekp(oldRecordPos);

    RecordFile >> record.Last >> record.First >> record.ID1 >> record.ID2;

    while ( !KeyFile.eof()) {
    	//cout<<"5";

        tempFile << record.Last << " " << record.First << " " << record.ID1 << " " << record.ID2 << " |\n";

        KeyFile >> oldRecordPos >> garbage;
        cout<<oldRecordPos<<" "<<garbage;
        RecordFile.seekp(oldRecordPos);
        RecordFile >> record.Last >> record.First >> record.ID1 >> record.ID2;
    }

    RecordFile.close();
    KeyFile.close();
    tempFile.close();
    cout<<"\nrename: "<<TempName<<"\nTo: "<<renameTemp<<endl;
    rename(TempName, renameTemp);

}

void initSequenceSet(string recordFileName, string treeFileName,int _order,int _key){
    Block::initBlockClass(_order,_key);
    cout<<"initialized block class (order, key), ("<<(Block::order)<<", "<<(Block::key)<<")\n";
    string inputString;
    int inputInt;
    int i = 0;
    Record record;
    ifstream infile(recordFileName);
    ofstream outfile(treeFileName, std::ios_base::out);
    cout<<"writing to file: "<<treeFileName<<endl;
    cout<<"reading from file: "<<recordFileName<<endl;


/* This will be used for now, in the future, the block below */
    int headerSize = 89;
    int order = Block::order;
    int key = Block::key;
    int firstRBN = 0;
    int lastRBN = 0;
    int rootRBN = 0;
    int RBNsize = 5;
    int fieldSize = 10;
    int keySize = 10;
    int blockSize = Block::blockSize;
    outfile << "HS " << setfill('0') << setw(5) << headerSize
            << " OR " << setfill('0') << setw(5) << order
            << " KY " << setfill('0') << setw(5) << key
            << " FR " << setfill('0') << setw(5) << firstRBN
            << " LR " << setfill('0') << setw(5) << lastRBN
            << " RR " << setfill('0') << setw(5) << rootRBN
            << " RS " << setfill('0') << setw(5) << RBNsize
            << " FS " << setfill('0') << setw(5) << fieldSize
            << " KS " << setfill('0') << setw(5) << keySize
            << " BS " << setfill('0') << setw(5) << blockSize;


    while(!infile.eof())
    {
        //block counter
         Block block(false, true, i);

        //for each space in the block, put a record in
        //or 3/4 or whatever
        for (float j = 0; j < Block::initialFill; j++)
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

        if (infile.eof())
            block.setRight(-9999);
        else
            block.setRight(i+1);

        if (i == 0)
            block.setLeft(-9999);
        else
            block.setLeft(i-1);

        block.setParent(i*20);
        block.writeBlock(outfile);
        //block.writeBlock(cout);
        i++;
    }
    infile.close();
    outfile.close();
}
#endif
