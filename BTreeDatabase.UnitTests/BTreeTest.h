#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

//#define TEST_DEBUG
int main(int argc, char** argv);

// Function Prototypes
void test_Create();
void test_Add();
void test_btree_addDataItem();
//void test_Create();

// Test Data Generation
// Credit tidwall\tests.h for the idea and purpose of the functions.  The implementation is my own.

// Allocates a memory block for test data
// numberOfItems is the number of items to allocate
// itemSize is the size of each item in bytes
void* alloc_TestData(size_t numberItems, size_t itemSize) {
    void* array = calloc(numberItems, itemSize);
    return array;
}

void free_TestData(void* block) {
    free(block);
}

// Ported from tidwall\btree implementation 
// Pseudo shuffles or randomizes a fixed array of
// items
// array the input array to be shuffled
// numberElements the number of items in the array
// elementSize size of each array entry
static void shuffle(void* array, size_t numberElements, size_t elementSize) {
    if (numberElements < 2) return; 

    char *tmp = calloc(elementSize, numberElements);
    char *arr = array;
    for (size_t i = 0; i < numberElements - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (numberElements - i) + 1);
        memcpy(tmp, arr + j * elementSize, elementSize);
        memcpy(arr + j * elementSize, arr + i * elementSize, elementSize);
        memcpy(arr + i * elementSize, tmp, elementSize);
    }
}