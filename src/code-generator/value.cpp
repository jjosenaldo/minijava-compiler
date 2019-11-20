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

// int and String operators
Value* operator+(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new IntValue(i1->getInt() + i2->getInt());

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new StringValue(s1->getString() + s2->getString());
    
    throw "Invalid operands between operator +";
}

Value* operator<(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new BoolValue(i1->getInt() < i2->getInt());

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new BoolValue(s1->getString() < s2->getString());
    
    throw "Invalid operands between operator <";
}

Value* operator<=(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new BoolValue(i1->getInt() <= i2->getInt());

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new BoolValue(s1->getString() <= s2->getString());
    
    throw "Invalid operands between operator <=";
}

Value* operator>(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new BoolValue(i1->getInt() > i2->getInt());

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new BoolValue(s1->getString() > s2->getString());
    
    throw "Invalid operands between operator >";
}

Value* operator>=(const Value& v1, const Value& v2) {
    const IntValue* i1 = dynamic_cast<const IntValue*>(&v1);
    const IntValue* i2 = dynamic_cast<const IntValue*>(&v2);

    if(i1 != nullptr and i2 != nullptr)
        return new BoolValue(i1->getInt() >= i2->getInt());

    const StringValue* s1 = dynamic_cast<const StringValue*>(&v1);
    const StringValue* s2 = dynamic_cast<const StringValue*>(&v2);

    if(s1 != nullptr and s2 != nullptr)
        return new BoolValue(s1->getString() >= s2->getString());
    
    throw "Invalid operands between operator >=";
}

// boolean operators
Value* operator!(const Value& v1) {
    const BoolValue* b1 = dynamic_cast<const BoolValue*>(&v1);

    if(b1 != nullptr)
        return new BoolValue(!b1->getBool());

    throw "Invalid operand in operator !";
}

Value* operator||(const Value& v1, const Value& v2) {
    const BoolValue* b1 = dynamic_cast<const BoolValue*>(&v1);
    const BoolValue* b2 = dynamic_cast<const BoolValue*>(&v2);

    if(b1 != nullptr and b2 != nullptr)
        return new BoolValue(b1->getBool() || b2->getBool());
    
    throw "Invalid operands between operator ||";
}

Value* operator&&(const Value& v1, const Value& v2) {
    const BoolValue* b1 = dynamic_cast<const BoolValue*>(&v1);
    const BoolValue* b2 = dynamic_cast<const BoolValue*>(&v2);

    if(b1 != nullptr and b2 != nullptr)
        return new BoolValue(b1->getBool() && b2->getBool());
    
    throw "Invalid operands between operator &&";
}

// all types operators
// TODO: Do it for all Types (waiting for ClassValue)
Value* operator==(const Value& v1, const Value& v2) { return nullptr; }
Value* operator!=(const Value& v1, const Value& v2) { return nullptr; }