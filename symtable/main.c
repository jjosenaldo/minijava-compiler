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

	entry1.id = "a";
	entry2.id = "b";
	entry3.id = "c";
	entry4.id = "d";

	addEntryToTable(table, &entry1);
	addEntryToTable(table, &entry2);
	addEntryToTable(table, &entry3);
	addEntryToTable(table, &entry4);

    return 0;
}