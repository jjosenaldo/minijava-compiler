#ifndef SYMTABLEPOOL_HPP
#define SYMTABLEPOOL_HPP

#include <string>
#include <unordered_map>
#include "symtable.hpp"

using std::unordered_map;
using std::string;

class SymtablePool{
    private:
        unordered_map<string, Symtable*> pool;
    
    public:
        bool insert(string className, Symtable* table);

        Symtable* get(string className);

        void print();
};


#endif