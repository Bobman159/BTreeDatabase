#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum NodeActions {ITEM_ADDED, NEEDS_SPLIT};

struct bTree {
    struct bTreeNode* root;       //Root node NULL if no tree
    size_t height;      // Height of tree
    size_t maxChildren; // Max number of children per node
    size_t maxKeys;     // Max number of keys per node;
    size_t minKeys;     // Min number of keys per node;
    size_t eleSize;     // Size of data elements
    int (*compare)(void* a, void* b);   //User compare function pointer
};

struct bTreeNode {
    size_t maxKeys;     // max # of data items - 
                        // constant for each node
    size_t itemCount;   // current # of data items
    bool isLeaf;        // true if node is a leaf node 
    char* data;         // data items
    struct bTreeNode *children[];
};

struct bTreeFindResult {
    size_t  foundIndex;   // index of key in the node (not zero based?)
    struct bTreeNode    *foundNode;   // 
};

// Function Prototypes 
// 
// Creates a new bTree for use
// Param keySize is max number of keys per node
// Param eleSize is size of each element
// Param compare is the compare callback function. See qsort documentation for return value information.
//
extern struct bTree* btree_Create(size_t keySize, size_t eleSize, int (*compare)(void* a, void* b));

// Add a new item to the tree
// Param bTree is the bTree for the item to be added
// Param udata is the user data to be added
extern void btree_Add(struct bTree* bTree, void* udata);

// Frees the btree and all items in the tree.
extern void btree_Free(struct bTree*);

struct bTreeNode* btree_Node_New(struct bTree* bTree, bool isLeaf);
void btree_Node_Split(struct bTree *bTree, struct bTreeNode *splitNode);
struct bTreeFindResult* btree_Node_Find(struct bTree* bTree, struct bTreeNode *node, void* key);
void * btree_Node_GetItem(struct bTreeNode* node, size_t elementSize, size_t index);
void  btree_Node_SetItem(struct bTreeNode* node, size_t elementSize, size_t index, void* userData);


// Adds data item to a btreeNode keeping the item keys in
// sorted order. If the node is full indicate the node must
// be split.
// Param bTree is the bTree for the item to be added
// Param node is the bTreeNode to add item to.
// Param udata is the user data to be added
//enum NodeActions btree_AddData_NotFull(struct bTree *bTree, struct bTreeNode *node, void *userData);
void btree_AddData_NotFull(struct bTree* bTree, struct bTreeNode* node, void* userData);

// Work Functions
struct bTreeNode *btree_Get_Root(struct bTree* bTree);
int btree_Compare(struct bTree *bTree, void* userData, struct bTreeNode* nodeData, size_t index);
//void btree_Shift_KeysRight(struct bTreeNode *node);
//struct btree_FindResult btree_Alloc_Node_FindResult(struct bTreeNode* foundNode, size_t foundIndex);