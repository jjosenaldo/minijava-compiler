#ifndef ACTIVATION_RECORD_HPP
#define ACTIVATION_RECORD_HPP

#include <unordered_map>
#include <string>
#include <stack>
#include <iostream> // TODO: Remove after
#include "value.hpp"

using namespace std;

//  ================= Class Diagram =================
//
//    +--------+
//    |        |
//    v        |
// +--------------+       +-------------------+
// |    Record    |       |    RecordClass    |
// |______________|<*-----|___________________|
// |              |       |                   |
// +--------------+       +-------------------+
//        |
//        |
//        v*
//  +-----------+
//  |   Value   |
//  |___________|
//  |           |
//  +-----------+
//  =================================================

class Record
{
private:
	unordered_map<string,Value*> table;

	Record* dynamicParent;

	Value* returnVal;

	void* b_label;

	void* e_label;

public:
	Record(Record* parent, void* b_label, void* e_label);
	~Record();

	Value* getVarVal(string id);
	Value* lookupVarVal(string id);
	Value* getReturn();
	void insertVar(string id, Value *v);
	void insertVar(string id, int v);
	void updateVar(string id, Value* v); // TODO: Free old value
	void* gete_label();
	void* getb_label();


	Record* getDynamicParent();

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
	void createRecord(void* b_label = nullptr, void* e_label = nullptr);
	Record* top();
	void pop();
	void* searchContinue();
	void* searchBreak();

};

#endif