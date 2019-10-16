#ifndef TABLECONTENT_HPP
#define TABLECONTENT_HPP

#include "../symtable/symtable.hpp"

union TableContent {
    class Symtable* symtable;
};

#endif