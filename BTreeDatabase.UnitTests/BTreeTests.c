#include "BTreeTest.h"
#include "meal.h"

// Modeled on qsort compare should return:
// < 0) : Less than zero, if the element pointed by p1 goes before the element pointed by p2.
// (0) : Zero, if the element pointed by p1 is equivalent to the element pointed by p2.
// (> 0) : Greater than zero, if the element pointed by p1 goes after the element pointed by p2.
int compareInts(void* inta, void* intb) {

    int* a = inta;
    int* b = intb;
    return  (*a > *b) - (*a < *b);
}

int compareMeal(void* a, void* b) {
    struct meal *mealA = a;
    struct meal *mealB = b;
//    printf("meal a is: %s", mealA->name);
//    printf("meal b is: %s", mealB->name);
    return 0;
}

int main(int argc, char** argv) {
   // test_Create();
      test_Add();
//      test_btree_addDataItem();
//    test_Compare();
      exit(0);
}

// For Coding only, I don't think this will be a permanent test
void test_btree_addDataItem() {

    const int NUMB_INTS = 3;
    struct bTree* bTree = btree_Create(NUMB_INTS, sizeof(int), compareInts);
    int* data = alloc_TestData(NUMB_INTS, sizeof(int));

    for (int ix = 0; ix < NUMB_INTS; ix++) {
        data[ix] = ix;
    }
    shuffle(data, NUMB_INTS, sizeof(int));

    struct bTreeNode* node = btree_Node_New(bTree, true);

    printf("\n data:");
    for (int ix = 0; ix < NUMB_INTS; ix++) {
        printf("% d", *(int*)&data[ix]);
//        btree_AddDataItemSorted(bTree, node, &data[ix]);
        btree_Add(bTree, &data[ix]);
    }

    printf("\n keys:");
    char* item = node->data;
    for (int ix = 0; ix < node->itemCount; ix++) {
        printf("%d,", *(int*) item);
        item = item + bTree->eleSize;
    }
    const int five = 5;
    btree_Add(bTree, &five);
}

void test_Create() {
    // TODO: Is this test worth keeping?
     struct bTree* bTree = btree_Create(4, sizeof(int), compareInts);
     assert(bTree != NULL);
     assert(bTree->root == NULL);
     assert(bTree->height == 0);
     assert(bTree->maxKeys == 4);
     assert(bTree->compare == compareInts);
     btree_Free(bTree);

     bTree = btree_Create(3,sizeof(int),compareInts);
     assert(bTree != NULL);
     assert(bTree->root == NULL);
     assert(bTree->height == 0);
     assert(bTree->maxKeys == 3);
     assert(bTree->compare == compareInts);

     printf("\ntest_Create() passed!");
}

void test_Add() {
    const int MAX_NODE_KEYS = 3;
    const int MAX_DATA_ITEMS = 50;
    int *data = alloc_TestData(MAX_DATA_ITEMS, sizeof(int));

    printf("\n data:");
    for (int ix = 0; ix < MAX_DATA_ITEMS; ix++) {
        data[ix] = ix;
        printf("%d,",data[ix]);
    }

    shuffle(data,MAX_DATA_ITEMS, sizeof(int));

    struct bTree *bTree = btree_Create(3, sizeof(int), compareInts);
#define TEST_DEBUG
#ifdef TEST_DEBUG
    printf("\nmaxKeys: %d", (int) bTree->maxKeys);

    printf("\n shuffled data:");
    for (int ix = 0; ix < MAX_DATA_ITEMS; ix++) {
        printf("%d,", *(int*)&data[ix]);
    }
#endif // DEBUG

    for (int ix = 0; ix < MAX_NODE_KEYS; ix++) {
        btree_Add(bTree, &data[ix]);
    }

    struct bTreeNode* node = bTree->root;
#ifdef TEST_DEBUG
    char* item = node->data;
    printf("\n keys: ");
    for (int ix = 0; ix < MAX_NODE_KEYS; ix++) {
//        printf("%d,", *(int*)item);
        printf("%d,", *(int *) item);
        item = item + bTree->eleSize;
//        item++;
    }

    printf("\n shuffled data:");
    for (int ix = 0; ix < MAX_DATA_ITEMS; ix++) {
        printf("%d,", *(int*)&data[ix]);
    }

#endif
    assert(node->itemCount == MAX_NODE_KEYS);
    assert(node->maxKeys == MAX_NODE_KEYS);
    
#define EXCLUDE
#ifndef EXCLUDE

    // Split Root Node
    for (int ix = MAX_NODE_KEYS + 1; ix < MAX_NODE_KEYS + 4; ix++) {
#ifdef TEST_DEBUG
        printf("\nadding %d\n", data[ix]);
#endif
        btree_Add(bTree, &data[ix]);
    }
#endif // EXCLUDE
    free_TestData(data);
}

//struct void test_Compare() {
//
//}