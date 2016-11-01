//keypos test;
#include <fstream>
#include <iostream>
#include "KeyPos.h"
#include <string>
#include <queue>
using namespace std;

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



int main(){
	KeyPos<string> a,b,c; 
	ifstream infile("HappyOutTest.txt");
	ifstream records("HappyTest.dat");
    infile >> a >> b >> c;
	cout << a << endl<<b<<endl<<c<<endl;
	string last,first,id1,id2;
	char firstChar;

	records.seekg(c.pos);
	records.get(firstChar);
	records.seekg(c.pos);
	records>>last>>first>>id1>>id2;
	cout<<"record: " << last<<" "<<first<<" "<< id1<< " "<<id2<<" "<<endl;
	cout<<"firstChar: "<<firstChar<<endl; 

	records.seekg(a.pos);
	records.get(firstChar);
	records.seekg(a.pos);
	records>>last>>first>>id1>>id2;
	cout<<"record: " << last<<" "<<first<<" "<< id1<< " "<<id2<<" "<<endl;
	cout<<"firstChar: "<<firstChar<<endl; 

	records.seekg(b.pos);
	records.get(firstChar);
	records.seekg(b.pos);
	records>>last>>first>>id1>>id2;
	cout<<"record: " << last<<" "<<first<<" "<< id1<< " "<<id2<<" "<<endl;
	cout<<"firstChar: "<<firstChar<<endl; 

	cout << "a>b: "<<(a>b?"true":"false")<<endl;
	cout<<"a<b: "<<(a<b?"true":"false")<<endl;
	cout<<"b>c:"<<(b>c?"true":"false")<<endl;
	cout<<"b<c:"<<(b<c?"true":"false")<<endl;
	//make this work please

	priority_queue< ValueRun<KeyPos<string> >, vector<ValueRun<KeyPos<string> > >, MinHeap<KeyPos<string> > > Heap;


	return 0;
}