#include "types.h"
#include "symtable.h"
#include <stdio.h>

int main(){
    // Type* t1 = MkTypeVoid();
    // Type* t2 = MkTypeInt();
    // Type* t3 = MkTypeInt();
    // TypeList* list = MkTypeList();
    // addTypeToList(list, t1);
    // addTypeToList(list, t2);
    // addTypeToList(list, t3);
    // printTypeList(list);
	TableEntryList* table = createSymTable();
	TableEntry entry1;
	TableEntry entry2;
	TableEntry entry3;
	TableEntry entry4;
	TableEntry entry5;
	TableEntry entry6;
	TableEntry entry7;
	TableEntry entry8;

	entry1.id = "JSDFH82384JH_jasjd";
	entry2.id = "bfsd7f763724HHAA__sda7sd";
	entry3.id = "JSDFH";
	entry4.id = "dsdf";
	entry5.id = "e111xx";
	entry6.id = "wild_";
	entry7.id = "myVar2";
	entry8.id = "myVar1";

	addEntryToTable(table, &entry1);
	addEntryToTable(table, &entry2);
	addEntryToTable(table, &entry3);
	addEntryToTable(table, &entry4);
	addEntryToTable(table, &entry5);
	addEntryToTable(table, &entry6);
	addEntryToTable(table, &entry7);
	addEntryToTable(table, &entry8);

	printTable(table);

    return 0;
}