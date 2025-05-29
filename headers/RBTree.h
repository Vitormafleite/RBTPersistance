#ifndef RBTREE_H
#define RBTREE_H

#include "Node.h"

class RBTree{
public:
	RBTree(){};
	~RBTree(){};

	void insert(int insertValue){};
	void remove(int removeValue){};
	void sucessor(int sucessorValue, int treeVersion);
	void printTree(int treeVersion);
	
private:

};

#endif //RBTREE_H
