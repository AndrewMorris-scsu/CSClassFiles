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
int BPlusTree<keyType>::open(string _treeFileName) {

}

template <class keyType>
int BPlusTree<keyType>::create(string _originalFileName, string _treeFileName, int _keyNum, int _order) {
	order =_order;
	keyNum=_keyNum;
	originalFileName=_originalFileName;
	treeFileName=_treeFileName;
   extractKeys(originalFileName,"tmp_extracted_"+originalFileName, keyNum);
   int memory=15;///number of items allowed in memory for replacement selection
   bool ascending=true;
   ifstream inputFile("tmp_extracted_"+originalFileName);
   ofstream otemp("tmp_runs_"+originalFileName, std::ios_base::binary | std::ios_base::out );
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
   rewriteRecordFromKey(originalFileName, "sortedRuns_"+originalFileName);
   initSequenceSet ("sorted"+originalFileName,treeFileName,order,keyNum); 
}

template <class keyType>
int BPlusTree<keyType>::close(){

}

template <class keyType>
int BPlusTree<keyType>::insert(const keyType key, const int recAddr) {
   int result; 
   int level = Height - 1;
   int newLargest = 0; 
   keyType prevKey, largestKey;
   Block * thisBlock, * newBlock, * parentBlock;
   //thisBlock = FindLeaf (key);

   // test for special case of new largest key in tree
   if (key > thisBlock->getLargestKey()) 
   {
      newLargest = 1; 
      prevKey = thisBlock->getLargestKey();
   }

   // handle special case of new largest key in tree
   if (newLargest)
   {
      for (int i = 0; i < Height-1; i++) 
      {
         
      }
   }
}
template class BPlusTree<string>;
