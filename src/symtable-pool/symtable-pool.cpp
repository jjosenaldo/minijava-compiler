#include <iostream>
#include "symtable-pool.hpp"

using std::cout;
using std::endl;

bool SymtablePool::insert(string className, Symtable* table){
    if(this->pool.find(className) != this->pool.end())
        return false;
    
    else{
        this->pool[className] = table;
        return true;
    }
}

Symtable* SymtablePool::get(string className){
    auto it = this->pool.find(className);

    if(it == this->pool.end())
        return nullptr;
    
    else
        return it->second;
}

void SymtablePool::print(){
    for(auto it : this->pool){
        cout << it.first << " : ";
        it.second->print();
        cout << endl;
    }
}