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

/*********************************************
* This constructor initializes the binary search tree
* by setting the root to nullptr and the count to 0.
*
* @param none
* @exception none
* @return void
*********************************************/
BinTree::BinTree() {
    root = nullptr;
    count = 0;
}

/*********************************************
* This destructor calls clear() to delete
* all nodes and free memory.
*
* @param none
* @exception none
* @return void
*********************************************/
BinTree::~BinTree() {
    clear();
}

/*********************************************
* This method checks if the tree is empty.
*
* @param none
* @exception none
* @return bool : true if the tree is empty, false otherwise
*********************************************/
bool BinTree::isEmpty() {
    return root == nullptr;
}

/*********************************************
* This method returns the count of nodes in the tree.
*
* @param none
* @exception none
* @return int : the count of nodes in the tree
*********************************************/
int BinTree::getCount() {
    return count;
}

/*********************************************
* This method retrieves the data of the root node.
* If the tree is not empty, it fills the given Data 
* struct with the root's data. Otherwise, it sets the 
* Data struct to indicate an empty tree.
*
* @param Data* data : pointer to a Data struct to store the root data
* @exception none
* @return bool : true if the root data was retrieved, false otherwise
*********************************************/
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

/*********************************************
* This method displays the tree's statistics and 
* performs all traversal methods to print the tree nodes.
*
* @param none
* @exception none
* @return void
*********************************************/
void BinTree::displayTree() {
    std::cout << "DISPLAY TREE ==============================================" << std::endl;
    if (isEmpty()) {
        std::cout << "Tree is empty" << std::endl;
    } else {
        std::cout << "Tree is NOT empty" << std::endl;
    }
    std::cout << "Height " << getHeight() << std::endl;
    std::cout << "Node count: " << getCount() << std::endl;
    std::cout << "Pre-Order Traversal ";
    displayPreOrder();
    std::cout << "In-Order Traversal ";
    displayInOrder();
    std::cout << "Post-Order Traversal ";
    displayPostOrder();
    std::cout << "==============================================" << std::endl;
}

/*********************************************
* This method clears the tree by deallocating all nodes
* and resetting the root and count.
*
* @param none
* @exception none
* @return void
*********************************************/
void BinTree::clear() {
    clear(root);
    root = nullptr;
    count = 0;
}

/*********************************************
* This private method recursively deallocates all nodes 
* in the tree starting from the given node.
*
* @param DataNode*& node : reference to a pointer to a DataNode
* @exception none
* @return void
*********************************************/
void BinTree::clear(DataNode*& node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }
}

/*********************************************
* This method adds a new node with the given id and
* information to the tree. It dynamically allocates 
* memory for the new node and inserts it in the 
* appropriate position to maintain the BST properties.
*
* @param int id : integer ID for the Data struct
* @param const std::string* info : pointer to string information for the Data struct
* @exception none
* @return bool : true if the node was successfully added, false otherwise
*********************************************/
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

/*********************************************
* This private method recursively adds a new node 
* to the tree, maintaining the BST properties.
*
* @param DataNode*& node : reference to a pointer to the current node
* @param DataNode* newNode : pointer to the new node to be added
* @exception none
* @return bool : true if the node was successfully added, false otherwise
*********************************************/
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

/*********************************************
* This method removes a node with the given id from 
* the tree. It calls the private recursive method 
* to perform the deletion and updates the node count.
*
* @param int id : integer ID of the node to remove
* @exception none
* @return bool : true if the node was successfully removed, false otherwise
*********************************************/
bool BinTree::removeNode(int id) {
    bool removed = removeNode(id, root) != nullptr;
    if (removed) {
        count--;
    }
    return removed;
}

/*********************************************
* This private method recursively removes a node 
* with the given id from the tree, maintaining the 
* BST properties.
*
* @param int id : integer ID of the node to remove
* @param DataNode*& node : reference to a pointer to the current node
* @exception none
* @return DataNode* : pointer to the removed node, or nullptr if not found
*********************************************/
BinTree::DataNode* BinTree::removeNode(int id, DataNode*& node) {
    DataNode* result = nullptr;
    if (node != nullptr) {
        if (id < node->data.id) {
            node->left = removeNode(id, node->left);
        } else if (id > node->data.id) {
            node->right = removeNode(id, node->right);
        } else {
            DataNode* temp = node;
            if (node->left == nullptr) {
                node = node->right;
            } else if (node->right == nullptr) {
                node = node->left;
            } else {
                DataNode* successor = node->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                node->data = successor->data;
                node->right = removeNode(successor->data.id, node->right);
            }
            delete temp;
            result = node;
        }
    }
    return result;
}

/*********************************************
* This method retrieves the node with the given id 
* from the tree. It calls the private recursive method 
* to perform the search.
*
* @param Data* data : pointer to a Data struct to store the retrieved data
* @param int id : integer ID of the node to retrieve
* @exception none
* @return bool : true if the node was found, false otherwise
*********************************************/
bool BinTree::getNode(Data* data, int id) {
    return getNode(data, id, root);
}

/*********************************************
* This private method recursively retrieves the node 
* with the given id from the tree.
*
* @param Data* data : pointer to a Data struct to store the retrieved data
* @param int id : integer ID of the node to retrieve
* @param DataNode* node : pointer to the current node
* @exception none
* @return bool : true if the node was found, false otherwise
*********************************************/
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

/*********************************************
* This method checks if a node with the given id 
* exists in the tree.
*
* @param int id : integer ID to check for
* @exception none
* @return bool : true if a node with the given id exists, false otherwise
*********************************************/
bool BinTree::contains(int id) {
    return contains(id, root);
}

/*********************************************
* This private method recursively checks if a node 
* with the given id exists in the tree.
*
* @param int id : integer ID to check for
* @param DataNode* node : pointer to the current node
* @exception none
* @return bool : true if a node with the given id exists, false otherwise
*********************************************/
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

/*********************************************
* This method returns the height of the tree.
*
* @param none
* @exception none
* @return int : the height of the tree
*********************************************/
int BinTree::getHeight() {
    return getHeight(root);
}

/*********************************************
* This private method recursively calculates the height 
* of the tree starting from the given node.
*
* @param DataNode* node : pointer to the current node
* @exception none
* @return int : the height of the tree
*********************************************/
int BinTree::getHeight(DataNode* node) {
    int height = 0;
    if (node != nullptr) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        height = 1 + std::max(leftHeight, rightHeight);
    }
    return height;
}

/*********************************************
* This method performs a pre-order traversal of 
* the tree and prints each node's data.
*
* @param none
* @exception none
* @return void
*********************************************/
void BinTree::displayPreOrder() {
    displayPreOrder(root);
}

/*********************************************
* This private method recursively performs a pre-order 
* traversal of the tree and prints each node's data.
*
* @param DataNode* node : pointer to the current node
* @exception none
* @return void
*********************************************/
void BinTree::displayPreOrder(DataNode* node) {
    if (node != nullptr) {
        std::cout << node->data.id << " " << node->data.information << std::endl;
        displayPreOrder(node->left);
        displayPreOrder(node->right);
    }
}

/*********************************************
* This method performs a post-order traversal of 
* the tree and prints each node's data.
*
* @param none
* @exception none
* @return void
*********************************************/
void BinTree::displayPostOrder() {
    displayPostOrder(root);
}

/*********************************************
* This private method recursively performs a post-order 
* traversal of the tree and prints each node's data.
*
* @param DataNode* node : pointer to the current node
* @exception none
* @return void
*********************************************/
void BinTree::displayPostOrder(DataNode* node) {
    if (node != nullptr) {
        displayPostOrder(node->left);
        displayPostOrder(node->right);
        std::cout << node->data.id << " " << node->data.information << std::endl;
    }
}

/*********************************************
* This method performs an in-order traversal of 
* the tree and prints each node's data.
*
* @param none
* @exception none
* @return void
*********************************************/
void BinTree::displayInOrder() {
    displayInOrder(root);
}

/*********************************************
* This private method recursively performs an in-order 
* traversal of the tree and prints each node's data.
*
* @param DataNode* node : pointer to the current node
* @exception none
* @return void
*********************************************/
void BinTree::displayInOrder(DataNode* node) {
    if (node != nullptr) {
        displayInOrder(node->left);
        std::cout << node->data.id << " " << node->data.information << std::endl;
        displayInOrder(node->right);
    }
}
