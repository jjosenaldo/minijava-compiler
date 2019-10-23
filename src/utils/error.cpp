#include <iostream>
#include "error.hpp"

using std::cout;
using std::endl;

void multipleClassError(string id){
    errorMsgPrefix();
    cout << "the class " << id << " was multiply defined" << endl;
}

void multipleMethodError(string className, string methodName){
    errorMsgPrefix();
    cout << "the entity " << methodName << " in the class " << className << " is multiply defined" << endl;
}

void multipleVariableError(string id){
    errorMsgPrefix();
    cout << "the variable " << id << " is already defined in this scope" << endl;
}

void multiplyDefinedFieldError(string id, string className){
    errorMsgPrefix();
    cout << "the field " << id << " is multiply defined in the class " << className << endl;
}

void multiplyDefinedParamError(string param, string method, string className){
    errorMsgPrefix();
    cout << "there are many params named " << param << " in the method " << method << " of the " << className << " class" << endl; 
}

void idNotPredefinedError(string id){
    errorMsgPrefix();
    cout << "the id " << id << " is not one of the predefined ones" << endl;
}

void classNotDefinedError(string className){
    errorMsgPrefix();
    cout << "the class " << className << " is not defined" << endl;
}

void variableNotDefinedError(string var){
    errorMsgPrefix();
    cout << "the variable " << var << " is not defined" << endl;
}

void methodNotFoundError(string method, string className){
    errorMsgPrefix();
    cout << "the method " << method << " was not defined in the class " << className << endl;
}

void fieldNotFoundError(string field, string className){
    errorMsgPrefix();
    cout << "the class " << className << " does not contain a field called " << field << endl;
}

void typeErrorBinOp(string type1, string type2, string op){
    errorMsgPrefix();
    cout << "the operator " << op << " can't be applied to arguments of types " << type1 << " and " << type2 << endl;
}

void typeErrorUnOp(string type1, string op){
    errorMsgPrefix();
    cout << "the operator " << op << " can't be applied to an argument of type " << type1 << endl;
}

void notAnObjectError(string exp, string method){
    errorMsgPrefix();
    cout << "the expression " << exp << " is not an object, so it cannot call methods, such as " << method << endl;
}

void incompatibleTypesMethodCall(string method, int position, string expectedType, string actualType){
    errorMsgPrefix();
    cout << "the method " << method << " expects a " << expectedType << " at the position " << position << " but a " << actualType << " was given" << endl;
}

void nonArrayExpressionError(string exp){
    errorMsgPrefix();
    cout << "the expression " << exp << " is not an array but it's being used as such" << endl;
}

void nonIntArrayDimensionError(string exp){
    errorMsgPrefix();
    cout << "the expression " << exp << " is not an int so it cannot be used as an array dimension" << endl;
}

void diffNumberOfArgsMethodError(string method, int actual, int expected){
    errorMsgPrefix();
    cout << "the method " << method << " was called with " << actual << " arguments but it requires " << expected << endl;
}

void arrayOfInvalidTypeError(string type){
    errorMsgPrefix();
    cout << "you cannot make an array of type " << type << endl;
}

void newTypeIsNotAnExpression(string type){
    cout << "the string \"new " << type << "\" is not an expression" << endl;
}

void errorMsgPrefix(){
    cout << "ERROR: ";
}