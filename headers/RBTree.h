#ifndef RBTREE_H
#define RBTREE_H

#include <limits>

#include "Node.h"

class RBTree{
public:
	RBTree();
	~RBTree();
	
	Node* root; 

	int currentVersion;

	//Insert Logic
	void insertValue(int value);
	Node* BinarySearchInsert(Node* rootNode, Node* Node);
	void fixInsert(Node* node);
	
	//Delete Logic
	void transplant(Node* u, Node* v);
	Node* findMinimunNode(Node* node);
	void deleteValue(int value);
	void fixDelete(Node* node);

	//successor
	int successor(int value); 

	void rotateLeft(Node* node);
    void rotateRight(Node* node);

	//for normal tree
	void print();
	void printTree(Node* node, int indent);

	//for versioned tree
	void printVersion(int version);
	void printTreeVersioned(Node* node, int version, int indent);

	void remove(int removeValue){};
	void sucessor(int sucessorValue, int treeVersion);

	void updateReturnPointers(Node* oldNode, Node* newNode, int version);

	void deleteTree(Node* node);

	//Getters and Setters for version mods //LEMBRAR DE IMPLEMENTAR AO ACORDAR, PARAMOS POR AQUI
	Node* getLeft(Node* node, int version);
    Node* getRight(Node* node, int version);
    Node* getParent(Node* node, int version);
    Color getColor(Node* node, int version); 

	Node* setLeft(Node* parent, Node* child, int version);
	Node* setRight(Node* parent, Node* child, int version);
	Node* setParent(Node* child, Node* parent, int version);
	Node* setColor(Node* node, Color color, int version);



};

#endif //RBTREE_H

