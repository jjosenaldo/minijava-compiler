#include "value.hpp"
#include <iostream>
using std::to_string;

IntValue::IntValue(int v){
    value = v;
    className = "IntValue";
}

IntValue::IntValue() : IntValue(0){}

string IntValue::toString(){
    return to_string(value);
}

int IntValue::getInt() const {
    return this->value;
}

BoolValue::BoolValue() : BoolValue(false){}

BoolValue::BoolValue(bool v){
    value = v;
    className = "BoolValue";
}

string BoolValue::toString(){
    return value ? "true" :  "false";
}

bool BoolValue::getBool() const {
    return this->value;
}

StringValue::StringValue() : StringValue(""){}

StringValue::StringValue(string v){
    this->value = v;
    className = "StringValue";
}

string StringValue::getString() const{
    return value;
}

string StringValue::toString(){
    return getString();
}

ArrayValue::ArrayValue(Value** v, int n){
    this->value = v;
    this->n = n;
    this->className = "ArrayValue";
}

Value** ArrayValue::getArray() const{
    return value;
}

void ArrayValue::setAt(int* dims, int n, Value* newVal){
    setAt(dims, 0, n, newVal, this);    
}

void ArrayValue::setAt(int* dims, int i, int n, Value* newVal, ArrayValue* currentArray){
    if(i == n-1)
        currentArray->value[dims[i]] = newVal;
    else 
        setAt(dims, i+1, n, newVal, dynamic_cast<ArrayValue*>(this->value[dims[i]]));
}

string ArrayValue::toString(){
    string res = "{";

    for(int i = 0; i < n; ++i)
        res += value[i]->toString();

    return res+"}";
}

ArrayValue::ArrayValue(int* dims, int n, Value* ctor ()) : ArrayValue(dims,1,n,ctor){}

ArrayValue::ArrayValue(int* dims, int i, int n, Value* ctor ()){
    // TODO: put this constructor in a separate recursive method so that this assignment
    // doesn't get executed every single time
    this->className = "ArrayValue";

    this->value = new Value*[dims[i-1]];
    if(i == n)
        for(int j = 0; j < dims[i-1]; ++j)
            this->value[j] = ctor();
    else
        for(int j = 0; j < dims[i-1]; ++j) 
            this->value[j] = new ArrayValue(dims, i+1,n,ctor);
        
    
}

ClassValue::ClassValue(string className){
    this->fields = new unordered_map<string, Value*>;
    this->className = className;
}

void ClassValue::set(string field, Value* value){
    (*this->fields)[field] = value;
}

Value* ClassValue::get(string field){
    return this->fields->at(field);
}

// array operators
Value* Value::operator[](const int i){
    NullValue* nv = dynamic_cast<NullValue*>(this);
    if(nv != nullptr){
        std::cerr << "ERROR: trying to access a position of a null array!\n";
        exit(0);
    }

    ArrayValue* arr = dynamic_cast<ArrayValue*>(this);
    return (arr->value)[i];
}

// int
Value* operator-(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new IntValue(i1->value - i2->value);
    throw "Invalid type!\n";
}

Value* operator-(const Value& v1) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);

    if(i1 != nullptr)
        return new IntValue(-i1->value);
    throw "Invalid type!\n";
}
Value* operator*(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new IntValue(i1->value * i2->value);
    throw "Invalid type!\n";
}
Value* operator/(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new IntValue(i1->value / i2->value);
    throw "Invalid type!\n";
}
Value* operator%(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new IntValue(i1->value % i2->value);
    throw "Invalid type!\n";
}

// String and int
Value* operator+(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new IntValue(i1->value + i2->value);

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new StringValue(s1->value + s2->value);

    throw "Invalid type!\n";
}

Value* operator<(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new BoolValue(i1->value < i2->value);

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new BoolValue(s1->value < s2->value);

    throw "Invalid type!\n";
}

Value* operator<=(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new BoolValue(i1->value <= i2->value);

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new BoolValue(s1->value <= s2->value);

    throw "Invalid type!\n";
}

Value* operator>(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new BoolValue(i1->value > i2->value);

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new BoolValue(s1->value > s2->value);

    throw "Invalid type!\n";
}

Value* operator>=(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new BoolValue(i1->value >= i2->value);

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new BoolValue(s1->value >= s2->value);

    throw "Invalid type!\n";
}

// bool
Value* operator!(const Value& v1) {
    const BoolValue* b1 = dynamic_cast<const BoolValue*>(&v1);
    if(b1 != nullptr)
        return new BoolValue(!b1->value);
    throw "Invalid type!\n";
}

Value* operator||(const BoolValue& v1, const BoolValue& v2) {
    const BoolValue* b1 = dynamic_cast<const BoolValue*>(&v1);
    const BoolValue* b2 = dynamic_cast<const BoolValue*>(&v2);
    if(b1 != nullptr and b2 != nullptr)
        return new BoolValue(b1->value || b2->value);
    throw "Invalid type!\n";
}

Value* operator&&(const BoolValue& v1, const BoolValue& v2) {
    const BoolValue* b1 = dynamic_cast<const BoolValue*>(&v1);
    const BoolValue* b2 = dynamic_cast<const BoolValue*>(&v2);
    if(b1 != nullptr and b2 != nullptr)
        return new BoolValue(b1->value && b2->value);
    throw "Invalid type!\n";
}

// all
Value* operator==(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);
    if(i1 != nullptr and i2 != nullptr)
        return new BoolValue(i1->value == i2->value);

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);
    if(s1 != nullptr and s2 != nullptr)
        return new BoolValue(s1->value == s2->value);

    const BoolValue* b1 = dynamic_cast<const BoolValue*>(&v1);
    const BoolValue* b2 = dynamic_cast<const BoolValue*>(&v2);
    if(b1 != nullptr and b2 != nullptr)
        return new BoolValue(b1->value == b2->value);

    const ClassValue* c1 = dynamic_cast<const ClassValue*>(&v1);
    const ClassValue* c2 = dynamic_cast<const ClassValue*>(&v2);
    if(c1 != nullptr and c2 != nullptr)
        return new BoolValue(c1 == c2);

    const ArrayValue* a1 = dynamic_cast<const ArrayValue*>(&v1);
    const ArrayValue* a2 = dynamic_cast<const ArrayValue*>(&v2);
    if(a1 != nullptr and a2 != nullptr)
        return new BoolValue(a1->value == a2->value);
    
    const NullValue* n1 = dynamic_cast<const NullValue*>(&v1);
    const NullValue* n2 = dynamic_cast<const NullValue*>(&v2);

    if(n1 != nullptr && n2 != nullptr)
        return new BoolValue(true); 
    
    if((n1 != nullptr && n2 == nullptr) || (n2 != nullptr && n1 == nullptr))
        return new BoolValue(false); 

    throw "Invalid type!\n";
}

Value* operator!=(const Value& v1, const Value& v2) {
    return !*(v1 == v2);
}