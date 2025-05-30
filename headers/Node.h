#ifndef NODE_H
#define NODE_H

enum Color { RED, BLACK};

class Node{
public:
	Node(int nodeValue);

	Color color;
	int nodeValue;

	Node* left;
	Node* right;
	Node* parent;
};

#endif //NODE_H
