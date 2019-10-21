#include <iostream>
#include "symtable.hpp"
#include "type.hpp"

using std::cout;
using std::endl;

TableContent tableContentFromType(Type* type){
    TableContent tc;
    tc.tag = TCTYPE;
    tc.type = type;
    return tc;
}

Symtable::Symtable() : Symtable(nullptr){}

Symtable::Symtable(Symtable* parent){
    this->parent = parent;
    this->table = new vector<pair<string, TableContent>>;
}

Symtable* Symtable::getParent(){
    return this->parent;
}

void Symtable::setParent(Symtable* table){
    this->parent = table;
}

void Symtable::insert(string id, TableContent content){
    this->table->emplace_back(id, content);
}

void Symtable::insert(Symtable* table){
    table->setLocalId(this->table->size());
    
    TableContent tc;
    tc.tag = TCSYMTABLE;
    tc.symtable = table;
    this->table->emplace_back("", tc);
}

void Symtable::setLocalId(int id){
    this->localId = id;
}

TableContent Symtable::get(string id){
    for(auto p : *table)
        if(p.first == id)
            return p.second;

    TableContent tcReturn;
    tcReturn.tag = TCNOCONTENT;
    return tcReturn;
}

void Symtable::print(){
    cout << "{" << endl;
    for(auto& entry : *this->table){
        cout << entry.first << " : ";
        printTableContent(entry.second);
        cout << endl;
    }
    cout << "}";
}

ClassSymtablePool::ClassSymtablePool(){
    pool = new unordered_map<string, ClassSymtable*>;
}

void ClassSymtablePool::insert(string className, ClassSymtable* table){
    this->pool->insert({{className,table}});
}

ClassSymtable* ClassSymtablePool::get(string className){
    auto it = this->pool->find(className);

    if(it == this->pool->end())
        return nullptr;
    
    else
        return it->second;
}

void ClassSymtable::print(){
    cout << "{" << endl;
    for(auto& entry : *this->table){
        cout << entry.first << " : ";
        printTableContent(entry.second);
        cout << endl;
    }
    
    for(auto it : *methodTables){
        cout << it.first << " : ";
        it.second->print();
        cout << endl;
    }

    cout << "}";
}

unordered_map<string, ClassSymtable*>* ClassSymtablePool::getPool(){
    return pool;
}

void ClassSymtablePool::print(){
    for(auto it : *pool){
        cout << it.first << " -> ";
        it.second->print();
        cout << endl;
    }
}

ClassSymtable::ClassSymtable(){
    this->methodTables = new unordered_map<string, Symtable*>;
}

void ClassSymtable::insertMethodTable(string methodName, Symtable* table){
    methodTables->insert({{methodName,table}});
}

unordered_map<string, Symtable*>* ClassSymtable::getMethodTables(){
    return methodTables;
}

void printTableContent(TableContent content){
    if(content.tag == TCTYPE){
        printType(content.type);
    } else if(content.tag == TCSYMTABLE){
        content.symtable->print();
    }
}