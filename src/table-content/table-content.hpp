#ifndef TABLECONTENT_HPP
#define TABLECONTENT_HPP

#include "../symtable/symtable.hpp"
#include "../type/type.hpp"

union TableContent {
    class Symtable* symtable;
    Type type;
};

#endif