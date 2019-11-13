#include "value.hpp"

using std::to_string;

IntValue::IntValue(int v){
    value = v;
}

int IntValue::getValue(){
    return value;
}

string IntValue::toString(){
    return to_string(value);
}

Value* IntValue::operator+(Value *b) {
	IntValue *ib = dinamic_cast<IntValue*>(b);
	return new IntValue(a.getInt() + ib->getInt()); // segmentation fault ???
}