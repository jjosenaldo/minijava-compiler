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
	Record* staticParent;
	Value* returnVal;
	ClassValue* currentObject;

	void* b_label;

	void* e_label;
	void* returnLabel;

public:
	Record(Record* staticParent, Record* dynamicParent, void* b_label, void* e_label, void* returnLabel, ClassValue* currentObject);
	Record(Record* staticParent, Record* dynamicParent, void* b_label, void* e_label, void* returnLabel);

	// Sets both parents to be the same record
	Record(Record* parent, void* b_label, void* e_label, void* returnLabel, ClassValue* currentObject);
	Record(Record* parent, void* b_label, void* e_label, void* returnLabel);
	~Record();

	Value* getVarVal(string id);
	Value* lookupStatic(string id);
	Value* lookupDynamic(string id);
	Value* getReturn();
	ClassValue* getCurrentObject();
	void insertVar(string id, Value *v);
	void insertVar(string id, int v);
	void updateStatic(string id, Value* v);
	void* gete_label();
	void* getb_label();
	void* getReturnLabel();
	
	/**
	 * @brief Checks if the block contained in the record is a regular block or is the statement
	 * list of a method
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isMethodBlock();

	Record* getStaticParent();
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
	void createRecord(void* b_label = nullptr, void* e_label = nullptr, void* returnLabel = nullptr, ClassValue* currentObject = nullptr);
	Record* top();
	void pop();
	void* searchContinue();
	void* searchBreak();

};

#endif