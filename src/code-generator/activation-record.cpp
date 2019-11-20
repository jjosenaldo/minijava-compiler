#include "activation-record.hpp"

// Record
Record::Record(Record *parent, void* b_label, void* e_label) {
	this->b_label = b_label;
	this->e_label = e_label;
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

void* Record::gete_label(){
	return this->e_label;
}

void* Record::getb_label(){
	return this->b_label;
}

// RecordStack
RecordStack::RecordStack() {}

RecordStack::~RecordStack() {}

// TODO: Transformar em escopo estático
void RecordStack::createRecord(void* b_label, void* e_label) {
	Record* parent = records.empty() ? nullptr : records.top();
	records.push(new Record(parent, b_label, e_label));
}

Record* RecordStack::top() {
	return records.top();
}

void RecordStack::pop() {
	records.top()->print(); // TODO: Remover after
	records.pop();
}

void* RecordStack::searchContinue() {
	while(records.top()->getb_label() != nullptr){
		records.pop();
	}
	return records.top()->getb_label();
}