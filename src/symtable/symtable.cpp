#include <iostream>
#include "global.hpp"
#include "symtable.hpp"
#include "type.hpp"
#include "ast.hpp"

using std::cout;
using std::endl;

TableContent tableContentFromType(Type* type){
    TableContent tc;
    tc.tag = TCTYPE;
    tc.type = type;
    return tc;
}

TableContent tableContentNoContent(){
    TableContent tc;
    tc.tag = TCNOCONTENT;
    return tc;
}

Symtable::Symtable(string className) : Symtable(className, nullptr){}

Symtable::Symtable(string className, Symtable* parent){
    this->className = className;
    this->parent = parent;
    this->table = new vector<pair<string, TableContent>>;
}

string Symtable::getClassName(){
    return this->className;
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


TableContent Symtable::lookup(string name){
    Symtable* table = this;

    while(table->getParent() != nullptr){
        TableContent tc = table->get(name);
        if(tc.tag != TCNOCONTENT)
            return tc;
        table = table->getParent();
    }

    return tableContentNoContent();
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
    this->loopBlockFlag = false;
}

void ClassSymtablePool::setIsLoopBlock(bool is){
    this->loopBlockFlag = is;
}

bool ClassSymtablePool::isLoopBlock() {
    return this->loopBlockFlag;
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

ClassSymtable::ClassSymtable(string className) : Symtable(className) {
    this->methodTables = new unordered_map<string, Symtable*>;
}

void ClassSymtable::insertMethodTable(string methodName, Symtable* table){
    methodTables->insert({{methodName,table}});
}

bool ClassSymtable::processMethodBodies(ClassDeclaration* classDecl, ClassSymtablePool* pool, Program* program){
    for(auto methodTablePair : *methodTables){
        string methodName = methodTablePair.first;
        Symtable* methodTable = methodTablePair.second;
        auto method = classDecl->getMethod(methodName);
        auto blockStmt = method->getStatement();

        if(blockStmt != nullptr){
            auto stmts = blockStmt->getStatements();

            for(auto stmt : *stmts)
                if(!stmt->process(methodTable, pool, program))
                    return false;
        }
    }

    return true;
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

bool processesClassInheritanceHierarchy(ClassSymtablePool* pool){
    unordered_map<string, string> unprocClasses;
    unordered_map<string, string> procClasses;

    for(auto p : g_classParentMap)
        unprocClasses.emplace(p.first, p.second);

    auto itCurrent = unprocClasses.begin();
    string firstInChain = itCurrent->second;
    string parent;

    while(true){
        if(itCurrent->first == itCurrent->second){
            circularInheritanceError(itCurrent->first);
            return false;
        }

        parent = itCurrent->second;
        if(parent == ""){
            procClasses.emplace(itCurrent->first, itCurrent->second);
            unprocClasses.erase(itCurrent);

            if(unprocClasses.empty())
                return true;

            itCurrent = unprocClasses.begin();
            firstInChain = itCurrent->second;
            continue;
        }

        auto itParentUnproc = unprocClasses.find(parent);
        if(itParentUnproc != unprocClasses.end()){
            procClasses.emplace(itCurrent->first, itCurrent->second);
            unprocClasses.erase(itCurrent);

            itCurrent = itParentUnproc;
            continue;
        }

        auto itParentProc = procClasses.find(parent);
        if(itParentProc != procClasses.end()){
            if(itParentProc->second == firstInChain){
                circularInheritanceError(firstInChain);
                return false;
            }

            procClasses.emplace(itCurrent->first, itCurrent->second);
            unprocClasses.erase(itCurrent);

            if(unprocClasses.empty())
                return true;

            itCurrent = unprocClasses.begin();
            firstInChain = itCurrent->second;
            continue;
        }

        classNotDefinedError(parent);
        return false;
    }

    return true;
}
bool addClassNamesToPool(Program* program, ClassSymtablePool* pool){
    for(auto classDecl : *program->getDecls()){
        if(classDecl->getParent() == g_mainClassName){
            inheritanceFromMainClassError(classDecl->getName());
            return false;
        }

        string className = classDecl->getName();

        if(pool->get(className) != nullptr) {
            multipleClassError(className);
            return false;
        }

        ClassSymtable* root = new ClassSymtable(className);
        pool->insert(className, root);
        g_classParentMap.emplace(className, classDecl->getParent());
    }

    return true;
}

ClassSymtablePool* buildClassSymtablePool(Program* program){
    ClassSymtablePool* pool = new ClassSymtablePool;

    if(!addClassNamesToPool(program, pool)){
        delete pool;
        return nullptr;
    }

    if(!processesClassInheritanceHierarchy(pool)) {
        delete pool;
        return nullptr;
    }

    // Processes each class
    for(auto classDecl : *program->getDecls()){
        string className = classDecl->getName();
        ClassSymtable* root = pool->get(className);

        // Processes the fields
        auto fields = classDecl->getFields();
        if(fields != nullptr)
            for(auto field : *fields)
                if(!field->process(className, root)){
                    delete pool;
                    return nullptr;
                }

        // Processes the method headers
        auto methods = classDecl->getMethods();
        if(methods != nullptr){
            for(auto method : *methods)
                if(!method->processHeader(className, root, pool)){
                    delete pool;
                    return nullptr;
                }
        }
    }

    // Processes each method body
    unordered_map<string, ClassSymtable*>* tablePool = pool->getPool();
    for(auto tablePoolEntry : *tablePool){
        string className = tablePoolEntry.first;
        ClassSymtable* classSymtable = tablePoolEntry.second;
        if(!classSymtable->processMethodBodies(program->getClassDecl(className), pool, program))  {
            delete pool;
            return nullptr;
        }
    }

    return pool;
}

bool isSubclassOf(string descendant, string ancestor){
    if(descendant == ancestor)
        return true;

    string currentParent = g_classParentMap[descendant];

    while(currentParent != ""){
        if(currentParent == ancestor)
            return true;
        currentParent = g_classParentMap[currentParent];
    }

    return false;
}