#include "../headers/RBTree.h"
#include <iostream>

RBTree::RBTree() {
    root = nullptr;
    currentVersion = 0;
}

RBTree::~RBTree(){
    deleteTree(root);
}

void RBTree::deleteTree(Node* node) {
    if (!node) 
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    
    delete node;
}

void RBTree::insertValue(int value) {
    Node* newNode = new Node(value, currentVersion);
    root = BinarySearchInsert(root, newNode);
    fixInsert(newNode);
}

Node* RBTree::BinarySearchInsert(Node* root, Node* node) {
    if (!root)
        return node;

    if (node->nodeValue < root->nodeValue) {
        root->left = BinarySearchInsert(root->left, node);
        root->left->parent = root;
    } else {
        root->right = BinarySearchInsert(root->right, node);
        root->right->parent = root;
    }

    return root;
}

void RBTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RBTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right)
        y->right->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void RBTree::fixInsert(Node* node) {
    while (node != root && node->parent->color == RED) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    rotateLeft(node);
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(grandparent);
            }
        } else {
            Node* uncle = grandparent->left;

            if (uncle && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rotateRight(node);
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(grandparent);
            }
        }
    }

    root->color = BLACK;
}

void RBTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != nullptr)
        v->parent = u->parent;
}

Node* RBTree::findMinimunNode(Node* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

void RBTree::deleteValue(int value) {
    Node* z = root;
    while (z != nullptr && z->nodeValue != value) {
        if (value < z->nodeValue)
            z = z->left;
        else
            z = z->right;
    }

    if (z == nullptr)
        return;

    Node* y = z;
    Color yOriginalColor = y->color;
    Node* x = nullptr;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = findMinimunNode(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            if (y->right) y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        if (y->left) y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK)
        fixDelete(x);
}

void RBTree::fixDelete(Node* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right; // x's sibling

            if (w && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }

            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->right || w->right->color == BLACK) {
                    if (w->left)
                        w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right)
                    w->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }

        } else {
            // Symmetric case: x is right child
            Node* w = x->parent->left;

            if (w && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }

            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->left || w->left->color == BLACK) {
                    if (w->right)
                        w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left)
                    w->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }

    if (x)
        x->color = BLACK;
}

int RBTree::successor(int value) {
    Node* curr = root;
    Node* succ = nullptr;

    while (curr) {
        if (curr->nodeValue > value) {
            succ = curr;
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return succ ? succ->nodeValue : std::numeric_limits<int>::max(); //weird way to return infinite, but it works i guess...
}

void RBTree::updateReturnPointers(Node* oldNode, Node* newNode, int version) {
    if (oldNode->rParentLeft) {
        oldNode->rParentLeft = oldNode->rParentLeft->addMod(FIELD_LEFT, newNode, version);
    }
    if (oldNode->rParentRight) {
        oldNode->rParentRight = oldNode->rParentRight->addMod(FIELD_RIGHT, newNode, version);
    }
    if (oldNode->rLeftSon) {
        oldNode->rLeftSon = oldNode->rLeftSon->addMod(FIELD_PARENT, newNode, version);
    }
    if (oldNode->rRightSon) {
        oldNode->rRightSon = oldNode->rRightSon->addMod(FIELD_PARENT, newNode, version);
    }
}


void RBTree::print() {
    printTree(root, 0);
    std::cout << std::endl;
}

void RBTree::printTree(Node* node, int indent) {
    const int SPACING = 6;

    if (node == nullptr) {
        std::cout << std::string(indent, ' ') << "null(B)\n";
        return;
    }

    printTree(node->right, indent + SPACING);

    std::cout << std::string(indent, ' ')
              << node->nodeValue << (node->color == RED ? "(R)" : "(B)") << "\n";

    printTree(node->left, indent + SPACING);
}


