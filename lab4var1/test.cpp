#include "tree.h"

int main() {
	//Program has to:
	CBinTree tree("Library.csv");//create tree from .csv
	CTreeNode Test(*(tree.GetRoot()));
	tree.Insert(Test);//Add new or existing books
	tree.Insert(CTreeNode(66, "Taras Shevchenko", "Kobzar", 2012, 999));//add new or existing books 
	tree.Remove(tree.Find("I Robot"));//delete by id
	tree.Find("I Robot");//find by title
	tree.PrintByAuthor("Isaac Azimov");//find all author's books
	tree.PrintByAuthor("Taras Shevchenko");
	
	system("pause");
	return 0;
}