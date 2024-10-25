#include "BTree.h"

/* A basic BTree implementation using a C struct for the key data.  Using a C struct as the key is based on the https://github.com/tidwall/btree.c repo at github.  The tree is not optimized for performance.
*/

extern struct bTree* btree_Create(size_t maxChildren, 
    size_t eleSize, 
    int (*compareFunc)(void* a, void* b)) {
    struct bTree *btree = malloc(sizeof(struct bTree));
    if (btree) {
        btree->height = 0;
        btree->maxChildren = maxChildren;
        // Allocate extra space for "overflow" key 
        // when splitting
        btree->maxKeys = maxChildren; // max items per node. max children is +1
        btree->minKeys = (maxChildren - 1) / 2;
        btree->eleSize = eleSize;
        btree->compare = compareFunc;
        btree->root = btree_Node_New(btree, true);
    }

    return btree;
}

extern void btree_Free(struct bTree* btree) {
    if (btree->root != NULL) {
        free(btree->root);
    }
    //TODO: Add free logic for freeing bTreeNode
    //TODO: Free btreeNode->data
    free(btree);
}

void btree_Shift_KeysRight(struct bTreeNode* node, size_t index, size_t elementSize)
{
    size_t number_ItemsToShift = node->itemCount - index;
    memcpy(node->data + elementSize * (index + 1), node->data + elementSize * index, number_ItemsToShift * elementSize);
}

void btree_Add(struct bTree* bTree, void* udata) {

    // From https://www.cs.utexas.edu/~djimenez/utsa/cs3343/lecture17.html
    struct bTreeNode* root = bTree->root;
    if (root->itemCount == bTree->maxKeys) {
        // uh-oh, the root is full, we have to split it
        struct bTreeNode* splitNode = btree_Node_New(bTree,false); 
        bTree->root = splitNode; 	  // new root node
//        splitNode->isLeaf = false;   // will have some children
        //splitNode->itemCount = 0;	// for now
        splitNode->children[0] = root; // child is the old root node
//      B - Tree - Split - Child(s, 1, r) // r is split
        btree_Node_Split(bTree,splitNode);
        btree_AddData_NotFull(bTree, root, udata);
    } else {
        btree_AddData_NotFull(bTree, root, udata);
    }
}

struct bTreeNode* btree_Node_New(struct bTree* bTree, bool isLeaf) {

    size_t item_offset = sizeof(struct bTreeNode) + (bTree->maxKeys) * bTree->eleSize;
    size_t size = item_offset + (sizeof(struct bTreeNode) * bTree->maxChildren + 1);
    size += item_offset;

    struct bTreeNode* node = malloc(size);
    if (node) {

        memset(node, 0, size);
        //    node->children = NULL;
        node->isLeaf = isLeaf;
        node->maxKeys = bTree->maxKeys;
        node->itemCount = 0;
        node->data = (char *) node + item_offset;

        //if (bTree->root == NULL) {
        //    bTree->root = node;
        //}
    }
    return node;
}

struct bTreeFindResult* btree_Node_Find(struct bTree *bTree, struct bTreeNode *node, void* key) {

    // From https://www.cs.utexas.edu/~djimenez/utsa/cs3343/lecture16.html
    int keyIndex = 1;

    // search for the correct child
    int result = btree_Compare(bTree,key, node, keyIndex);
    while (keyIndex <= node->maxKeys && result > 1) {
        keyIndex++;
        result = btree_Compare(bTree, key, node, keyIndex);
    }

    // now keyIndex is the least index in the key array such that
    // k <= keyi[x], so k will be found here or
    // in the i'th child

    int itemIndex = 1;
    int itemResult = btree_Compare(bTree, key, node, bTree->eleSize);
    while (itemIndex <= node->itemCount && itemResult < 1) {
        itemIndex++;
        itemResult = btree_Compare(bTree, key, node, bTree->eleSize);
    }

    if (itemIndex <= node->itemCount && itemResult == 0) {
        // we found k at this node
//        return (node, keyIndex);
        struct bTreeFindResult *result = malloc(sizeof(struct bTreeFindResult));
        if (result) {
            result->foundNode = node->children[keyIndex];
            result->foundIndex = itemIndex;
        }
        return result;
    }

    if (node->isLeaf) { // Why return NULL if node is a Leaf?
                        // Possibly Because this a Leaf Node & key is NOT in the node?
        return NULL;
    }
    
    // we must read the block before we can work with it
    //Disk - Read(ci[x])
    // Move to next node to check for the key
    keyIndex++;
    return btree_Node_Find(bTree, &(node->children[keyIndex]), key);

}

void btree_Node_Split(struct bTree* bTree, struct bTreeNode* splitNode) {

    //if (splitNode == bTree->root) {
    //    bTree->root->isLeaf = false;
    //}

    //
    //struct bTreeNode *leftNode = btree_Node_New(bTree, true);
    //struct bTreeNode* rightNode = btree_Node_New(bTree, true);


//Left:
//    the first(M - 1) / 2 values
//        Middle :
//    the middle value(position 1 + ((M - 1) / 2)
//                     Right:
//    the last(M - 1) / 2 values

}

void* btree_Node_GetItem(struct bTreeNode* node, size_t elementSize, size_t index) {
    return node->data + (elementSize * index--);
}

void btree_Node_SetItem(struct bTreeNode* node, size_t elementSize, size_t index, void *userData) {
    void* keyP = node->data + (elementSize * (index));
    memcpy(keyP, userData, elementSize);
}

//enum NodeActions btree_AddData_NotFull(struct bTree* bTree, struct bTreeNode* node, void* userData) {
void btree_AddData_NotFull(struct bTree* bTree, struct bTreeNode* node, void* userData) {

    //*if (node->itemCount == bTree->maxKeys) {
    //    return NEEDS_SPLIT;
    //}*/

    //char* itemP = node->data;
    //int size = node->itemCount;
    //size_t elementSize = bTree->eleSize;
    //int result = bTree->compare(userData, itemP, elementSize);

    //while (size > 0 && result == 1) {
    //    itemP += elementSize;
    //    size--;
    //    result = bTree->compare(userData, itemP, elementSize);
    //}

    //char* endItemP = node->data + (elementSize * node->maxKeys);
    //int moveSize = (endItemP - itemP) - elementSize;
    //memmove(itemP + elementSize, itemP, moveSize);

    //memmove(itemP, userData, elementSize);
    //node->itemCount++;
    //
    //if (node->itemCount == bTree->maxKeys) {
    //    return NEEDS_SPLIT;
    //}
    //else {
    //    return ITEM_ADDED;
    //}

    // From https://www.cs.utexas.edu/~djimenez/utsa/cs3343/lecture17.html Pseudocode
    // i = n[x]
    //    size_t index = node->maxKeys;
    size_t index = node->itemCount;
    size_t keyIndex = 0;
    if (node->isLeaf) {

        // shift everything over to the "right" up to the
        // point where the new key k should go
//        int result = btree_Compare(bTree, userData, node, index);
//        void *firstKey = btree_Node_GetItem(node, bTree->eleSize, index + 1);
        void* nodeKey = btree_Node_GetItem(node, bTree->eleSize, keyIndex);
        int result = btree_Compare_Void(bTree, userData, nodeKey);
//        int result = btree_Compare(bTree, node->data, node, index);         

//        while (index >= 1 && k < keyi[x]) {
        while(index >= 1 && result == 1 ) {
            //keyi + 1[x] = keyi[x];
            index--;
            keyIndex++;
//            result = btree_Compare(bTree, userData, node, index);
//            firstKey = btree_Node_GetItem(node, bTree->eleSize, index + 1);
            nodeKey = btree_Node_GetItem(node, bTree->eleSize, keyIndex);
            result = btree_Compare_Void(bTree, userData, nodeKey);
        }
//        if (node->itemCount > 0) {
//            index++;
            btree_Shift_KeysRight(node, keyIndex, bTree->eleSize);
//        }


        // stick k in its right place and bump up n[x]
//        keyi + 1[x] = k;
        btree_Node_SetItem(node, bTree->eleSize, keyIndex, userData);
        node->itemCount++;
    }
    else {

        // find child where new key belongs:
        int childResult = btree_Compare(bTree, userData, node, index);
        //        while (index >= 1 && userData < keyi[x]) {
        while (index >= 1 && childResult == -1) {
            index--;
        }

        // if k is in ci[x], then k <= keyi[x] (from the definition)
        // we'll go back to the last key (least i) where we found this
        // to be true, then read in that child node

        index++;
        // Disk - Read(ci[x])
        struct bTreeNode* childNode = node->children[index];
        //        if (n[ci[x]] = 2t - 1) {
        if (childNode->itemCount == bTree->maxKeys) {

            // uh-oh, this child node is full, we'll have to split it
            btree_Node_Split(bTree, childNode);
            //B - Tree - Split - Child(x, i, ci[x])

            // now ci[x] and ci+1[x] are the new children, 
            // and keyi[x] may have been changed. 
            // we'll see if k belongs in the first or the second

            int result = btree_Compare(bTree, userData, childNode, index);
            //            if (k > keyi[x]) {
            if (result == 1) {
                index++;
            }

            // call ourself recursively to do the insertion
            btree_AddData_NotFull(bTree, childNode, userData);
            //          B - Tree - Insert - Nonfull(ci[x], k)
        }
    }
}

int btree_Compare(struct bTree* bTree, void* userData, struct bTreeNode* node, size_t index) {

    void* nodeData = btree_Node_GetItem(node, bTree->eleSize, index);
    return bTree->compare(userData, nodeData);
}

int btree_Compare_Void(struct bTree *bTree, void *firstKey, void *secondKey) {

//    void* nodeData = btree_Node_GetItem(node, bTree->eleSize, index);
    return bTree->compare(firstKey, secondKey);
}