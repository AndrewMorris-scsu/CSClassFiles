#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include "Block.h"
#include "ReplacementSelection.h"
#include "KeyPos.h"
#include "merge.h"
#include <cmath>
#include <sstream>

using namespace std;

/**
  * Main B+ tree creator
  *
  * Use Block class objects to manipulate record and its indexes
  * to form sequence set and index set of the tree.
  *
  * *****************CONTROL FILE****************************
  * Must be able to do following operations:
  *   - open the file initially to get input files 
  *      ->( 1st project task plus Component A of 2nd project )
  *   - Create a B+ tree
  *   - Search for a record using a given key
  *   - Insert records ( Bulk loading and individual records)
  *   - Delete records ( Rebuild tree to take care of deletion)
  *   - Refresh -> (don't know what this would entail)
  *   - Check consistency ( DEBUG functions to check the correctness)
  */
template <class keyType>
class BPlusTree {
   public:
      int keyNum;
      int order;
      string originalFileName;
      string treeFileName;

      BPlusTree();
      BPlusTree(int _keyNum, string _originalFileName, string _treeFileName, int _order=6);
      int open (string _treeFileName);
      int create (string _originalFileName, string _treeFileName, int _keyNum=3, int _order=6);
      int close ();
      int insert (const keyType key, const int recAddr);
      int remove (const keyType key, const int recAddr = -1);
      int search (const keyType key, const int recAddr = -1);
      void refresh ();
      void checkConsistency ();
      void newTree();
      //void Print (ostream &);
      //void Print (ostream &, int nodeAddr, int level);

   protected:
      Block * findLeaf (const keyType key);
      Block * newBlock();
      Block * fetch(const int recaddr);
      int store (Block *);
      Block Root;
      int Height; // height of the tree
      int Order;  // order of te tree
};
#endif