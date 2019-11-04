#include "activation-record.hpp"

// Record
Record::Record(Record *parent) {
	staticParent = parent;
}
	
Record::~Record() {}

Value* Record::getVarVal(string id) { 
	Value *v;
	try {
		v = table.at(id);
	}
	catch(exception &e) {
		return nullptr;
	}
	return v;
}

Value* Record::getReturn() {
	return returnVal;
}
	
void Record::insertVar(string id, Value *v) {
	table[id] = v;
}

void Record::insertVar(string id, int v) {
	Value* v1 = new IntValue(v);
	table[id] = v1;
}

void Record::updateVar(string id, Value* v) {
	table[id] = v;
}


// RecordStack
RecordStack::RecordStack() {}

RecordStack::~RecordStack() {}

void RecordStack::createRecord() {
	Record* parent = records.empty() ? nullptr : records.top();
	records.push(new Record(parent));
}

Record* RecordStack::top() {
	return records.top();
}

void RecordStack::pop() {
	records.top()->print(); // TODO: Remover after
	records.pop();
}