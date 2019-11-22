#include "value.hpp"
#include <iostream>
using std::to_string;

IntValue::IntValue(int v){
    value = v;
}

IntValue::IntValue(){
    value = 0;
}

string IntValue::toString(){
    return to_string(value);
}

int IntValue::getInt() const {
    return this->value;
}

string IntValue::getClassName(){
    return "IntValue";
}

BoolValue::BoolValue() : BoolValue(false){}

BoolValue::BoolValue(bool v){
    value = v;
}

string BoolValue::toString(){
    return value ? "true" :  "false";
}

bool BoolValue::getBool() const {
    return this->value;
}

string BoolValue::getClassName(){
    return "BoolValue";
}

StringValue::StringValue() : StringValue(""){}

StringValue::StringValue(string v){
    this->value = v;
}

string StringValue::getString() const{
    return value;
}

string StringValue::toString(){
    return getString();
}

string StringValue::getClassName(){
    return "StringValue";
}

ArrayValue::ArrayValue(Value** v, int n){
    value = v;
    this->n = n;
}

Value** ArrayValue::getArray() const{
    return value;
}

string ArrayValue::toString(){
    // TODO
    return "";
}

string ArrayValue::getClassName(){
    return "ArrayValue";
}

ArrayValue::ArrayValue(int* dims, int n, EnumValue ev) : ArrayValue(dims,1,n,ev){}

ArrayValue::ArrayValue(int* dims, int i, int n, EnumValue ev){
    this->value = new Value*[dims[i-1]];
    if(i == n){
        for(int j = 0; j < dims[i-1]; ++j){ 
            // TODO: ClassValue
            switch(ev){
                case EnumValue::EV_IntValue:
                    this->value[j] = new IntValue();
                    break;
                case EnumValue::EV_StringValue:
                    this->value[j] = new StringValue();
                    break;
                case EnumValue::EV_BoolValue:
                    this->value[j] = new BoolValue();
                    break;
            }
        }
    } else{
        for(int j = 0; j < dims[i-1]; ++j) {
            this->value[j] = new ArrayValue(dims, i+1,n,ev);
        }
    }
}


// int operators
IntValue* operator-(const IntValue& v1, const IntValue& v2) {
    return new IntValue(v1.value - v2.value);
}

IntValue* operator-(const IntValue& v1) {
    return new IntValue(-v1.value);
}

IntValue* operator*(const IntValue& v1, const IntValue& v2) {
    return new IntValue(v1.value * v2.value);
}

IntValue* operator/(const IntValue& v1, const IntValue& v2) {
    return new IntValue(v1.value / v2.value);
}

IntValue* operator%(const IntValue& v1, const IntValue& v2) {
    return new IntValue(v1.value % v2.value);
}

// int and String operators
template<typename Val>
Val* operator+(const Val& v1, const Val& v2) {
    return new Val(v1.value + v2.value);
}

template<typename Val>
BoolValue* operator<(const Val& v1, const Val& v2) {
    return new BoolValue(v1.value < v2.value);
}

template<typename Val>
BoolValue* operator<=(const Val& v1, const Val& v2) {
    return new BoolValue(v1.value <= v2.value);
}

template<typename Val>
BoolValue* operator>(const Val& v1, const Val& v2) {
    return new BoolValue(v1.value > v2.value);
}

template<typename Val>
BoolValue* operator>=(const Val& v1, const Val& v2) {
    return new BoolValue(v1.value >= v2.value);
}

// boolean operators
BoolValue* operator!(const BoolValue& v1) {
    return new BoolValue(!v1.value);
}

BoolValue* operator||(const BoolValue& v1, const BoolValue& v2) {
    return new BoolValue(v1.value || v2.value);
}

BoolValue* operator&&(const BoolValue& v1, const BoolValue& v2) {
    return new BoolValue(v1.value && v2.value);
}

// array operators
Value* Value::operator[](const int i){
    ArrayValue* arr = dynamic_cast<ArrayValue*>(this);
    return (arr->value)[i];
}

// all types operators
template<typename Val>
BoolValue* operator==(const Val& v1, const Val& v2) {
    return new BoolValue(v1.value == v2.value);
}

template<typename Val>
BoolValue* operator!=(const Val& v1, const Val& v2) {
    return new BoolValue(v1.value != v2.value);
}