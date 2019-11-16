#include "value.hpp"

using std::to_string;

IntValue::IntValue(int v){
    value = v;
}

string IntValue::toString(){
    return to_string(value);
}

// TODO: implement concatenation of strings
Value* IntValue::operator+(Value &b) {
	IntValue *ib = dynamic_cast<IntValue*>(&b);
	return new IntValue(this->getInt() + ib->getInt()); 
}

// TODO: implement unary operators (namely, ! and unary -)

int IntValue::getInt() {
    return this->value;
}