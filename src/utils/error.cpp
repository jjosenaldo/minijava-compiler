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
    errorMsgPrefix();
    cout << "the string \"new " << type << "\" is not an expression" << endl;
}

void classAsExpressionError(string id){
    errorMsgPrefix();
    cout << id << " is a class name so it cannot be used as an expression" << endl;
}

void classAsVariableNameError(string id){
    errorMsgPrefix();
    cout << id << " is a class name so it cannot be used as the name of a variable" << endl;
}

void classInheritsFromItselfError(string id){
    errorMsgPrefix();
    cout << "the class " << id << " inherits from itself, which is not allowed" << endl;
}

void circularInheritanceError(string id){
    errorMsgPrefix();
    cout << "circular inheritance involving the class " << id << endl;
}

void methodCallOnNonobjectError(string expr){
    errorMsgPrefix();
    cout << "you called a method on the expression " << expr << " but it is not an object" << endl;
}

void varDeclarationTypeError(string id, string expected, string actual){
    errorMsgPrefix();
    cout << "you can't assign a value of type " << actual << " to a variable (" << id << ") of type " << expected << endl;
}

void typeError(string expected, string actual){
    errorMsgPrefix();
    cout << "you used a " << actual << " when a " << expected << " was expected" << endl;
}

void notAnLvalueError(string exp){
    errorMsgPrefix();
    cout << "the expression " << exp << " is not a lvalue" << endl;
}

void instanceOfMainClassError(){
    errorMsgPrefix();
    cout << "you cannot create an object with the main class as type" << endl;
}

void instanceOfForbiddenTypeError(string type){
    errorMsgPrefix();
    cout << "you cannot create an object of type " << type << endl;
}

void inheritanceFromMainClassError(string id){
    errorMsgPrefix();
    cout << "the class " << id << " is inheriting from the main class" << endl;
}

void mainMethodNameError(string mainMethod, string otherMethod){
    errorMsgPrefix();
    cout << "the main method should be called " << mainMethod << ", not " << otherMethod << endl;
}

void callMainMethodError(){
    errorMsgPrefix();
    cout << "you cannot call the main method" << endl;
}

void breakOutsideLoop() {
    errorMsgPrefix();
    cout << "you cannot call a break from outside a loop" << endl;
}

void methodReturnTypeError(string returned, string expected, string methodName) {
    errorMsgPrefix();
    cout << "expected " << expected << " but returned " << returned << " in method " << methodName << endl;
}

void attributeInitValueTypeError(string id, string expected, string actual) {
    errorMsgPrefix();
    cout << "you can't initialize attribute (" << id << ") of type " << expected << " with a value of type " << actual << endl;
}

void nonDefaultClassError(string id){
    errorMsgPrefix();
    cout << id << " is not a default class" << endl;
}

void nonExistingMethodInDefaultClass(string className, string method){
    errorMsgPrefix();
    cout << "the default class " << className << " doesn't have a default method called " << method << endl;
}

void errorMsgPrefix(){
    cout << "ERROR: ";
}
