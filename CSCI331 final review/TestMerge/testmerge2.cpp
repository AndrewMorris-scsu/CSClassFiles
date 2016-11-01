#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
//#include "Run.h"
using namespace std;
struct Run {
	streampos pos;
	int numObjects;
	int objectsExtracted;
};
template<class obj>
struct ValueRun{
    obj value;
    int run;
};

template<class obj>
struct MaxHeap
{
    bool operator()(ValueRun<obj> const &a, ValueRun<obj> const &b) { return a.value < b.value; }
};

template<class obj>
struct MinHeap
{
    bool operator()(ValueRun<obj> const &a, ValueRun<obj> const &b) { return a.value > b.value; }
};


template <class obj>
vector<Run> initRuns(string filename){
	ifstream infile(filename.c_str());
	vector<Run> runVector;
	int totalElementsCount=0;
	Run run;
	char nextChar;
	obj temp;
	bool end_of_file=false;
	streampos begin = infile.tellg();
	//for the whole file
	while(!infile.eof()){
		infile.seekg(begin);
		run.objectsExtracted=0;
		run.pos=infile.tellg();
		string line;
		//cout<<"tellg before/after:"<<infile.tellg()<<" ";
		getline(infile, line, '|');
		//infile.ignore(5, '\n');
	    //cout<<infile.tellg()<<endl;
		int i=0;
		istringstream runLine(line);
		//for each element in the line
		while(!runLine.eof()){
			runLine>>temp;
			i++;
			totalElementsCount++;
			cout<<temp<<" ";
		}
		run.numObjects = i;
		cout<<" Run is:(pos, number, current): (" << run.pos
			<< ", "<<run.numObjects
			<<", "<<run.objectsExtracted<<")\n";
		runVector.push_back(run);
		begin=infile.tellg();
	}
	cout<<"totalElements: "<<totalElementsCount<<endl;
	return runVector;
}
template<class obj>
void merge(string outFileName, string inFileName, vector<Run> runVector){

	int totalElements=0;
	for(int i=0; i<runVector.size();i++){
		int size=runVector[i].numObjects;
		cout<<"run " << i <<  " has this many elements: "<<size<<endl;
		totalElements+=size;
	}
	cout<<"total Elements: "<<totalElements<<endl;
	ifstream infile(inFileName.c_str());
	ofstream outfile(outFileName.c_str());
	//for each run, enqueue the first element
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
	bool done=false;
	int count=0;
	while(count<totalElements){
		count++;
		//pop the last element into outfile the last element is from run R[x]
		ValueRun<obj> popped = Heap.top();
		int x = popped.run;

		outfile<<popped.value<<" ";
		cout<<popped.value<<" ";
		//cout<<x<< " ";
		//cout<<popped.value<<" ";
		//enqueue the next element in R[x]
		if(runVector[x].objectsExtracted<runVector[x].numObjects){
					ValueRun<obj> insert;
					infile.seekg(runVector[x].pos);
					infile>>insert.value;
					//cout<<insert.value<<" ";
					runVector[x].pos=infile.tellg();
					runVector[x].objectsExtracted++;
					insert.run=x;
					Heap.push(insert);
				}
		//if all runs are complete, done=true
		//cout<<endl;
		for(int i=0; i<runVector.size(); i++){
			done=true;
			if(runVector[i].objectsExtracted<runVector[i].numObjects)
				done=false;
		}
		Heap.pop();
	}
	// while(!Heap.empty()){
	// 	ValueRun<obj> popped = Heap.top();
	// 	outfile<<popped.value<<" ";
	// 	cout<<popped.value<<" ";
	// 	Heap.pop();
	// }
    cout << endl;
}
int main(){
	vector<Run> runVector = initRuns<int> ("test.dat");
	merge<int> ("output.dat","test.dat", runVector);

}