#ifndef RBTREE_H
#define RBTREE_H

#include "Node.h"

class RBTree{
public:
	RBTree();
	~RBTree();
	
	Node* root; 

	//Insert Logic
	void insertValue(int value);
	Node* BinarySearchInsert(Node* rootNode, Node* Node);
	void fixInsert(Node* node);
	
	//Delete Logic
	void transplant(Node* u, Node* v);
	Node* findMinimunNode(Node* node);
	void deleteValue(int value);
	void fixDelete(Node* node);

	void rotateLeft(Node* node);
    void rotateRight(Node* node);

	void print();
	void printTree(Node* node, int indent);

	void remove(int removeValue){};
	void sucessor(int sucessorValue, int treeVersion);

	void deleteTree(Node* node);
};

#endif //RBTREE_H

