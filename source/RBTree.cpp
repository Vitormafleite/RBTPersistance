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

    //if (node->nodeValue < root->nodeValue) {
    //    root->left = BinarySearchInsert(root->left, node);
    //    root->left->parent = root;
    //} else {
    //    root->right = BinarySearchInsert(root->right, node);
    //    root->right->parent = root;
    //}

    if (node->nodeValue < root->nodeValue) {
        Node* leftChild = BinarySearchInsert(getLeft(root, currentVersion), node);
        root = setLeft(root, leftChild, currentVersion);
        if (leftChild != nullptr)
            setParent(leftChild, root, currentVersion);
    } else {
        Node* rightChild = BinarySearchInsert(getRight(root, currentVersion), node);
        root = setRight(root, rightChild, currentVersion);
        if (rightChild != nullptr)
            setParent(rightChild, root, currentVersion);
    }

    return root;
}


//IMPLEMENTATIONS FOR REGULAR RBTREE WITHOUT PARTIAL PERSISTANCE
//void RBTree::rotateLeft(Node* x) {
//    Node* y = x->right;
//    x->right = y->left;
//    if (y->left)
//        y->left->parent = x;
//
//    y->parent = x->parent;
//
//    if (!x->parent)
//        root = y;
//    else if (x == x->parent->left)
//        x->parent->left = y;
//    else
//        x->parent->right = y;
//
//    y->left = x;
//    x->parent = y;
//}
//
//void RBTree::rotateRight(Node* x) {
//    Node* y = x->left;
//    x->left = y->right;
//    if (y->right)
//        y->right->parent = x;
//
//    y->parent = x->parent;
//
//    if (!x->parent)
//        root = y;
//    else if (x == x->parent->right)
//        x->parent->right = y;
//    else
//        x->parent->left = y;
//
//    y->right = x;
//    x->parent = y;
//}

void RBTree::rotateLeft(Node* x) {
    Node* y = getRight(x, currentVersion);

    Node* yLeft = getLeft(y, currentVersion);
    x = setRight(x, yLeft, currentVersion);

    if (yLeft != nullptr)
        setParent(yLeft, x, currentVersion);

    Node* xParent = getParent(x, currentVersion);
    y = setParent(y, xParent, currentVersion);

    if (xParent == nullptr) {
        root = y;
    } else if (x == getLeft(xParent, currentVersion)) {
        setLeft(xParent, y, currentVersion);
    } else {
        setRight(xParent, y, currentVersion);
    }

    y = setLeft(y, x, currentVersion);
    x = setParent(x, y, currentVersion);
}

void RBTree::rotateRight(Node* x) {
    Node* y = getLeft(x, currentVersion);

    Node* yRight = getRight(y, currentVersion);
    x = setLeft(x, yRight, currentVersion);

    if (yRight != nullptr)
        setParent(yRight, x, currentVersion);

    Node* xParent = getParent(x, currentVersion);
    y = setParent(y, xParent, currentVersion);

    if (xParent == nullptr) {
        root = y;
    } else if (x == getRight(xParent, currentVersion)) {
        setRight(xParent, y, currentVersion);
    } else {
        setLeft(xParent, y, currentVersion);
    }

    y = setRight(y, x, currentVersion);
    x = setParent(x, y, currentVersion);
}

//void RBTree::fixInsert(Node* node) {
//    while (node != root && node->parent->color == RED) {
//        Node* parent = node->parent;
//        Node* grandparent = parent->parent;
//
//        if (parent == grandparent->left) {
//            Node* uncle = grandparent->right;
//
//            if (uncle && uncle->color == RED) {
//                parent->color = BLACK;
//                uncle->color = BLACK;
//                grandparent->color = RED;
//                node = grandparent;
//            } else {
//                if (node == parent->right) {
//                    node = parent;
//                    rotateLeft(node);
//                }
//                parent->color = BLACK;
//                grandparent->color = RED;
//                rotateRight(grandparent);
//            }
//        } else {
//            Node* uncle = grandparent->left;
//
//            if (uncle && uncle->color == RED) {
//                parent->color = BLACK;
//                uncle->color = BLACK;
//                grandparent->color = RED;
//                node = grandparent;
//            } else {
//                if (node == parent->left) {
//                    node = parent;
//                    rotateRight(node);
//                }
//                parent->color = BLACK;
//                grandparent->color = RED;
//                rotateLeft(grandparent);
//            }
//        }
//    }
//
//    root->color = BLACK;
//}

void RBTree::fixInsert(Node* node) {
    while (node != root && 
           getParent(node, currentVersion) != nullptr && 
           getColor(getParent(node, currentVersion), currentVersion) == RED) {
        Node* parent = getParent(node, currentVersion);
        if (!parent) break;  // safety check

        Node* grandparent = getParent(parent, currentVersion);
        if (!grandparent) break;  // safety check

        if (parent == getLeft(grandparent, currentVersion)) {
            Node* uncle = getRight(grandparent, currentVersion);

            if (uncle != nullptr && getColor(uncle, currentVersion) == RED) {
                setColor(parent, BLACK, currentVersion);
                setColor(uncle, BLACK, currentVersion);
                setColor(grandparent, RED, currentVersion);
                node = grandparent;
            } else {
                if (node == getRight(parent, currentVersion)) {
                    node = parent;
                    rotateLeft(node);
                }
                setColor(parent, BLACK, currentVersion);
                setColor(grandparent, RED, currentVersion);
                rotateRight(grandparent);
            }
        } else {
            Node* uncle = getLeft(grandparent, currentVersion);

            if (uncle != nullptr && getColor(uncle, currentVersion) == RED) {
                setColor(parent, BLACK, currentVersion);
                setColor(uncle, BLACK, currentVersion);
                setColor(grandparent, RED, currentVersion);
                node = grandparent;
            } else {
                if (node == getLeft(parent, currentVersion)) {
                    node = parent;
                    rotateRight(node);
                }
                setColor(parent, BLACK, currentVersion);
                setColor(grandparent, RED, currentVersion);
                rotateLeft(grandparent);
            }
        }
    }
    setColor(root, BLACK, currentVersion);
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

// PRINT FOR NORMAL RBTREE NO PERSISTANCE
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

void RBTree::printVersion(int version) {
    std::cout << "=== Tree at version " << version << " ===" << std::endl;
    printTreeVersioned(root, version, 0);
    std::cout << std::endl;
}

void RBTree::printTreeVersioned(Node* node, int version, int indent) {
    const int SPACING = 6;

    if (node == nullptr) {
        std::cout << std::string(indent, ' ') << "null(B)\n";
        return;
    }

    printTreeVersioned(getRight(node, version), version, indent + SPACING);

    std::cout << std::string(indent, ' ')
              << node->nodeValue << (getColor(node, version) == RED ? "(R)" : "(B)") << " [v" << node->nodeVersion << "]\n";

    printTreeVersioned(getLeft(node, version), version, indent + SPACING);
}

Node* RBTree::getLeft(Node* node, int version) {
    return static_cast<Node*>(node->getFieldValue(FIELD_LEFT, version));
}

Node* RBTree::getRight(Node* node, int version) {
    return static_cast<Node*>(node->getFieldValue(FIELD_RIGHT, version));
}

Node* RBTree::getParent(Node* node, int version) {
    return static_cast<Node*>(node->getFieldValue(FIELD_PARENT, version));
}

Color RBTree::getColor(Node* node, int version) {
    return *static_cast<Color*>(node->getFieldValue(FIELD_COLOR, version));
}

Node* RBTree::setLeft(Node* parent, Node* child, int version) {
    parent->addMod(FIELD_LEFT, static_cast<void*>(child), version);

    if (child != nullptr) {
        child->rParentLeft = parent;
    }

    return parent;
}

Node* RBTree::setRight(Node* parent, Node* child, int version) {
    parent->addMod(FIELD_RIGHT, static_cast<void*>(child), version);

    if (child != nullptr) {
        child->rParentRight = parent;
    }

    return parent;
}

Node* RBTree::setParent(Node* child, Node* parent, int version) {
    if (child == nullptr) return child;

    child->addMod(FIELD_PARENT, static_cast<void*>(parent), version);

    if (parent != nullptr) {
        if (getLeft(parent, version) == child) {
            child->rParentLeft = parent;
        } else if (getRight(parent, version) == child) {
            child->rParentRight = parent;
        }
    }

    return child;
}


Node* RBTree::setColor(Node* node, Color color, int version) {
    node->addMod(FIELD_COLOR, static_cast<void*>(&color), version);
    return node;
}

