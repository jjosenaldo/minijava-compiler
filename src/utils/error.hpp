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

void incompatibleTypesMethodCall(string method, int position, string expectedType, string actualType);

void nonArrayExpressionError(string exp);

void nonIntArrayDimensionError(string exp);

void diffNumberOfArgsMethodError(string method, int actual, int expected);

void arrayOfInvalidTypeError(string type);

void newTypeIsNotAnExpression(string type);

void classAsExpressionError(string id);

void classAsVariableNameError(string id);

void classInheritsFromItselfError(string id);

void circularInheritanceError(string id);

void methodCallOnNonobjectError(string expr);

void varDeclarationTypeError(string id, string expected, string actual);

void notAnLvalueError(string exp);

void typeError(string expected, string actual);

void instanceOfMainClassError();

void instanceOfForbiddenTypeError(string type);

void inheritanceFromMainClassError(string id);

void mainMethodNameError(string mainMethod, string otherMethod);

void callMainMethodError();

void breakOutsideLoopError();

void methodReturnTypeError(string returned, string expected, string methodName);

void attributeInitValueTypeError(string id, string expected, string actual);

void nonDefaultClassError(string id);

void nonExistingMethodInDefaultClass(string className, string method);

void nonstaticMethodOnDefaultClassNotFound(string className, string method);

void typeDoesntContainNonstaticMethodError(string type, string method);

void classAsFieldNameError(string name);

void classAsMethodNameError(string methodName);

void returnPathError(string methodName);

void notBooleanGuardError();

#endif