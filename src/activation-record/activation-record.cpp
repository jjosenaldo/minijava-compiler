#include "activation-record.hpp"

// Record
Record::Record(Record *parent) {
	dynamicParent = parent;
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

Value* Record::lookupVarVal(string id) { 
	Value *v = nullptr;
	Record* currentRecord = this;

	do{
		v = currentRecord->getVarVal(id);
		currentRecord = currentRecord->getDynamicParent();
	} while(v == nullptr && currentRecord != nullptr);
	
	return v;
}

Record* Record::getDynamicParent(){
	return dynamicParent;
}

Value* Record::getReturn() {
	return returnVal;
}
	
void Record::insertVar(string id, Value *v) {
	table[id] = v;
}

void Record::insertVar(string id, int v) {
	insertVar(id, new IntValue(v));
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