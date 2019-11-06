#ifndef ACTIVATION_RECORD_HPP
#define ACTIVATION_RECORD_HPP

#include <unordered_map>
#include <string>
#include <stack>
#include <iostream> // TODO: Remove after

#include "value.hpp"

using namespace std;

class Record
{
private:
	unordered_map<string,Value*> table;

	Record* staticParent;

	Value* returnVal;

public:
	Record(Record* parent);
	~Record();

	Value* getVarVal(string id);
	Value* lookupVarVal(string id);
	Value* getReturn();
	void insertVar(string id, Value *v);
	void insertVar(string id, int v);
	void updateVar(string id, Value* v); // TODO: Free old value 
	void updateVar(string id, int v) { table[id] = new IntValue(v);}

	Record* getStaticParent();

	// TODO: Remove after
	void print() {
		cout << "{\n";
		for(auto &e : table)
			cout << "\t" << e.first << ", " << (e.second == nullptr ? "nullptr" : e.second->toString()) << endl; 
		cout << "}\n";
	}
};

class RecordClass
{
public:
	RecordClass();
	~RecordClass();
	
};

class RecordStack
{
	stack<Record*> records;

public:
	RecordStack();
	~RecordStack();
	void createRecord();
	Record* top();
	void pop();
};

#endif