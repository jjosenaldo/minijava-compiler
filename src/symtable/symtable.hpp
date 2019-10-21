#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include <string>
#include <unordered_map>
#include <utility>
#include "type.hpp"

using std::pair;
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

TableContent tableContentFromType(Type* type);

class Symtable{
    protected:
        Symtable* parent;
        int localId;
        vector<pair<string, TableContent>>* table;

    public:
        Symtable();

        Symtable(Symtable* parent);

        Symtable* getParent();

        void setParent(Symtable* table);

        void insert(string id, TableContent content);

        void insert(Symtable* content);

        void setLocalId(int id);

        TableContent get(string id);

        virtual void print();
};

class ClassSymtable : public Symtable{
    private:
        unordered_map<string, Symtable*>* methodTables;
    public:
        ClassSymtable();
        void insertMethodTable(string methodName, Symtable* table);
        unordered_map<string, Symtable*>* getMethodTables();
        void print();
};

class ClassSymtablePool{
    private:
        unordered_map<string, ClassSymtable*>* pool;
    
    public:
        ClassSymtablePool();
        void insert(string className, ClassSymtable* table);

        ClassSymtable* get(string className);

        unordered_map<string, ClassSymtable*>* getPool();

        void print();
};

void printTableContent(TableContent content);

#endif