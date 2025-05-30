#include "../headers/Node.h"

Node::Node(int nodeValue) {
    this->nodeValue = nodeValue;
    this->color = RED;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}