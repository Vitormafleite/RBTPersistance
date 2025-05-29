#ifndef NODE_H
#define NODE_H

#include <vector>

class Node{
public:
	Node(){};
	~Node(){};

private:
	bool color; // 0 == black, 1 == red 
	bool isRoot; //might not be necessary, will see later on
	
}	

#endif //NODE_H
