#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include <string>
#include <unordered_map>
#include "table-content.hpp"

using std::string;
using std::unordered_map;

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

#endif