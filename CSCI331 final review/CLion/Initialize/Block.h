#ifndef BLOCKH
#define BLOCKH
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <iomanip>

using namespace std;
struct Record {
	string Last;
	string First;
	int ID1;
	int ID2;
};


class Block{

	private:
	/*
		*@breif
		*Member variables
	*/

	int RBN;///Relative block number
	int elementsUsed;
	int numChildren;
	int parent;///Parent RBH


	/**
		fields used if Block is a leaf
	*/
	int left;///sibling RBN
	int right;///sibling RBN
	vector<Record> recordList;///size = order, min = ceil (order /2)-1

	/**
		fields used if Block is an interior node
	*/
	vector<string> keyList;///size = order-1 (+1 extra, so order), min ceil(order/2)-1 
	vector<int> childrenList;///size = order, min ceil(order/2)
	
	/**
		*@breif 
		*constructors, ehhh idk which ones will be most useful
	*/
	public:
	/**
		*@breif
		*Static variables:
		*These are shared by all instances
		*of the Block class.
		*
		*	OrderSet is false initially and
		*true once order has been set.
		*order is to be shared by all intances 
		*of blocks in the program. 
		*
		*	If order is changed after it has been set
		*then we must rebuild the tree.
		*	
		*	FileName is the file name for which the 
		*current b+ tree is stored. It is shared 
		*by all Blocks, make sure fileName is the 
		*correct B+ tree.
		*
		*	Key is an integer 1, 2, 3 or 4 that 
		*represents the field in the Record struct
		*that the B+ tree is indexed by. 
		* 
		*	BlockSize is the number of bytes in a block.
		*BlockSize is determined by the order, and by the
		*format which we have chosen for the elements to
		*be stored in each block. 
		*
	*/


	//BEGIN STATIC VARIABLES
	static int order;
	static int recordSize;
	static int headerSize;
	static int key;
	static int leafBlockSize;
	static int interiorBlockSize;
	static int initialFill;
	static int difference;
	static int blockSize;
	/**
		@
		THIS MUST BE CALLED BEFORE USE ASDFJASDKFA
	*/
	static void initBlockClass(int _order=6, int _key=3){
		order = _order;
		key=_key;
		recordSize=46;
		headerSize=89;
		initialFill = (int)(order * .75);
		initialFill = (initialFill>(order/2)?initialFill:(order/2));
		leafBlockSize=(order-1)*recordSize+28;
		interiorBlockSize=14+(order-1)*6+order*11+4-5;
		difference = (interiorBlockSize>leafBlockSize?
									interiorBlockSize-leafBlockSize
									:leafBlockSize- interiorBlockSize);
		blockSize= (interiorBlockSize>leafBlockSize?
								interiorBlockSize:leafBlockSize);
	}
	//END STATIC VARIABLES
	bool isRoot;
	bool isLeaf;
	Block (int _RBN);
	Block (int _RBN, iostream& file);
	Block(bool _isRoot, bool _isLeaf, int _RBN);//for creating new nodes
	Block();
	/**
		*@breif
		*getters and setters for data members
	*/
	void setRoot(bool _isRoot){ isRoot=_isRoot; }
	void setLeaf(bool _isLeaf){	isLeaf=_isLeaf; }
	void toggleRoot(){ isRoot=!isRoot; }
	void toggleLeaf(){ isLeaf=!isLeaf; }

	bool leaf(){ return isLeaf; }
	bool root(){ return isRoot; }

	void setLeft(int _leftRBN){ left = _leftRBN; }
	void setRight(int _rightRBN){ right=_rightRBN; }
	void setParent(int _parentRBN){ parent = _parentRBN; }
	void setRBN(int _RBN){ RBN=_RBN; }

	int getRight(){ return right; }
	int getLeft(){ return left; }
	int getParent(){ return parent; }
	int getRBN(){ return RBN; }
	int getUsed(){ return elementsUsed; }
	int getRBNat(int nth_RBN);
	void putRecord(Record r){
		assert(isLeaf);
		recordList.push_back(r);
		elementsUsed++;
	}
	void putRecordAt(Record r, int i){
		assert(isLeaf);
		recordList.push_back(r);
		//shift things around; 
		elementsUsed++;
		for(int j=i; j<elementsUsed-1; j++){
			recordList[j+1].Last=recordList[j].Last;
			recordList[j+1].Last=recordList[j].First;
			recordList[j+1].Last=recordList[j].ID1;
			recordList[j+1].Last=recordList[j].ID2;
		}
		recordList[i].Last=r.Last;
		recordList[i].Last=r.First;
		recordList[i].Last=r.ID1;
		recordList[i].Last=r.ID2;
	}
	void putKey(string key){
		assert(!isLeaf);
		keyList.push_back(key);
		elementsUsed++;
	}
	void putChild(int childRBN){
		assert(!isLeaf);
		childrenList.push_back(childRBN);
		numChildren++;
	}
	bool checkKeyRRN(){
		return elementsUsed == (numChildren-1);
	}
	Record getRecord(int i){
		assert(isLeaf&&i<elementsUsed&&"i>=elementsUsed, you bad.");
		return recordList.at(i);
	}
	string getKey(int i){
		assert(!isLeaf&&i<elementsUsed&&"i>=elementsUsed. bad.");
		return keyList.at(i);
	}
	int getChild(int i){
		assert(!isLeaf&&i<numChildren&&"i>elementsUsed. bad.");
		return childrenList.at(i);

	}
	string getLargestKey();
	string getSmallestKey();
	string KeyFromRecord(Record r);
	void writeBlock(ostream& out);
	void readBlock(int _RBN, iostream& file);
	friend ostream &operator<<( ostream &output, const Block &b ){ 
	         ///print the formatted block to output. 
	         
	         return output;            
	      }


};
#endif