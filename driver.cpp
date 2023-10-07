//Authors Maddie Neely, Abi Sipes, Connor Comstock
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;	// Ryan ** hi
#include "tree.h"
#include "Licorice.h"

int main()
{
	srand(time(0));	//this is for the random function in Licorice

	ifstream babiesFile;
	babiesFile.open("licoriceBabies.txt"); //open file to read from


	string name;
	int score;
	int weapon;
	Tree<Licorice> babyTree;  //create the tree

	//!!We made the assumtion there would be no duplicate babies!!
	while(babiesFile >> name >> score >> weapon) //read in all the babies from licoriceBabies.txt
	{
		Licorice testBaby(name, score, weapon);
		babyTree.insertNode(testBaby);	//insert baby into tree
		cout << "baby has been inserted " << endl;
	}

	cout << "------------------"<<endl;
	cout << "Inorder: " << endl;	//print in order traversal
	babyTree.inOrder();
	cout << endl;
	cout << "------------------"<<endl;
	cout << "Preorder: " << endl;	//print preorder traversal
	babyTree.preOrder();
	cout << endl;
	cout << "------------------"<<endl;
	cout << "Postorder: " << endl;	//print postorder traversal
	babyTree.postOrder();
	cout << endl;

	cout << "depth: " << babyTree.depth() << endl;


	babiesFile.close();
	return 0;
}
