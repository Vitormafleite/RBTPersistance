#ifndef NODE_H
#define NODE_H

enum Color { RED, BLACK };
enum Field{ FIELD_LEFT, FIELD_RIGHT, FIELD_PARENT, FIELD_COLOR };

struct mods{
	int version;
	Field field;
	void* value;
};

class Node{
public:
	static constexpr int MAX_MODS = 8; //Here we can insure that the amount of mods we store is at most 8, respecting the rule <= 2p

	Node(int nodeValue, int versionOnCreation);

	Color color;
	int nodeValue;

	Node* left;
	Node* right;
	Node* parent;

	//Return nodes
	Node* rParentLeft;
	Node* rParentRight;
	Node* rLeftSon;
	Node* rRightSon;

	Node* previousNodeVersion;

	//mods array
	mods modBox[MAX_MODS];
	int modCount;
	int nodeVersion; //On node Creation

	void* getFieldValue(Field field, int version); 
	Node* addMod(Field field, void* value, int version);
	Node* copyNode(int newVersion);
};

#endif //NODE_H
