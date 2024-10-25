#pragma once

enum ColumnType {Int = 0, Char = 1, Varchar = 2};
struct TableDefinition {
    char*                    tableName;
    unsigned char            numberColumns;
    struct ColumnDefinition* columns;
};

struct ColumnDefinition {
    unsigned char   number;
    char*           name;
    enum ColumnType type;
    unsigned char   Size;
};

//struct TableDefinition* createTable(char* tableName);
void createTable(char* tableName);
void addColumn(enum ColumnType type, char* columnName);
void dropTable(char* tableName);
void exportCommaSeparated(char* tableName, char* csvFileName);
void importCommaSeparated(char* csvFileName, char* tableName);
