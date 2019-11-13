#include "value.hpp"

using std::to_string;

IntValue::IntValue(int v){
    value = v;
}

string IntValue::toString(){
    return to_string(value);
}

Value* IntValue::operator+(Value &b) {
	IntValue *ib = dynamic_cast<IntValue*>(&b);
	return new IntValue(this->getInt() + ib->getInt()); // segmentation fault ???
}

int IntValue::getInt() {
    return this->value;
}