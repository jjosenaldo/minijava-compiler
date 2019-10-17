#include <iostream>
#include "symtable.hpp"
#include "../table-content/table-content.hpp"
using std::cout;
using std::endl;

Symtable::Symtable(){
    this->parent = nullptr;
}

Symtable::Symtable(Symtable* parent){
    this->parent = parent;
}

Symtable* Symtable::getParent(){
    return this->parent;
}

bool Symtable::insert(string id, TableContent content){
    if(this->table.find(id) != this->table.end())
        return false;
    
    else{
        this->table[id] = content;
        return true;
    }
}

TableContent Symtable::get(string id){
    return this->table[id];
}

void Symtable::print(){
    cout << "{" << endl;
    for(auto& entry : this->table){
        cout << entry.first << " : ";
        printTableContent(entry.second);
        cout << endl;
    }
    cout << "}";
}