#include "table-content.hpp"

void printTableContent(TableContent content){
    if(content.tag == TCTYPE){
        printType(content.type);
    } else if(content.tag == TCSYMTABLE){
        content.symtable->print();
    }
}