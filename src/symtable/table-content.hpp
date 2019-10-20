#ifndef TABLECONTENT_HPP
#define TABLECONTENT_HPP

#include "type.hpp"

// Forward declaration
class Symtable;

enum TableContentTag{
    TCTYPE,
    TCSYMTABLE,
    TCNOCONTENT
};

struct TableContent{
    TableContentTag tag;

    union{
        Symtable* symtable;
        Type* type;
    };
};


void printTableContent(TableContent content);

#include "../symtable/symtable.hpp"

#endif