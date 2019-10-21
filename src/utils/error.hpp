#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

using std::string;

void errorMsgPrefix();

void multipleClassError(string id);

void multipleMethodError(string className, string methodName);

void multipleVariableError(string id);

void multiplyDefinedFieldError(string id, string className);

void multiplyDefinedParamError(string param, string method, string className);

void idNotPredefinedError(string id);

void classNotDefinedError(string className);

void variableNotDefinedError(string var);

void methodNotFoundError(string method, string className);

void fieldNotFoundError(string field, string className);

void typeErrorBinOp(string type1, string type2, string op);

void typeErrorUnOp(string type1, string op);

void notAnObjectError(string exp, string method);

void incompatibleTypesMethodCall(string method, int position, string expectedType, string actualType);

void nonArrayExpressionError(string exp);

void nonIntArrayDimensionError(string exp);

#endif