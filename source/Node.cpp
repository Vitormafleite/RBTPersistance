#include "../headers/Node.h"

Node::Node(int nodeValue, int versionOnCreation) {
    this->nodeValue = nodeValue;
    this->color = RED;

    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;

    //Return nodes
    this->rParentLeft = nullptr;
    this->rParentRight = nullptr;
    this->rLeftSon = nullptr;
    this->rRightSon = nullptr;

    this->previousNodeVersion = nullptr;

    //Mods 
    this->modCount = 0;
    this->nodeVersion = versionOnCreation;
}

void* Node::getFieldValue(Field field, int version) {
    void* result = nullptr;
    int latestVersion = -1;

    for (int i = 0; i < modCount; ++i) {
        if (modBox[i].field == field && modBox[i].version <= version) {
            if (modBox[i].version > latestVersion) {
                latestVersion = modBox[i].version;
                result = modBox[i].value;
            }
        }
    }

    if (result == nullptr) {
        switch (field) {
            case FIELD_LEFT:
                result = static_cast<void*>(left);
                break;
            case FIELD_RIGHT:
                result = static_cast<void*>(right);
                break;
            case FIELD_PARENT:
                result = static_cast<void*>(parent);
                break;
            case FIELD_COLOR:
                result = static_cast<void*>(&color);
                break;
        }
    }

    return result;
}

Node* Node::addMod(Field field, void* value, int version) {
    if (modCount < MAX_MODS) {
        modBox[modCount].field = field;
        modBox[modCount].value = value;
        modBox[modCount].version = version;
        modCount++;
        return this;
    } else {
        // Mod capacity full so we create copy node
        Node* newNode = this->copyNode(version);

        // Now apply the new mod directly on the new node
        switch (field) {
            case FIELD_LEFT:
                newNode->left = static_cast<Node*>(value);
                break;
            case FIELD_RIGHT:
                newNode->right = static_cast<Node*>(value);
                break;
            case FIELD_PARENT:
                newNode->parent = static_cast<Node*>(value);
                break;
            case FIELD_COLOR:
                newNode->color = *(static_cast<Color*>(value));
                break;
        }

        return newNode;  // Return the new node copy
    }
}

Node* Node::copyNode(int newVersion) {
    // Create new node with same base value and new version
    Node* newNode = new Node(this->nodeValue, newVersion);

    // Copy base fields
    newNode->color = this->color;
    newNode->left = this->left;
    newNode->right = this->right;
    newNode->parent = this->parent;

    //set return to older version
    newNode->previousNodeVersion = this;

    // Copy return pointers
    newNode->rParentLeft = this->rParentLeft;
    newNode->rParentRight = this->rParentRight;
    newNode->rLeftSon = this->rLeftSon;
    newNode->rRightSon = this->rRightSon;

    // Apply all mods valid up to newVersion
    for (int i = 0; i < this->modCount; ++i) {
        if (this->modBox[i].version <= newVersion) {
            Field f = this->modBox[i].field;
            void* val = this->modBox[i].value;

            switch (f) {
                case FIELD_LEFT:
                    newNode->left = static_cast<Node*>(val);
                    break;
                case FIELD_RIGHT:
                    newNode->right = static_cast<Node*>(val);
                    break;
                case FIELD_PARENT:
                    newNode->parent = static_cast<Node*>(val);
                    break;
                case FIELD_COLOR:
                    newNode->color = *(static_cast<Color*>(val));
                    break;
            }
        }
    }

    newNode->modCount = 0;

    return newNode;
}
