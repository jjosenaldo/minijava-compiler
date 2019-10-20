#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include <string>
#include <unordered_map>
#include "type.hpp"

using std::string;
using std::unordered_map;

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

class Symtable{
    private:
        Symtable* parent;
        unordered_map<string, TableContent> table;

    public:
        Symtable();

        Symtable(Symtable* parent);

        Symtable* getParent();

        bool insert(string id, TableContent content);

        TableContent get(string id);

        void print();
};

class SymtablePool{
    private:
        unordered_map<string, Symtable*> pool;
    
    public:
        bool insert(string className, Symtable* table);

        Symtable* get(string className);

        void print();
};

void printTableContent(TableContent content);

#endif