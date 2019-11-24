#include "activation-record.hpp"

Record::Record(Record *parent, void* b_label, void* e_label, void* returnLabel) :
	Record(parent,parent, b_label, e_label, returnLabel, nullptr) {}

Record::Record(Record *parent, void* b_label, void* e_label, void* returnLabel, ClassValue* currentObject) :
	Record(parent,parent, b_label, e_label, returnLabel, currentObject) {}

Record::Record(Record *staticParent, Record* dynamicParent, void* b_label, void* e_label, void* returnLabel) : 
	Record(staticParent, dynamicParent, b_label, e_label, returnLabel, nullptr){}

Record::Record(Record *staticParent, Record* dynamicParent, void* b_label, void* e_label, void* returnLabel, ClassValue* currentObject){
	this->b_label = b_label;
	this->e_label = e_label;
	this->returnLabel = returnLabel;
	this->dynamicParent = dynamicParent;
	this->staticParent = staticParent;
	this->currentObject = currentObject;
}

Record::~Record() {}

ClassValue* Record::getCurrentObject(){
	return currentObject;
}

bool Record::isMethodBlock(){
	return !(returnLabel == nullptr);
}

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

Value* Record::lookupStatic(string id) {
	Value *v = nullptr;
	Record* currentRecord = this;

	do{
		v = currentRecord->getVarVal(id);
		currentRecord = currentRecord->getStaticParent();
	} while(v == nullptr && currentRecord != nullptr);

	return v;
}

Value* Record::lookupDynamic(string id) {
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

Record* Record::getStaticParent(){
	return staticParent;
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

void Record::updateStatic(string id, Value* newValue) {
	Record* currentRecord = this;
	Value *v = currentRecord->getVarVal(id);

	while(v == nullptr && currentRecord != nullptr){
		currentRecord = currentRecord->getStaticParent();
		v = currentRecord->getVarVal(id);
	}

	delete currentRecord->table[id];
	currentRecord->table[id] = newValue;
}

void* Record::gete_label(){
	return this->e_label;
}

void* Record::getb_label(){
	return this->b_label;
}

void* Record::getReturnLabel() {
	return this->returnLabel;
}

// RecordStack
RecordStack::RecordStack() {}

RecordStack::~RecordStack() {}

// TODO: Transformar em escopo estático
void RecordStack::createRecord(void* b_label, void* e_label, void* returnLabel, ClassValue* currentObject) {
	Record* dynamicParent = records.empty() ? nullptr : records.top();
	Record* staticParent = returnLabel == nullptr ? dynamicParent : nullptr ;
	records.push(new Record(staticParent, dynamicParent , b_label, e_label, returnLabel,currentObject));
}

Record* RecordStack::top() {
	return records.top();
}

void RecordStack::pop() {
	records.pop();
}

void* RecordStack::searchContinue() {
	while(records.top()->getb_label() != nullptr){
		records.pop();
	}
	return records.top()->getb_label();
}