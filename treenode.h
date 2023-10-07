#ifndef TREENODE_H
#define TREENODE_H
#include <cstddef> //this was my google fix?


// I recommend that you declare the color as an enum
//(short for enumeration), which is a user-defined type that specifies constant variable names that
//substitute in for integer constants.

enum Color {BLACK = 0, RED};

// forward declaration of a class Tree
template<typename NODETYPE> class Tree;

template<typename NODETYPE>
class TreeNode {
	friend class Tree<NODETYPE>;

	private:
		TreeNode<NODETYPE> * left;
		TreeNode<NODETYPE> * right;
		TreeNode<NODETYPE> * parent;
		NODETYPE data;
		Color color;

	public:
		//NODETYPE data;
		// Class setup
		TreeNode(const NODETYPE & d) : left(NULL), right(NULL), parent(NULL), color(RED), data(d) {}
		// Access function
		NODETYPE getData() const {return data;}
		NODETYPE * getRight() const{return right;}
		NODETYPE * getLeft() const{return left;}
		void setColor(Color c) //c is RED or BLACK
		{
			color = c;
		}

}; // end class TreeNode

#endif
