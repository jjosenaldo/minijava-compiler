#ifndef SYMTABLE_H
#define SYMTABLE_H

#define TABLE_SIZE 10

#include "types.h"

typedef enum Kind{
	_VAR,
	_FUNCTION,
	_CLASS
} Kind;

typedef struct TableEntry{
	char* id;
	Type type;
	Kind kind;
} TableEntry;


typedef struct TableEntryNode{
    TableEntry* tableEntry;
    struct TableEntryNode* next;
} TableEntryNode;

typedef struct TableEntryList{
    TableEntryNode* head;
} TableEntryList;


TableEntryList* createSymTable();


int hashString(char* string);


// List methods
void addEntryToList(TableEntryList* list, TableEntry* entry);
void removeEntryFromList(TableEntryList* list, char* id);
TableEntry* getEntryFromList(TableEntryList* list, char* id);
void printList(TableEntryList* list);

// Table methods
void addEntryToTable(TableEntryList* table, TableEntry* entry);
void removeEntryFromTable(TableEntryList* table, char* id);
TableEntry* getEntryFromTable(TableEntryList* table, char* id);
void printTable(TableEntryList* table);

// Symbol table
TableEntryList* symTable;

#endif
