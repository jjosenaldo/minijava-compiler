#include <iostream>
#include "type/type.hpp"
#include "symtable/symtable.hpp"


using std::cout;
using std::endl;

int main(){
    Type* t1 = MkTypeInt();
    TableContent tc1;
    tc1.tag = TCTYPE;
    tc1.type = t1;

    Type* t2 = MkTypeBoolean();
    TableContent tc2;
    tc2.tag = TCTYPE;
    tc2.type = t2;

    Type* t3 = MkTypeClass("Cat");
    TableContent tc3;
    tc3.tag = TCTYPE;
    tc3.type = t3;

    Symtable* table1 = new Symtable();
    table1->insert("myInt", tc1);
    table1->insert("myBool", tc2);
    table1->insert("cat", tc3);

    Symtable* table2 = new Symtable();
    TableContent tc4;
    tc4.tag = TCSYMTABLE;
    tc4.symtable = table1;

    table2->insert("myTable", tc4);
    table2->insert("myInt", tc1);

    table2->print();
    cout << endl;

    delete table1;
    delete table2;

    return 0;
}