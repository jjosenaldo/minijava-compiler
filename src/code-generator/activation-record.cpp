#include "activation-record.hpp"

Record::Record(Record *staticParent, Record* dynamicParent, void* b_label, void* e_label, void* methodCallPosLabel, ClassValue* currentObject, Value* returnVal) {
	this->b_label = b_label;
	this->e_label = e_label;
	this->methodCallPosLabel = methodCallPosLabel;
	this->dynamicParent = dynamicParent;
	this->staticParent = staticParent;
	this->currentObject = currentObject;
	this->returnVal = returnVal;
}

Record::~Record() {}

ClassValue* Record::getCurrentObject(){
	return currentObject;
}

bool Record::isMethodBlock(){
	return !(methodCallPosLabel == nullptr);
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

	return v->copy();
}

Value* Record::lookupDynamic(string id) {
	Value *v = nullptr;
	Record* currentRecord = this;

	do{
		v = currentRecord->getVarVal(id);
		currentRecord = currentRecord->getDynamicParent();
	} while(v == nullptr && currentRecord != nullptr);

	return v->copy();
}

Record* Record::getDynamicParent(){
	return dynamicParent;
}

Record* Record::getStaticParent(){
	return staticParent;
}

Value* Record::getReturnValue() {
	return returnVal;
}

void Record::setReturnValue(Value* value) {
	this->returnVal = value;
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

	currentRecord->table[id] = newValue;
	delete v;
}

void* Record::gete_label(){
	return this->e_label;
}

void* Record::getb_label(){
	return this->b_label;
}

void* Record::getMethodCallPosLabel() {
	return this->methodCallPosLabel;
}

void Record::print() {
	cout << "tenho label? "<< (methodCallPosLabel != nullptr) << "\n";
	cout << "tenho pai estatico? " << (staticParent != nullptr) << "\n";
	cout << "{\n";
	for(auto &e : table)
		cout << "\t" << e.first << ", " << (e.second == nullptr ? "nullptr" : e.second->toString()) << endl;
	cout << "}\n";
}

// RecordStack
RecordStack::RecordStack() {}

RecordStack::~RecordStack() {}

void RecordStack::createRecord(void* b_label, void* e_label, void* returnLabel, ClassValue* currentObject, Value* returnVal) {
	Record* dynamicParent = records.empty() ? nullptr : records.back();
	Record* staticParent;

	if(dynamicParent == nullptr) 
		staticParent = nullptr;
	
	else 
		staticParent = returnLabel != nullptr ? nullptr : dynamicParent ;
	records.push_back(new Record(staticParent, dynamicParent , b_label, e_label, returnLabel,currentObject, returnVal));
}

Record* RecordStack::top() {
	return records.back();
}

void RecordStack::pop() {
	records.pop_back();
}

void* RecordStack::searchContinue() {
	while(records.back()->getb_label() != nullptr){
		records.pop_back();
	}
	return records.back()->getb_label();
}


void* RecordStack::searchBreak() {
	while(records.back()->gete_label() != nullptr){
		records.pop_back();
	}
	return records.back()->gete_label();
}

void* RecordStack::searchMethodCallLabel() {
	while(records.back()->getMethodCallPosLabel() == nullptr){
		records.pop_back();
	}
	
	return records.back()->getMethodCallPosLabel();
}

void RecordStack::print(){
	for(auto r : records) r->print();
}