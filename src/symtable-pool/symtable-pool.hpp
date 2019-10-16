#ifndef SYMTABLEPOOL_HPP
#define SYMTABLEPOOL_HPP

#include <string>
#include <unordered_map>
#include "../symtable/symtable.hpp"

using std::unordered_map;
using std::string;

class SymtablePool{
    private:
        unordered_map<string, Symtable*> pool;
    
    public:
        SymtablePool();

        void addTable(string className, Symtable* table);
};


#endif