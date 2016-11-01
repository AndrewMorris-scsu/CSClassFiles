///extract keys and positions from record file to key and position file.
///sort the record file from the key and position file.
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
    char RecordName[] = "RecordFile.dat";
    strncpy(RecordName, originalrecordfile.c_str(), sizeof(RecordName)-1);
	//RecordName[sizeof(RecordName) - 1] = 0;
    char KeyName[] = "KeyFile.txt";
    strncpy(KeyName, keyfile.c_str(), sizeof(KeyName)-1);
	//KeyName[sizeof(KeyName) - 1] = 0;
    char TempName[] = "temp.dat";

    int oldRecordPos;

    string garbage; // The key value does not matter, we know the positions
                    // of the records in the file. Upon building B+ tree, extracting
                    // the key values will be trivial.

    fstream RecordFile;
    ifstream KeyFile;
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
    cout << "get rec at " << oldRecordPos << endl;
    RecordFile.seekp(oldRecordPos);

    RecordFile >> record.Last >> record.First >> record.ID1 >> record.ID2;

    while ( !KeyFile.eof() ) {

        tempFile << record.Last << " " << record.First << " " << record.ID1 << " " << record.ID2 << " |\n";

        KeyFile >> oldRecordPos >> garbage;

        RecordFile.seekp(oldRecordPos);
        RecordFile >> record.Last >> record.First >> record.ID1 >> record.ID2;
    }


    RecordFile.close();
    KeyFile.close();
    tempFile.close();

    rename(TempName, RecordName );

}




