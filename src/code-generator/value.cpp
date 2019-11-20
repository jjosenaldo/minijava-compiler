#include "value.hpp"

using std::to_string;

IntValue::IntValue(int v){
    value = v;
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

// TODO: implement string concatenation (it'll need a cast)
IntValue* operator+(const Value& v1, const Value& v2){
    return new IntValue(v1.getInt() + v2.getInt());
}

BoolValue* operator<(const Value& v1, const Value& v2){
	return new BoolValue(v1.getInt() < v2.getInt());
}
