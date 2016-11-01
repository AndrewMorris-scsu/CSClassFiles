/**
	* @file merge.h
	* Header file for the merge algorithm implementation
	* @authors Jeff Witthuhn, Ross Kostron, Subodh Bhattarai, Andrew Morris, Alex Gatzke

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include "KeyPos.h"
using namespace std;
/** \struct Run
	\breif The run struct.

	A struct to hold details about a Run.
*/
struct Run
{
	streampos pos;/**< positiion of next object in the run */
	int numObjects;/**< total number of objects in the run */
	int objectsExtracted;/**< current number of items taken from the run */
};

/** \struct ValueRun
	\breif The ValueRun struct.

	Container to be placed in the priority queue 
	that keeps track of the value of the object to be compared
	and also holds information on which run it comes from.
*/
template<class obj>
struct ValueRun
{
    obj value; /**< struct value value */
    int run; /**< struct value run */
};

/** \struct MaxHeap
	\breif The MaxHeap struct.

	Comparitors for priority queue.
*/
template<class obj>
struct MaxHeap
{
    bool operator()(ValueRun<obj> const &a, ValueRun<obj> const &b) { return a.value < b.value; }
};

/** \struct MinHeap
	\breif The MinHeap struct.

	Comparitors for priority queue.
*/
template<class obj>
struct MinHeap
{
    bool operator()(ValueRun<obj> const &a, ValueRun<obj> const &b) { return a.value > b.value; }
};

/**
	The initRuns method obtains the vector of Runs for a given file, indicated by filename
	\pre the file filename contains runs to be merged, 
	each run is separated by a '|' and a '\n' each element 
	in the run is separated by a space, make sure line endings are unix.
	\post the returned vector contains all of the runs in the file to be merged by the merge operation
	\param filename the name of the file that contains the runs
	\return a vector of runs to be merged
*/
template <class obj>
vector<Run> initRuns(string filename)
{
	ifstream infile(filename.c_str()); //input file
	vector<Run> runVector; //vector of runs
	int totalElementsCount=0; //total elements
	Run run; //the run
	char nextChar; //next character
	obj temp; //temp item
	bool end_of_file=false; //at end of file?
	streampos begin = infile.tellg(); //start pos
	//for the whole file
	while(!infile.eof()){
		infile.seekg(begin);
		run.objectsExtracted=0;
		run.pos=infile.tellg();
		string line;
		getline(infile, line, '|');
		infile.ignore(5, '\n');
		int i=0;
		istringstream runLine(line);
		//for each element in the line
		while(!runLine.eof()){
			runLine>>temp;
			if(runLine){
				i++;
				totalElementsCount++;
							}
		}
		run.numObjects = i; 
		runVector.push_back(run);
		begin=infile.tellg();
	}
	return runVector;
}

/**
	The merge function to merge a file of runs
	\pre user specifies if the file is ascending or decending,  assumes 
	they tell the truth the file inFileName has unix line endings,
	each run is separated by a '|' and '\n' each object is separated by a space.
	\post the file outFileName contains a single line  that contains all objects in the file inFileName in sorted order
	\param outFileName the output file name
	\param inFileName the input file name
	\param runVector the vector of runs
	\param ascending bool if ascending or decending
	\return a ouput file of all objects in sorted order
*/
template<class obj>
void merge(string outFileName, string inFileName, vector<Run> runVector,bool ascending)
{
	if (ascending){//use MinHeap, very redundant. 
		int totalElements=0;
		//count total elements so we know how many elements to merge
			for(int i=0; i<runVector.size();i++){
				int size=runVector[i].numObjects;
			//	cout<<"run i has this many elements: "<<size<<endl;
				totalElements+=size;
			}
			cout<<"total Elements: "<<totalElements<<endl;

			ifstream infile(inFileName.c_str());
			ofstream outfile(outFileName.c_str());
			//create priority queue and push the first element of each run in.
			priority_queue<ValueRun<obj>, vector<ValueRun<obj> >, MinHeap<obj> > Heap;
			for(int i=0; i<runVector.size();i++){
				if(runVector[i].objectsExtracted<runVector[i].numObjects){
							ValueRun<obj> insert;
							infile.seekg(runVector[i].pos);
							infile>>insert.value;
							runVector[i].pos=infile.tellg();
							runVector[i].objectsExtracted++;
							insert.run=i;
							Heap.push(insert);
						}
			}
			int count=0; //counter
			while(count<totalElements){
				count++;
				//pop the last element into outfile the last element is from run R[x]
				ValueRun<obj> popped = Heap.top();
				int x = popped.run; //top index
				outfile<<popped.value<<" ";
				//cout<<popped.value<<" ";
				if(runVector[x].objectsExtracted<runVector[x].numObjects){
							ValueRun<obj> insert;
							infile.seekg(runVector[x].pos);
							infile>>insert.value;
							runVector[x].pos=infile.tellg();
							runVector[x].objectsExtracted++;
							insert.run=x;
							Heap.push(insert);
						}
				Heap.pop();
			}
		}
		else{//use MaxHeap, Very redundant 
			int totalElements=0; //total elements
			for(int i=0; i<runVector.size();i++){
				int size=runVector[i].numObjects;
				//cout<<"run i has this many elements: "<<size<<endl;
				totalElements+=size;
			}
			cout<<"total Elements: "<<totalElements<<endl;
			ifstream infile(inFileName.c_str()); //input file
			ofstream outfile(outFileName.c_str()); //output file
			//create priority queue and push the first element of each run in.
			priority_queue<ValueRun<obj>, vector<ValueRun<obj> >, MaxHeap<obj> > Heap;
			for(int i=0; i<runVector.size();i++){
				if(runVector[i].objectsExtracted<runVector[i].numObjects){
							ValueRun<obj> insert;
							infile.seekg(runVector[i].pos);
							infile>>insert.value;
							runVector[i].pos=infile.tellg();
							runVector[i].objectsExtracted++;
							insert.run=i;
							Heap.push(insert);
						}
			}
			bool done=false; //done?
			int count=0; //counter
			while(count<totalElements){
				count++;
				//pop the last element into outfile the last element is from run R[x]
				ValueRun<obj> popped = Heap.top();
				int x = popped.run;
				outfile<<popped.value<<" ";
				//cout<<popped.value<<" ";
				//enqueue the next element in R[x] 
				if(runVector[x].objectsExtracted<runVector[x].numObjects){
							ValueRun<obj> insert;
							infile.seekg(runVector[x].pos);
							infile>>insert.value;
							runVector[x].pos=infile.tellg();
							runVector[x].objectsExtracted++;
							insert.run=x;
							Heap.push(insert);
						}
				Heap.pop();
			}
		}
		//cout<<endl;
}

/**
	The MergeFile glue function for the merging operation using the above functions (used outside to call merge).
	\pre user specifies if the file is ascending or decending,  assumes 
	they tell the truth the file inFileName has unix line endings,
	each run is separated by a '|' and '\n' each object is separated by a space.
	\post the file outFileName contains a single line  that contains all objects in the file inFileName in sorted order
	\param outFileName the output file name
	\param inFileName the input file name
	\param ascending bool if ascending or decending
	\return a ouput file of all objects in sorted order
*/
template <class obj>
void MergeFile(string outFileName, string inFileName, bool ascending)
{
	merge<obj>(outFileName,inFileName, initRuns<obj>(inFileName), ascending);
}