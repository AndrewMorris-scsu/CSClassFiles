void search(string parameterKey)
{
	int order = 0;
	int key = 0;
	int rootRBN = 0;	
	
	string mySearchKey = parameterKey;
	string searchKey = 0;
	int elementsUsed = 0;
	int pointer = 0;
	Record tempRecord;
	
	/* update tree variables */
	order = BPlusTree.getField("order");
	key = BPlusTree.getField("key");
	rootRBN = BPlusTree.getField("rootRBN");
	
	/* load root block into memory */
	Block block(rootRBN, file);
	block.readBlock(rootRBN, file);
	
	/* update block variables */		
	elementsUsed = block.getUsed();
	
	/* while at an interior node */
	while (!block.isLeaf())
	{
		/* locate appropriate searchKey value */
		int i = 0;
		for (i = 0; i < elementsUsed; i++)
		{
			searchKey = block.getKey[i];
			if (mySearchKey.compare(searchKey) < 0)//CHANGE TO STRING COMPARE
				break;
		}
		
		/* get child RBN associated with appropriate searchKey value */
		pointer = block.getChild[i];
	
		/* read child block (new current block) into memory */
		block.readBlock(pointer, file);
		
		/* update elementsUsed */
		elementsUsed = block.getUsed()
	}
	
	int i = 0;
	for (i = 0; i < elementsUsed - 1; i++)
	{		
		tempRecord = block.getChild[i];		
		
		if (key == 1)
		{
			/* key is Last */
			searchKey = tempRecord.Last;			
		}
		else if (key == 2)
		{
			/* key is First */
			searchKey = tempRecord.First;
		}
		else if (key == 3)
		{
			/* key is ID1 */
			searchKey = tempRecord.ID1;
		}
		else if (key == 4)
		{
			/* key is ID2 */
			searchKey = tempRecord.ID2;
		}
		
		if (searchKey > mySearchKey)
			break;
	}
	
	if (searchKey.compare(mySearchKey) == 0)
	{
		cout << "Record found: " << tempRecord.Last ", " << tempRecord.First
			<< " " << tempRecord.ID1 << " " << tempRecord.ID2 << endl;
	}
	else
	{
		cout << "Sorry, no record with that key exists in the tree" << endl;
	}
	
	return 0;
}