#include "activation-record.hpp"

// Record::Record(Record *parent, void* b_label, void* e_label, void* methodCallPosLabel, Value* returnVal) :
// 	Record(parent,parent, b_label, e_label, methodCallPosLabel, nullptr, returnVal) {}

// Record::Record(Record *parent, void* b_label, void* e_label, void* methodCallPosLabel, ClassValue* currentObject, Value* returnVal) :
// 	Record(parent,parent, b_label, e_label, methodCallPosLabel, currentObject, returnVal) {}

// Record::Record(Record *staticParent, Record* dynamicParent, void* b_label, void* e_label, void* methodCallPosLabel, Value* returnVal) :
// 	Record(staticParent, dynamicParent, b_label, e_label, methodCallPosLabel, nullptr, returnVal){}

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
		// std::cout << "procurando: " << id << " no registro\n";
		// currentRecord->print();
		v = currentRecord->getVarVal(id);
		currentRecord = currentRecord->getStaticParent();
		// std::cout << "proximo regisitro: " << std::endl;
		// if(currentRecord == nullptr) std::cout << "null\n";
		// else currentRecord->print();
	} while(v == nullptr && currentRecord != nullptr);

	// std::cout << "cabou/desisto\n";

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
/*
Value** Record::lookupStaticReference(string id) {
	Value **v = new Value*;
	Record* currentRecord = this;

	do{
		*v = currentRecord->getVarVal(id);
		currentRecord = currentRecord->getStaticParent();
	} while(v == nullptr && currentRecord != nullptr);

	return v;
}
*/


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

// RecordStack
RecordStack::RecordStack() {}

RecordStack::~RecordStack() {}

void RecordStack::createRecord(void* b_label, void* e_label, void* returnLabel, ClassValue* currentObject, Value* returnVal) {
	// std::cout << "quero inserir um registro. pilha atual:\n";
	// this->print();
	Record* dynamicParent = records.empty() ? nullptr : records.back();
	Record* staticParent;

	if(dynamicParent == nullptr) 
		staticParent = nullptr;
	
	else 
		staticParent = returnLabel != nullptr ? nullptr : dynamicParent ;
	records.push_back(new Record(staticParent, dynamicParent , b_label, e_label, returnLabel,currentObject, returnVal));
	// std::cout << "após inserir:\n";
	// this->print();
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

