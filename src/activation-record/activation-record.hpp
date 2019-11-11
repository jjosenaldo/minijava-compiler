#ifndef ACTIVATION_RECORD_HPP
#define ACTIVATION_RECORD_HPP
#include <unordered_map>
#include <string>
#include <stack>
#include <iostream> // TODO: Remove after

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

class Value
{
public:
	Value() {}
	~Value() {}
	virtual int getValue(){return 0;}
	virtual string toString() = 0;
};

class IntValue : public Value {
private:
	int value;
public:
	IntValue(int v) { value = v; }
	int getValue(){return 0;}
	string toString() { return to_string(value); }
};

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
	Value* getReturn();
	void insertVar(string id, Value *v);
	void insertVar(string id, int v);
	void updateVar(string id, Value* v); // TODO: Free old value 
	void updateVar(string id, int v) { table[id] = new IntValue(v);}

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