#include <stdlib.h>
#include <string.h>
#include "bTreeTable.h"
//#include "pch.h"
//#include "framework.h"

//struct TableDefinition* createTable(char* tableName) {
void createTable(char* tableName)
{
    struct TableDefinition* workTable = malloc(sizeof (struct TableDefinition));
    workTable->columns = 0;
    workTable->tableName = malloc(strlen(tableName));
    workTable->columns = NULL;
//    return workTable;
}