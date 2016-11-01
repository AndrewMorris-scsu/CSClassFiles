/**
	* @file BPlusTree.cpp
	* implementation file for B+ tree
	* @authors Jeff Witthuhn, Ross Kostron, Subodh Bhattarai, Andrew Morris, Alex Gatzke

*/

#include "BPlusTree.h"
#include "fileOperations.h"

template <class keyType>
BPlusTree<keyType>::BPlusTree(){}
template <class keyType>
BPlusTree<keyType>::BPlusTree(int _keyNum, string _originalFileName, string _treeFileName, int _order){
	order =_order;
	keyNum=_keyNum;
	originalFileName=_originalFileName;
	treeFileName=_treeFileName;
}

template <class keyType>
void BPlusTree<keyType>::Print(ostream& outfile){
   fstream file(treeFileName, std::fstream::in | std::fstream::out);
   Block root_block;
   root_block.readBlock(rootRBN, file);
   outfile<<"root block:"<<endl;
   //root_block.writeBlock(outfile);
   Record r;
   if(root_block.leaf()){
      outfile<<"LEAF BLOCKS\n";
   for(int i=0; i<root_block.getUsed(); i++){
         r=root_block.getRecord(i);
         outfile <<"|"<<setfill(' ')<<setw(10)<<r.Last<<" | ";
      }
      outfile<<endl;
   for(int i=0; i<root_block.getUsed(); i++){
         r=root_block.getRecord(i);
         outfile <<"|"<<setfill(' ')<<setw(10)<<r.First<<" | ";
      }
      outfile<<endl;
   for(int i=0; i<root_block.getUsed(); i++){
         r=root_block.getRecord(i);
         outfile <<"|"<<setfill('0')<<setw(10)<<r.ID1<<" | ";
      }
      outfile<<endl;
   for(int i=0; i<root_block.getUsed(); i++){
         r=root_block.getRecord(i);
         outfile <<"|"<<setfill('0')<<setw(10)<<r.ID2<<" | ";
      }
      outfile<<endl;
   }

}
template <class keyType>
void BPlusTree<keyType>::open(string _treeFileName) {
   treeFileName = _treeFileName;
   ifstream infile(treeFileName);
   keyNum = getField("KY",infile);
   rootRBN = getField("RR",infile);
   order = getField("OR",infile);
}


template <class keyType>
void BPlusTree<keyType>::create(string _originalFileName, string _treeFileName, int _keyNum, int _order) {
	order =_order;
	keyNum=_keyNum;
	originalFileName=_originalFileName;
	treeFileName=_treeFileName;
   extractKeys(originalFileName,"tmp_extracted_"+originalFileName, keyNum);
   int memory=15;///number of items allowed in memory for replacement selection
   bool ascending=true;
   ifstream inputFile("tmp_extracted_"+originalFileName);
   ofstream otemp("tmp_runs_"+originalFileName, std::ios_base::binary | std::ios_base::out |std::ios_base::trunc );
   if(keyNum==1||keyNum==2){
   ReplacementSelection<KeyPos<string> > sortedRuns(memory,inputFile,otemp,ascending);
   otemp.close();
   MergeFile<KeyPos<string> >("tmp_sortedRuns_"+originalFileName,"tmp_runs_"+originalFileName,ascending);
   }
   else{
   ReplacementSelection<KeyPos<int> > sortedRuns(memory,inputFile,otemp,ascending);
   otemp.close();
   MergeFile<KeyPos<int> >("tmp_sortedRuns_"+originalFileName,"tmp_runs_"+originalFileName,ascending);
   }
   rewriteRecordFromKey(originalFileName, "tmp_sortedRuns_"+originalFileName);
   initSequenceSet ("sorted"+originalFileName,treeFileName,order,keyNum); 
   buildFromSS(treeFileName);
}

template <class keyType>
void BPlusTree<keyType>::close(){

}

template <class keyType>
void BPlusTree<keyType>::insert(const keyType key, const int recAddr) {
   
}

template class BPlusTree<string>;
