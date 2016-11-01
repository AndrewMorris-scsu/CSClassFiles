/**
 * By: Default State & Co.
 * Created: 12-8-15
 * Updated: 12-8-15
 *
 * Current State:
 * Logic to extract the key from the child node needs to be established.
 */


#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include "Block.h"
#include "fileOperations.h"



/**
 *
 * @long TO INITIALIZE TREE
 * 1. Read over all of the populated data blocks
 * 2. get a count of the amount of blocks, determine how many internal nodes needed.
 *      -How to calculate?
 * 3. for each level, besides root, populate the nodes.
 * 4. create the root
 * 5. Update header file with root location.
 *
 * preconditions :
 * @post A B+ tree file has been created
 * @post Header information is known/retrievable.
 * @post the sequence set has been built, and links between nodes is established
 *       via left and right RBNs.
 *
 * @post : A B+ Tree will be initialized, and the root location value in the header has been update.
 *
 *
 *
 */



using namespace std;

string findKey(int rightPointer, iostream& file);

int main()
{
    int g;
    cout << "Building the Sequence Set" << endl;
    initSequenceSet("HappyTest.dat", "test.txt", 5, 3);

    cout << "Initializing" << endl;
    fstream file("test.txt", std::fstream::in | std::fstream::out );

    int nextRBN = 0;
    Block blockStats;     //NOT USED FOR ALL BLOCKS!!!! A container in case we need it.


    int header_size = blockStats.headerSize;        //header_size will be passed in from the header.
    int block_size = blockStats.blockSize;         //Header_size + RBN * block_size  will be the first char of each block.

    int num_of_leaves = 0;      //Number of leaves
    int extra_children=0;
    int num_of_parents = 0;     //Number of parents to generate for a given level
    int fillpercent=(int) ceil((blockStats.order -1) * 0.75);
    int minfill=(int) ceil(Block::order/2);
    int recs_per_node = (fillpercent>minfill?fillpercent:minfill);
    cout<<"FillPercent:"<<fillpercent;
    cout<<"recs_per_node: "<<recs_per_node;
    int levels = 0;
    int Key;                    // 1, 2, 3, or 4. This is which key we are sorted by.

    /*                            // Passed in from header file.
    setField("headerSize", blockStats.headerSize, file);
    setField("order", blockStats.order, file );
    setField("key", blockStats.key, file );
    setField("firstRBN", blockStats.key, file );
    setField("lastRBN", blockStats.key, file );
    setField("rootRBN", blockStats.key, file );
    setField("RBNsize", blockStats.key, file );
    setField("fieldSize", blockStats.key, file );
    setField("keySize", blockStats.key, file );
    setField("blockSize", blockStats.key, file );
    */
    // TO INITIALIZE TREE
    // 1. Read over all of the populated data blocks
    file.seekg(header_size);

    Block temp(false, true, 0);
    cout << "reading first block.. " << endl;
    temp.readBlock(nextRBN, file);
    ++nextRBN;
    ++num_of_leaves;

    int RBN_to_right = temp.getRight();
    cout << "RBN to the right = " << RBN_to_right << endl;
    while (RBN_to_right > 0) {

        cout << RBN_to_right << endl;
        cout << "nextRBN =" << nextRBN << endl;
        temp.readBlock(nextRBN, file);
        //temp.writeBlock(cout);
        RBN_to_right = temp.getRight();

        ++nextRBN;
        ++num_of_leaves;
    }

    file.seekg(0, file.beg);
    cout << "There are [" << num_of_leaves << "] leaves." << endl;
    cout << "streampos is now :" << file.tellg() << endl;
    cout << ((file.eof())? "EOF is tripped. dammit" :
             "EOF is reset! Continue") << endl;
    if (file.eof()) {
        cout << "EOF has not been reset... Eff word.";
        return -1;
    }
    // 2. get a count of the amount of blocks,
    // determine how many internal nodes needed.

    // Get the records per node, this is how many leaves
    // I can assign to a single interior node.

    cout << "Placing " << recs_per_node << " keys per node." << endl;


    // Below is just getting the ceiling of the integer division.
    // The the number of parents needed for a level.
    extra_children=num_of_leaves%recs_per_node;
    num_of_parents = num_of_leaves/recs_per_node;


    cout << "Should have " << num_of_parents << " parents for leaves." << endl;

    Block the_root(true, false, 0);
    // 3. for each leaf establish the first level above leaves
    if (num_of_leaves <= recs_per_node) {
        /**
         * Will need to handle the case where the number of
         * leaves does not exceed the number of keys we will
         * hold in an interior node. In this case, we will need
         * to create one interior branch that is also the root.
         *
         * This will currently be considered as a edge case, but
         * is definitely likely with small data sets with a large
         * order.
         */
        cout << "Looks like you only need a root. " << endl;
        the_root.setRBN(nextRBN);

        for (int i = 0; i < num_of_leaves; i++) {
            Block existing_child;
            existing_child.readBlock(i,file );      //Retrieve Child record
            existing_child.setParent(nextRBN);      //Set Parent of child
            //Push RBN to parent
            if (i > 0) {
                the_root.putKey(existing_child.getSmallestKey());
            }
            the_root.putChild(i);
            //update children with parents information
            existing_child.setParent(nextRBN);
            //write out child
            cin>>g;
            existing_child.writeBlock(file);

        }
        ++nextRBN;

    } else {
        cout << "You will have at least one level" << endl;
        /**
         * In this case, there will be at least one level of interior
         * nodes between the root node and the data node.
         *
         * First establish the lowest level of the tree above the leaves.
         * Then generalize the situation to populate the branch nodes
         * to the root. Finally create the root.
         */
        int least_parentRBN = num_of_leaves;
        for (int i = 0; i < num_of_leaves; i += recs_per_node+ ((extra_children > 0)? 1:0 )) {

            //create a new interior node
            Block new_interior(false, false, nextRBN);
            cout << "New block created. RBN =  " << nextRBN << endl;

            cout << "Children are RBNs :";
            //for each child
            for (int j = 0; j < recs_per_node+ (extra_children>0?1:0)
                            && (i+j) < num_of_leaves; j++) {
                //read in child

                Block existing_child;
                existing_child.readBlock(i + j, file);
                cout<< "" << j + i <<  ", ";


                existing_child.setParent(nextRBN);
                //Push RBN to parent
                new_interior.putChild(i + j);

                //Push Key to parent
                /**
                 * We need to establish our rule here for keys.
                 *
                 * An idea of mine is that the first and last children
                 * do not actually pass up their keys.
                 * So for a order so for n children
                 * Only children 1 < child < n would pass the key up to
                 * the parent.
                 */
                if (j > 0) {
                    new_interior.putKey(existing_child.getSmallestKey());
                }
                //update children with parents information
                existing_child.setParent(nextRBN);
                //write out child
                cout << "CHILD Writing RBN" << existing_child.getRBN() << endl;
                cin>>g;
                existing_child.writeBlock(file);



            }
            if(extra_children>0){
                extra_children--;
            }
            cout << endl;
            cout << "INT Writing RBN" << new_interior.getRBN() << endl;
            cin>>g;
            new_interior.writeBlock(file);
            ++nextRBN;                      //Next available RBN for allocation
            //levels ABOVE leaf nodes.

            //write out interior node
        }
        ++levels; // Just in case we want the number of levels in the tree....

        /**
         * The branch nodes above the leaves have been populated, populate the
         * rest of the tree TO  the root.
         * The ROOT will need to be populated AFTER the next WHILE loop.
         */

        // Get number of parents needed.
        num_of_leaves = num_of_parents;
        extra_children=num_of_leaves%recs_per_node;
        num_of_parents = num_of_leaves/recs_per_node;

        least_parentRBN = num_of_leaves;
        cout << "Num_of_Parents = " << num_of_parents << endl;
        cout << "least_parentRBN = " << least_parentRBN << endl;
        //for the rest of the leaves
        while (num_of_leaves > recs_per_node) {
            cout <<"NEW LEVEL -> " << levels << endl;

            //The least interior parent. Start here.
            for (int i = least_parentRBN; i < num_of_leaves + least_parentRBN;
                 i += (recs_per_node) + ((extra_children > 0)? 1:0 )) {


                cout << "new interior node. RBN = " << nextRBN << endl;
                Block new_interior(false, false, nextRBN);
                if (new_interior.leaf()) {
                    cout << "Teh Feck? new_interior is a leaf before 'For' loop" << endl;
                }
                cout<<"recs_per_node: "<<recs_per_node<<endl;
                cout<<"extra children: "<<extra_children<<endl;
                cout<<"num_of_leaves:"<<num_of_leaves<<endl;
                cout<<"i + j: "<<" "<<i<<" + "<<" : "<<i<<endl;

                for (int j = 0; j < recs_per_node + ((extra_children)>0?1:0)
                                &&(i+j) <least_parentRBN+ num_of_leaves ; j++) {
                    //read in child
                    Block existing_child;
                    existing_child.readBlock((i + j), file);
                    
                    //Push RBN to parent
                    new_interior.putChild(i + j);
                    cout<<"adding RBN:"<<i+j<<"\n";
                    cout<<"current block rbn is:"<<new_interior.getRBN()<<endl;
                    //Push Key to parent when not the first echild.
                    if (j > 0 ) {
                        cout<<"adding key:"<<findKey( new_interior.getChild(j),file)<<"\n";
                        new_interior.putKey(findKey( new_interior.getChild(j) , file));
                    }
                    //update children with parents information
                    existing_child.setParent(new_interior.getRBN());
                    //write out child
                    cout << "INT Writing RBN" << existing_child.getRBN() << endl;
                    cin>>g;
                    existing_child.writeBlock(file);

                }
                if(extra_children>0){
                    extra_children--;
                }
                cout << "INT2 Writing RBN" << new_interior.getRBN() << endl;
                cin>>g;
                new_interior.writeBlock(file);
                ++nextRBN;
            }
            //get parents needed.
            num_of_leaves = num_of_parents;
            extra_children=num_of_leaves%recs_per_node;
            num_of_parents = num_of_leaves/recs_per_node;
            least_parentRBN = nextRBN - num_of_leaves;

            ++levels;           //Those pesky incrementing operations...
        }

        // The only thing left to do is build the ROOT.
        cout<<"creating root:\n";
        the_root.setRBN(nextRBN);
        the_root.setParent(-9999);
        int counter = 0;
        cout<<"starting parent loop:\n";
        cout<<"least_parentRBN:"<<least_parentRBN<<endl;
        cout<<"nextRBN:"<<nextRBN<<endl;
        cout<<"num_of_leaves:"<<num_of_leaves<<endl;
        for (int i = least_parentRBN; i < num_of_leaves + least_parentRBN; i++) {

            Block existing_child;                //Retrieve Child record
            cout<<"adding RBN:"<<i<<"\n";
            cout<<"current block rbn is:"<<the_root.getRBN()<<endl;
            existing_child.readBlock(i, file);

            //Push RBN to parent

            the_root.putChild(i);
            cout<<"zput child:"<<i<<"elements is: "<< the_root.getUsed()<<"\n";

            if (counter > 0 ) {
                the_root.putKey(findKey( the_root.getChild(counter), file ));
                cout<<"zzput child:"<<i<<"elements is: "<< the_root.getUsed()<<"\n";

            }
            counter++;
            //update children with parents information
            existing_child.setParent(nextRBN);
            cout<<"set parent of block "<<existing_child.getRBN()<<" to: "<<existing_child.getParent()<<endl;
            //write out child
            cin>>g;
            existing_child.writeBlock(file);
            existing_child.writeBlock(cout);

        }
        //Set the keys for the root nodes.
        /**
         * Keys in the root nodes need to be dividers of the
         * leaf nodes.
         * I propose that for each root key, we add them post
         * addition of the RBNs ('pointers'). The order of the RBNs
         * will not change in the root node, but because we are
         * initializing the tree, we can select the keys to be
         * in the root to our specs.
         *
         * to populate each root key, I suggest following the
         * right pointer once, then continue left until the leaf
         * nodes are hit. Then take the least element and populate
         * that key up to the root.
         * This method will assure that we have are establishing the
         * search rules in the B+ tree.
         */

    }

    // 5. Update header with root location
    nextRBN++;
    cout << "ROOT Writing RBN" << the_root.getRBN() << endl;

    the_root.writeBlock(file);

    cout << "Tree Complete" << endl;
    return 0;
}


string findKey(int rightPointer, iostream& file) {

    Block kid;

    kid.readBlock(rightPointer, file);

    while (!kid.leaf()){
        kid.readBlock( kid.getChild(0), file );
    }
    return kid.getSmallestKey();


}