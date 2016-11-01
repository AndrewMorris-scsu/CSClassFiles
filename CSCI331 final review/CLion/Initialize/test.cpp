//test.cpp use -std=c++11
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "fileOperations.h"
#include "Block.h"


#include <typeinfo>
#include <random>
#include <cmath>
#include <sstream>
using namespace std;

int main(){

	int order =6;
	int keyNum=1;
	string originalFileName="Records.txt";
	string treeFileName="tree.txt";
	/*
   	extractKeys(originalFileName,"extracted_"+originalFileName, keyNum);
	int memory=15;///number of items allowed in memory for replacement selection
	bool ascending=true;
	ifstream inputFile("extracted_"+originalFileName);
	ofstream otemp("runs_"+originalFileName, std::ios_base::binary | std::ios_base::out );
	if(keyNum==1||keyNum==2){
		ReplacementSelection<KeyPos<string> > sortedRuns(memory,inputFile,otemp,ascending);
		otemp.close();
		MergeFile<KeyPos<string> >("sortedRuns_"+originalFileName,"runs_"+originalFileName,ascending);
	}
   else{
      ReplacementSelection<KeyPos<int> > sortedRuns(memory,inputFile,otemp,ascending);
      otemp.close();
      MergeFile<KeyPos<int> >("sortedRuns_"+originalFileName,"runs_"+originalFileName,ascending);
   }
   */
   rewriteRecordFromKey(originalFileName, "sortedRuns_"+originalFileName);

   


}