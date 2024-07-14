/*******************************************
 * Name: Posan Gc
 * Assignment 8: Binary Search Tree
 * Purpose of the File: The purpose of this file is to provide the implementation of 
 * the Binary Search Tree (BST) class. This class allows for the creation, manipulation, 
 * and traversal of a binary search tree, which is a data structure that maintains elements 
 * in a sorted order. The BST supports various operations including insertion, deletion, searching,
 *  and different types of tree traversals (pre-order, in-order, and post-order).
*********************************************/

#include "treebin.h"

BinTree::BinTree() {
    root = nullptr;
    count = 0;
}

BinTree::~BinTree() {
    clear();
}

bool BinTree::isEmpty() {
    return root == nullptr;
}

int BinTree::getCount() {
    return count;
}

bool BinTree::getRootData(Data* data) {
    bool retrieved = false;
    if (isEmpty()) {
        data->id = -1;
        data->information = "";
    } else {
        data->id = root->data.id;
        data->information = root->data.information;
        retrieved = true;
    }
    return retrieved;
}

void BinTree::displayTree() {
    std::cout << "DISPLAY TREE ==============================================" << std::endl;
    if (isEmpty()) {
        std::cout << "Tree is empty" << std::endl;
    } else {
        std::cout << "Tree is NOT empty" << std::endl;
    }
    std::cout << "Height " << getHeight() << std::endl;
    std::cout << "Node count: " << getCount() << std::endl;
    std::cout << "Pre-Order Traversal" << std::endl;
    displayPreOrder();
    std::cout << "In-Order Traversal" << std::endl;
    displayInOrder();
    std::cout << "Post-Order Traversal" << std::endl;
    displayPostOrder();
    std::cout << "==============================================" << std::endl;
}

void BinTree::clear() {
    clear(root);
    root = nullptr;
    count = 0;
}

void BinTree::clear(DataNode*& node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }
}

bool BinTree::addNode(int id, const std::string* info) {
    DataNode* newNode = new DataNode();
    newNode->data.id = id;
    newNode->data.information = *info;
    newNode->left = nullptr;
    newNode->right = nullptr;

    bool added = addNode(root, newNode);
    if (added) {
        count++;
    } else {
        delete newNode;
    }
    return added;
}

bool BinTree::addNode(DataNode*& node, DataNode* newNode) {
    bool added = false;
    if (node == nullptr) {
        node = newNode;
        added = true;
    } else if (newNode->data.id < node->data.id) {
        added = addNode(node->left, newNode);
    } else {
        added = addNode(node->right, newNode);
    }
    return added;
}

bool BinTree::removeNode(int id) {
    bool removed = removeNode(id, root) != nullptr;
    if (removed) {
        count--;
    }
    return removed;
}

BinTree::DataNode* BinTree::removeNode(int id, DataNode*& node) {
    if (node == nullptr) return nullptr;

    if (id < node->data.id) {
        node->left = removeNode(id, node->left);
    } else if (id > node->data.id) {
        node->right = removeNode(id, node->right);
    } else {
        if (node->left == nullptr) {
            DataNode* temp = node->right;
            delete node;
            node = nullptr;
            return temp;
        } else if (node->right == nullptr) {
            DataNode* temp = node->left;
            delete node;
            node = nullptr;
            return temp;
        } else {
            DataNode* successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            node->data = successor->data;
            node->right = removeNode(successor->data.id, node->right);
        }
    }
    return node;
}

bool BinTree::getNode(Data* data, int id) {
    return getNode(data, id, root);
}

bool BinTree::getNode(Data* data, int id, DataNode* node) {
    bool found = false;
    if (node != nullptr) {
        if (id < node->data.id) {
            found = getNode(data, id, node->left);
        } else if (id > node->data.id) {
            found = getNode(data, id, node->right);
        } else {
            data->id = node->data.id;
            data->information = node->data.information;
            found = true;
        }
    }
    return found;
}

bool BinTree::contains(int id) {
    return contains(id, root);
}

bool BinTree::contains(int id, DataNode* node) {
    bool found = false;
    if (node != nullptr) {
        if (id < node->data.id) {
            found = contains(id, node->left);
        } else if (id > node->data.id) {
            found = contains(id, node->right);
        } else {
            found = true;
        }
    }
    return found;
}

int BinTree::getHeight() {
    return getHeight(root);
}

int BinTree::getHeight(DataNode* node) {
    int height = 0;
    if (node != nullptr) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        height = 1 + std::max(leftHeight, rightHeight);
    }
    return height;
}

void BinTree::displayPreOrder() {
    displayPreOrder(root);
}

void BinTree::displayPreOrder(DataNode* node) {
    if (node != nullptr) {
        std::cout << node->data.id << " " << node->data.information << std::endl;
        displayPreOrder(node->left);
        displayPreOrder(node->right);
    }
}

void BinTree::displayPostOrder() {
    displayPostOrder(root);
}

void BinTree::displayPostOrder(DataNode* node) {
    if (node != nullptr) {
        displayPostOrder(node->left);
        displayPostOrder(node->right);
        std::cout << node->data.id << " " << node->data.information << std::endl;
    }
}

void BinTree::displayInOrder() {
    displayInOrder(root);
}

void BinTree::displayInOrder(DataNode* node) {
    if (node != nullptr) {
        displayInOrder(node->left);
        std::cout << node->data.id << " " << node->data.information << std::endl;
        displayInOrder(node->right);
    }
}

