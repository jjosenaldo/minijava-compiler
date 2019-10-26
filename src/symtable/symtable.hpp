#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include <deque>
#include <string>
#include <unordered_map>
#include <utility>
#include "error.hpp"
#include "type.hpp"

using std::deque;
using std::pair;
using std::string;
using std::unordered_map;

class Program;
class ClassDeclaration;
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

TableContent tableContentNoContent();

class Symtable{
    protected:
        string className;
        Symtable* parent;
        int localId;
        vector<pair<string, TableContent>>* table;

    public:
        Symtable(string className);

        Symtable(string className, Symtable* parent);

        Symtable* getParent();

        string getClassName();

        void setParent(Symtable* table);

        void insert(string id, TableContent content);

        void insert(Symtable* content);

        void setLocalId(int id);

        TableContent lookup(string id);

        TableContent get(string id);

        virtual void print();
};

class ClassSymtablePool;

class ClassSymtable : public Symtable{
    private:
        unordered_map<string, Symtable*>* methodTables;
    public:
        ClassSymtable(string className);
        void insertMethodTable(string methodName, Symtable* table);
        unordered_map<string, Symtable*>* getMethodTables();
        void print();
        bool processMethodBodies(ClassDeclaration* classDecl, ClassSymtablePool* pool, Program* program);
};

class ClassSymtablePool{
    private:
        unordered_map<string, ClassSymtable*>* pool;
        bool loopBlockFlag;

    public:
        ClassSymtablePool();
        void insert(string className, ClassSymtable* table);

        ClassSymtable* get(string className);

        unordered_map<string, ClassSymtable*>* getPool();

        void setIsLoopBlock(bool is);

        bool isLoopBlock();

        void print();
};

void printTableContent(TableContent content);


bool addClassNamesToPool(Program* program, ClassSymtablePool* pool);

bool processesClassInheritanceHierarchy(ClassSymtablePool* pool);

ClassSymtablePool* buildClassSymtablePool(Program* program);

bool isSubclassOf(string descendant, string ancestor);

#endif