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