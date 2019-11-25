#ifndef ACTIVATION_RECORD_HPP
#define ACTIVATION_RECORD_HPP

#include <iostream> 
#include <string>
#include <unordered_map>
#include <vector>

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
	ClassValue* currentObject;

	Value* returnVal;

	void* b_label;

	void* e_label;
	void* methodCallPosLabel;
	Value* getVarVal(string id);

public:
	Record(Record* staticParent, Record* dynamicParent, void* b_label, void* e_label, void* methodCallPosLabel, ClassValue* currentObject, Value* returnVal);
	~Record();

	Value* lookupStatic(string id);
	Value* lookupDynamic(string id);
	Value* getReturnValue();
	void setReturnValue(Value* value);
	ClassValue* getCurrentObject();
	void insertVar(string id, Value *v);
	void insertVar(string id, int v);
	void updateStatic(string id, Value* v);
	void* gete_label();
	void* getb_label();

	/**
	 * @brief Checks if the block contained in the record is a regular block or is the statement
	 * list of a method
	 *
	 * @return true
	 * @return false
	 */
	bool isMethodBlock();

	Record* getStaticParent();
	void* getMethodCallPosLabel();

	Record* getDynamicParent();
	void print();
};

class RecordClass
{
public:
	RecordClass();
	~RecordClass();

};

class RecordStack
{
	vector<Record*> records;

public:
	RecordStack();
	~RecordStack();
	void print();
	void createRecord(void* b_label = nullptr, void* e_label = nullptr, void* methodCallPosLabel = nullptr, ClassValue* currentObject = nullptr, Value* returnVal = nullptr);
	Record* top();
	void pop();
	void* searchContinue();
	void* searchBreak();
	void* searchMethodCallLabel();

};

#endif