/*******************************************
 * Name: Posan Gc
 * Assignment 8: Binary Search Tree
 * Purpose of File: The purpose of this file is to provide the declaration of 
 * the Binary Search Tree (BST) class. This class allows for the creation, manipulation, 
 * and traversal of a binary search tree, which is a data structure that maintains elements 
 * in a sorted order. The BST supports various operations including insertion, deletion, searching,
 *  and different types of tree traversals (pre-order, in-order, and post-order).
*********************************************/

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H

#include "adata.h"
#include <iostream>

/*********************************************
This class defines a Binary Search Tree (BST). 
It allows for the creation and management of a 
binary search tree where nodes are inserted in 
a sorted manner. The tree supports various 
operations including adding, deleting, retrieving 
nodes, and performing different types of tree 
traversals (pre-order, in-order, and post-order).

@attrib root : the pointer to the root node of the tree
@attrib count : the number of nodes in the tree
*********************************************/
class BinTree {
private:
    struct DataNode {
        Data data;
        DataNode* left;
        DataNode* right;
    };

    DataNode* root;
    int count; 

    void clear(DataNode*&);
    bool addNode(DataNode*&, DataNode*);
    DataNode* removeNode(int, DataNode*&);
    bool getNode(Data*, int, DataNode*);
    bool contains(int, DataNode*);
    int getHeight(DataNode*);
    void displayPreOrder(DataNode*);
    void displayPostOrder(DataNode*);
    void displayInOrder(DataNode*);

public: 
    /**********************
    Constructors/Destructor
    ***********************/
    BinTree();
    ~BinTree();

    /**********************
    Getters/Accessors
    ***********************/
    bool isEmpty();
    int getCount();
    bool getRootData(Data*);
    void displayTree();
    bool getNode(Data*, int);
    bool contains(int);
    int getHeight();

    /**********************
    Setters/Mutators
    ***********************/
    void clear();
    bool addNode(int, const std::string*);
    bool removeNode(int);

    /**********************
    Tree Traversal Methods
    ***********************/
    void displayPreOrder();
    void displayPostOrder();
    void displayInOrder();
};

#endif /* BINTREE_BINTREE_H */
