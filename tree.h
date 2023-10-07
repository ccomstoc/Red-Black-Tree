#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;
#include "treenode.h"

template<typename NODETYPE> class Tree {
	private:
		TreeNode<NODETYPE> * root;

		typedef TreeNode<NODETYPE> * TreeNodePtr;

		// Helper functions
		void insertNodeHelper(TreeNodePtr & curr, const NODETYPE & value);
		TreeNodePtr deleteNodeHelper(TreeNodePtr & curr, const NODETYPE & value);

		void preOrderHelper(TreeNodePtr curr) const;
		void inOrderHelper(TreeNodePtr curr) const;
		void postOrderHelper(TreeNodePtr curr) const;
		void depthHelper(TreeNodePtr curr, int & total, int current) const;


	public:
		// Class setup
		Tree() { root = NULL; }
		~Tree();
		// Core functionality
		TreeNode<NODETYPE> * search(const NODETYPE & value);
		TreeNode<NODETYPE> * searchHelper(TreeNodePtr curr, const NODETYPE & value) const;
		void insertNode(const NODETYPE & value);
		void deleteNode(const NODETYPE & value) { deleteNodeHelper(root, value); }
		void preOrder() const { preOrderHelper(root); }
		void inOrder() const { inOrderHelper(root); }
		void postOrder() const { postOrderHelper(root); }
		int depth() const {
			int total = 0, current = 0;
			depthHelper(root, total, current);
			return total;
		} // end function depth()

		void leftRotate(TreeNodePtr x);
		void rightRotate(TreeNodePtr y);
		void recolor(TreeNodePtr k);
		TreeNodePtr getRoot() const { return root;}

}; // end class Tree

template<typename NODETYPE>
Tree<NODETYPE>::~Tree() {
	while (root != NULL)
		deleteNode(root->data);
} // end destructor

template<typename NODETYPE>
TreeNode<NODETYPE> * Tree<NODETYPE>::search(const NODETYPE & value)
{
	//search for a value and return the treeNode ptr
	//we need this function so we can recolor after we insert
	return searchHelper(root,value);
}

template<typename NODETYPE>
TreeNode<NODETYPE> * Tree<NODETYPE>::searchHelper(TreeNodePtr curr,const NODETYPE & value) const {

	if (curr == NULL)
		return curr;
	else if (value < curr->data) //then we need to recurse down left side of tree
		return searchHelper(curr->left, value);
	else if (value > curr->data) //then we need to recurse down the right subtree
		return searchHelper(curr->right, value);

	return curr;
} // end


template<typename NODETYPE>
void Tree<NODETYPE>::insertNode(const NODETYPE & value)
{
	insertNodeHelper(root, value);
	cout << "ReColoringg on "<< search(value)->data;
	recolor(search(value));
	//search for value return the nodeptr
	//call recolor on that nodeptr

}



template<typename NODETYPE>
void Tree<NODETYPE>::insertNodeHelper(TreeNodePtr & curr, const NODETYPE & value) {
	// If the subtree is empty, then we have found our new nesting place.
	// This is the base case, so let's create the new node.
	if (curr == NULL) {
		curr = new TreeNode<NODETYPE>(value);
		return;
	}
	if (value <= curr->data)
	{
		insertNodeHelper(curr->left, value);
		curr->left->parent = curr;  //set parent pointer

	}
	else
	{
		insertNodeHelper(curr->right, value);
		curr->right->parent = curr;  //set parent pointer
	}
} // end insertNodeHelper

//not sure if we have to do anything with this delteNodeHelper yet... since delete is extra credit
template<typename NODETYPE>
TreeNode<NODETYPE> * Tree<NODETYPE>::deleteNodeHelper(TreeNodePtr & curr, const NODETYPE & value) {
	// If the subtree is empty, quit
	if (curr == NULL)
		return curr;
	else if (value < curr->data)
		curr->left = deleteNodeHelper(curr->left, value);
	else if (value > curr->data)
		curr->right = deleteNodeHelper(curr->right, value);
	else {
		// We know that curr->data == value, so we're ready to delete

		// Let's call the "node to be deleted" . . . . doomed
		// Case 1: (doomed has no children)
		if ((curr->left == NULL) && (curr->right == NULL)) {
			delete curr;
			curr = NULL;
		} // end case 1 if

		// Case 2: (doomed has one child)
		else if (curr->left == NULL) {
			TreeNodePtr temp = curr;
			curr = curr->right;
			curr->parent = temp->parent; //fix parent pointer
			delete temp;
		} // end case 2a if
		else if (curr->right == NULL) {
			TreeNodePtr temp = curr;
			curr = curr->left;
			curr->parent = temp->parent; //fix parent pointer
			delete temp;
		} // end case 2b if

		// Case 3: (doomed has two children)
		else {
			// Find the smallest element on the right side of the tree.
			TreeNodePtr smallestRight = curr->right;
			while (smallestRight->left != NULL)
				smallestRight = smallestRight->left;

            // Notice that you actually only ever delete a node with 0 or 1 child from the tree.
            // Nodes with two children are too big to fail.
			curr->data = smallestRight->data;
			curr->right = deleteNodeHelper(curr->right, smallestRight->data);
		} // end case 3
	} // end outside else

	return curr;
}

template<typename NODETYPE>
void Tree<NODETYPE>::preOrderHelper(TreeNodePtr curr) const {
	if (curr == NULL)
		return;
	cout << curr->data << ' ';		// process the node
	cout << "color: " << curr->color << ' ';		// print the color
	if(curr->parent == NULL)
		cout << "parent is null..." << endl;
	else
		cout << "parent data : " << curr->parent->data << endl;		// print the parent data
	//cout << curr->parent << ' '; 	//print the parent?
	preOrderHelper(curr->left);		// traverse the left subtree
	preOrderHelper(curr->right);		// traverse the right subtree
} // end preOrderHelper

template<typename NODETYPE>
void Tree<NODETYPE>::inOrderHelper(TreeNodePtr curr) const {
	if (curr == NULL)
		return;
	inOrderHelper(curr->left);		// traverse the left subtree
	cout << curr->data << ' ';		// process the node
	cout << "color: " << curr->color << ' ';		// print the color
	if(curr->parent == NULL)
		cout << "parent is null..." <<endl;
	else
		cout << "parent data : " << curr->parent->data << endl;		// print the parent data
	inOrderHelper(curr->right);		// traverse the right subtree
} // end inOrderHelper

template<typename NODETYPE>
void Tree<NODETYPE>::postOrderHelper(TreeNodePtr curr) const {
	if (curr == NULL)
		return;
	postOrderHelper(curr->left);		// traverse the left subtree
	postOrderHelper(curr->right);		// traverse the right subtree
	cout << curr->data << ' ';			// process the node
	cout << "color: " << curr->color << ' ';		// print the color
	if(curr->parent == NULL)
		cout << "parent is null..." << endl;
	else
		cout << "parent data : " << curr->parent->data << endl;		// print the parent data
} // end postOrderHelper

template<typename NODETYPE>
void Tree<NODETYPE>::depthHelper(TreeNodePtr curr, int & total, int current) const {
	// if tree is empty, quit
	if (curr == NULL)
		return;
	current++;

	// Update total if it's bigger.
	if (current > total)
		total = current;
	depthHelper(curr->left, total, current);
	depthHelper(curr->right, total, current);
} // end depthHelper

 // Red/Black recoloring helper functions*/
template<typename NODETYPE>
void Tree<NODETYPE>::leftRotate(TreeNodePtr x)
{

    TreeNode<NODETYPE> * y;	//create a treenode pointer
    y = x->right; //set it equal to the given node's right child
    x->right = y->left; // set the given node's right child equal to the right chids left pointer
    if(y->left != NULL)	//if the left child of the right child is null
    {
        y->left->parent = x; //set the right child's left child's parent pointer to x
    }
    y->parent = x->parent; //set the parent of y to the parent of x
    if(x->parent == NULL)	//this means x was the root
    {
        root = y;	//so now y is the root
    }
    else if(x->parent->left == x) //this means x was a left child
    {
        x->parent->left = y; //so we want y to be a left child
    }
    else	//this means x was right child
    {
        x->parent->right = y; //so we want to make y a right child
	}
	y->left = x; //finally swap x and y by making y's left child x
	x->parent = y; //and x's parent y

}
template<typename NODETYPE>
void Tree<NODETYPE>::rightRotate(TreeNodePtr y)
{
	 TreeNode<NODETYPE> * x;
	 x = y->left;
	 y->left = x->right;
	 if(x->right != NULL)
	 {
	 	x->right->parent = y;
	 }
	 x->parent = y->parent;
	 if(y->parent == NULL)
	 {
	 	root = x;
	 }
	 else if(y->parent->right == y)// this means y was a right child
	 {
	 	y->parent->right = x;
	 }
	 else //this means y was a left child
	 {
		y->parent->left = x;
	 }
	 //finally make the swap
	 x->right = y;
	 y->parent = x;

}
template<typename NODETYPE>
void Tree<NODETYPE>::recolor(TreeNodePtr k)
{
	TreeNode<NODETYPE> * u;// Is usefull for case 3

	//-----case 1: this is the case where k is the root
	if(k->parent == NULL)
	{
		k->setColor(BLACK);
		return;
	}
	//-----case 2: k's parent is black
	else if (k->parent->color == BLACK)
	{
		cout << "the parent is b, do nothing " << endl;
		return;
	}
	//-----case 3: k's parent is red
	//violates rule if the parent is red...both it's children must be black
	while(k->parent != NULL && k->parent->color == RED )
	{
		if(k->parent->parent == NULL || k->parent == NULL)//Making sure we break the loop after we bubble up
		{																									//This handels the issue where the parent or the grandparent is the root
			return;
		}
		if(k->parent == k->parent->parent->right) // check if k's parent is the right child
		{
			u = k->parent->parent->left; //uncle of k
			if (u != NULL)
				cout << "the uncle of k " << u->data << endl; //Print the Uncle

			//-----case3.1 parent and uncle are both red
			if(u != NULL && u->color == RED) // if uncle is NULL it means it is also black
			{																//We only want this case to run when the uncle is red
				u->setColor(BLACK); //flip color of uncle to black
				k->parent->setColor(BLACK); //flip color of parent to black
				k->parent->parent->setColor(RED); //flip color of the grandparent
				k=k->parent->parent; //this set's up the "recursion"
			}

			else//uncle is black
			{
				//-----case3.2.1 uncle is black
				if(k==k->parent->right) // if k is the right child
				{
					//k=k->parent; //set k equal to k's parent  //so now k is parent
					leftRotate(k->parent->parent); //call left rotate
					k->parent->left->setColor(RED);
					k->parent->setColor(BLACK);
					k=k->parent;// Set ups "Recursion"
				}
				//-----case3.2.2
				else if(k==k->parent->left)
				{
					rightRotate(k->parent);
					k=k->right;
				}
			}
		}//Mirror Cases
		else if(k->parent == k->parent->parent->left)//The parent is a left child of a grandparent
		{
			u = k->parent->parent->right; // this is the uncle of k
			if (u != NULL)
				cout << "the uncle of k " << u->data << endl;
				//-----case3.1 Mirror
				if(u != NULL && u->color == RED)
				{
					u->setColor(BLACK); //flip color of uncle to black
					k->parent->setColor(BLACK); //flip color of parent to black
					k->parent->parent->setColor(RED); //flip color of the grandparent
					k=k->parent->parent; //this set's up the "recursion"
					//note we need to handle the g is root issue (This should be done at end)
				}
				else
				{
					//-----case3.2.3 uncle is black
					if(k==k->parent->left) // if k is the left child
					{
						//k=k->parent; //set k equal to k's parent  //so now k is parent
						rightRotate(k->parent->parent); //call left rotate
						k->parent->right->setColor(RED);
						k->parent->setColor(BLACK);
						k=k->parent;// Set ups "Recursion"
					}
					//-----case3.2.4
					else if(k==k->parent->right)
					{
						leftRotate(k->parent);
						k=k->left;
					}

				}
			}
	root->setColor(BLACK); //Makes sure root is black

	}
}


#endif
