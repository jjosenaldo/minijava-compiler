#include "ast.hpp"
#include "expression.hpp"
#include "global.hpp"
#include "statement.hpp"
#include "static-visitor.hpp"
#include "type.hpp"

StaticVisitor::StaticVisitor(Symtable* environment, ClassSymtablePool* pool){
    this->environment = environment;
    this->pool = pool;
}

bool StaticVisitor::visit(BinExpression* exp){
    Expression* first = exp->first;
    Expression* second = exp->second;
    auto op = exp->op;

    bool retFirst = first->accept(*this);
    bool retSecond = second->accept(*this);

    if(!retFirst || !retSecond)
        return false;

    Type* newType = returnTypeBinOp(first->getType(), second->getType(), op);

    if(newType == nullptr){
        typeErrorBinOp(first->getType()->toString(), second->getType()->toString(), binOpSymbol(op));
        return false;
    }

    exp->setType(newType);
    return true;
}

bool StaticVisitor::visit(UnExpression* exp){
    Expression* first = exp->first;
    bool retFirst = first->accept(*this);
    auto op = exp->op;

    if(!retFirst)
        return false;

    Type* newType = returnTypeUnOp(first->getType(), op);

    if(newType == nullptr){
        typeErrorUnOp(first->getType()->toString(), unOpSymbol(op));
        return false;
    }

    exp->setType(newType);
    return true;
}

bool StaticVisitor::visit(AtomExpression* exp){
    return true;
}

bool StaticVisitor::visit(ArrayDeclExpression* exp) {
    Type* type = exp->type;

    switch(type->kind){
        case TypeNull:
            arrayOfInvalidTypeError(type->toString());
            return false;
        case TypeMethod:
            arrayOfInvalidTypeError(type->toString());
            return false;
        case TypeVoid:
            arrayOfInvalidTypeError(type->toString());
            return false;
        case TypeClass:
            if(pool->get(type->getClassName()) == nullptr){
                classNotDefinedError(type->getClassName());
                return false;
            }
    }

    return true;
}

bool StaticVisitor::visit(NewObjExpression* exp) {
    string id = exp->id;

    if(pool->get(id) == nullptr){
        classNotDefinedError(id);
        return false;
    }

    exp->setType(MkTypeClass(id));
    return true;
}

bool StaticVisitor::visit(IdExpression* exp){
    string id = exp->id;

    if(predefinedId(id) || pool->get(id) != nullptr){
        classAsExpressionError(id);
        return false;
    }

    TableContent tc = environment->lookup(id);

    if(tc.tag != TCTYPE){
        variableNotDefinedError(id);
        return false;
    }

    exp->setType(tc.type);
    
    return true;
}

bool StaticVisitor::visit(FieldAccessExpression* exp){
    string id = exp->id;
    TableContent tc;
    string currentClass = environment->getClassName();

    while(currentClass != ""){
        tc = pool->get(currentClass)->get(id);

        // The class doesn't contain the field
        if(tc.tag == TCNOCONTENT || (tc.tag == TCTYPE && tc.type->kind == TypeMethod))

            // Looks in its parent
            currentClass = g_classParentMap[currentClass];

        else{
            exp->setType(tc.type);
            return true;
        }
    }

    fieldNotFoundError(id, environment->getClassName());
    return false;
}

bool StaticVisitor::visit(ThisExpression* exp){
    exp->setType(MkTypeClass(environment->getClassName()));
    return true;
}

bool StaticVisitor::visit(ParenExpression* exp){
    auto first = exp->first;
    bool retFirst = first->accept(*this);

    if(!retFirst)
        return false;

    exp->setType(exp->first->getType());
    return true;
}

bool StaticVisitor::visit(LitArrayExpression* exp){
    auto expressions = exp->expressions;

    Type** types = new Type*[expressions->size()];
    bool retExp;

    int i = 0;
    for(auto otherExp : *expressions){
        retExp = otherExp->accept(*this);

        if(!retExp){
            delete[] types;
            return false;
        }

        types[i++] = otherExp->getType();
    }

    Type* resType = resultingType(types, expressions->size());
    delete[] types;

    if(resType == nullptr)
        return false;

    exp->setType(resType);
    return true;
}

bool StaticVisitor::visit(MethodCallExpression* exp) {
    auto method = exp->method;
    auto left = exp->left;
    auto arguments = exp->arguments;

    Type* type = nullptr;
    
    if(environment->getClassName() == g_mainClassName){
        if(method == MAIN_METHOD_NAME){
            callMainMethodError();
            return false;
        }
    }
    
    auto visitor = StaticVisitor(environment, pool);
    bool leftResult = left->accept(visitor);

    // The callee expression is not well-formed
    if(!leftResult)
        return false;

    // The callee expression is an object
    if(left->isObject()){
        string className = left->getType()->getClassName();

        if(g_defaultSymbolHandler.isDefaultClass(className)){
            MethodType* res = g_defaultSymbolHandler.getDefaultNonstaticMethodHeader(className, method);

            if(res == nullptr){
                nonstaticMethodOnDefaultClassNotFound(className, method);
                return false;
            } else type = res;
        } else{
            ClassSymtable* classTable = pool->get(className);
            TableContent tc = classTable->get(method);

            // Search for the method (including the ancestor classes)
            string currentClass = left->getType()->getClassName();
            bool methodFound = false;

            while(currentClass != ""){
                tc = pool->get(currentClass)->get(method);

                // The class doesn't contain the field
                if(tc.tag == TCNOCONTENT || (tc.tag == TCTYPE && tc.type->kind != TypeMethod))

                    // Looks in its parent
                    currentClass = g_classParentMap[currentClass];

                else{
                    methodFound = true;
                    break;
                }
            }

            // The method doesnt exist
            if(!methodFound){
                methodNotFoundError(method, left->getType()->getClassName());
                return false;
            }

            type = tc.type;
        }
    } else{
        type = g_defaultSymbolHandler.getDefaultNonstaticMethodHeader(left->getType(), method);

        if(type == nullptr){
            typeDoesntContainNonstaticMethodError(left->getType()->toString(), method);
            return false;
        }
    }



    vector<Type*>* methodHeader = type->getMethodHeader();
    int expectedArgs = methodHeader->size() - 1;

    if(arguments == nullptr) {
        if(expectedArgs != 0){
            diffNumberOfArgsMethodError(method, 0, expectedArgs);
            return false;
        }

        exp->setType(methodHeader->at(0));
        return true;
    }

    if(arguments->size() != expectedArgs){
        diffNumberOfArgsMethodError(method, arguments->size(), expectedArgs);
        return false;
    }

    for(int i = 0; i < expectedArgs; ++i){
        if(!  arguments->at(i)->accept(visitor)  )
            return false;

        if(!areCompatibleTypes(methodHeader->at(i+1), arguments->at(i)->getType()  )    ){ // +1 because the first element is the return type
            incompatibleTypesMethodCall(method, i+1, methodHeader->at(i+1)->toString(), arguments->at(i)->getType()->toString());
            return false;
        }
    }

    type = methodHeader->at(0);

    exp->setType(type);
    return true;
}

bool StaticVisitor::visit(StaticMethodCallExpression* exp){
    auto method = exp->method;
    auto className = exp->className;
    auto methodHeader = g_defaultSymbolHandler.getDefaultStaticMethodHeader(className, method);
    auto arguments = exp->arguments;

    if(methodHeader == nullptr){
        nonExistingMethodInDefaultClass(className, method);
        return false;
    }

    int expectedArgs = methodHeader->getMethodHeader()->size() - 1;

    if(arguments == nullptr) {
        if(expectedArgs != 0){
            diffNumberOfArgsMethodError(method, 0, expectedArgs);
            return false;
        }

        exp->setType(methodHeader->getMethodHeader()->at(0));
        return true;
    }

    if(arguments->size() != expectedArgs){
        diffNumberOfArgsMethodError(method, arguments->size(), expectedArgs);
        return false;
    }

    for(int i = 0; i < expectedArgs; ++i){
        auto visitor = StaticVisitor(environment, pool);
        if(!  arguments->at(i)->accept(visitor)  )
            return false;

        if(!areCompatibleTypes(methodHeader->getMethodHeader()->at(i+1), arguments->at(i)->getType()  )    ){ // +1 because the first element is the return type
            incompatibleTypesMethodCall(method, i+1, methodHeader->getMethodHeader()->at(i+1)->toString(), arguments->at(i)->getType()->toString());
            return false;
        }
    }

    exp->setType(methodHeader->getMethodHeader()->at(0));
    return true;
}

bool StaticVisitor::visit(ArrayAccessExpression* exp){
    auto left = exp->left; 
    auto dimensions = exp->dimensions;

    bool retLeft = left->accept(*this);

    if(!retLeft)
        return false;

    Type* currentType = left->getType();

    for(auto dim : *dimensions){
        if(currentType->kind != TypeArray){
            nonArrayExpressionError(left->toString());
            return false;
        }

        bool ret = dim->accept(*this);

        if(!ret)
            return false;

        if(dim->getType()->kind != TypeInt){
            nonIntArrayDimensionError(dim->toString());
            return false;
        }

        currentType = currentType->getBaseType();
    }

    exp->setType(currentType);
    return true;
}

bool StaticVisitor::visit(NewArrayExpression* exp){
    auto dimensions = exp->dimensions;
    auto type = exp->type;

    for(auto dim : *dimensions)
        if(!dim->accept(*this))
            return false;

    if(type->kind == TypeMethod || type->kind == TypeNull || type->kind == TypeVoid){
        arrayOfInvalidTypeError(type->toString());
        return false;
    }

    if(type->kind == TypeClass){
        if(predefinedId(type->getClassName()))
            return true;

        if(pool->get(type->getClassName()) != nullptr)
            return true;

        classNotDefinedError(type->getClassName());
        return false;
    }

    return true;
}

bool StaticVisitor::visit(VarDec* stmt) {
    auto id = stmt->id;
    auto type = stmt->type;
    auto value = stmt->value;

    if(type->kind == TypeClass && !g_defaultSymbolHandler.isDefaultClass(type->getClassName())){
        if(pool->get(type->getClassName()) == nullptr){
            classNotDefinedError(type->getClassName());
            return false;
        }

        if(g_mainClassName == type->getClassName()){
            instanceOfMainClassError();
            return false;
        }
    }
    
    if(!canBeInstantiated(type, pool))
        return false;

    if(g_defaultSymbolHandler.isDefaultClass(id) || pool->get(id) != nullptr){
        classAsVariableNameError(id);
        return false;
    }

    if(environment->get(id).tag != TCNOCONTENT){
        multipleVariableError(id);
        return false;
    }

    if(value != nullptr){
        if(!value->accept(*this))
            return false;

        if(!areCompatibleTypes(type, value->getType())){
            varDeclarationTypeError(id, type->toString(), value->getType()->toString());
            return false;
        }

        if(value->getType()->kind == TypeClass)
            type->setActualClassName(value->getType()->getClassName());
    }

    environment->insert(id, tableContentFromType(type));

    return true;
}

bool StaticVisitor::visit(Block* stmt) {
    auto oldEnvironment = environment;
    auto statements = stmt->statements;
    Symtable* table = new Symtable(environment->getClassName(), environment->getMethodName());
    table->setParent(environment);
    environment = table;

    if(statements != nullptr)
        for(auto stmt : *statements){
            if(!stmt->accept(*this))
                return false;
        }

    environment = oldEnvironment;
    environment->insert(table);
    return true;
}

bool StaticVisitor::visit(ElselessIf* stmt) {
    if(!stmt->guard->accept(*this))
        return false;
    
    if(stmt->guard->getType()->kind != TypeBoolean){
        notBooleanGuardError();
        return false;
    }
    
    return stmt->statement->accept(*this);
}

bool StaticVisitor::visit(IfElse* stmt) {
    if(!stmt->guard->accept(*this))
        return false;
    
    if(stmt->guard->getType()->kind != TypeBoolean){
        notBooleanGuardError();
        return false;
    }

    return stmt->statementIf->accept(*this) && stmt->statementElse->accept(*this);
}

bool StaticVisitor::visit(While* stmt) {
    if(!stmt->guard->accept(*this))
        return false;
    
    if(stmt->guard->getType()->kind != TypeBoolean){
        notBooleanGuardError();
        return false;
    }

    pool->setIsLoopBlock(true);
    bool r = stmt->statement->accept(*this);
    pool->setIsLoopBlock(false);
    return r;
}

bool StaticVisitor::visit(Assignment* stmt) {
    auto lvalue = stmt->lvalue;
    auto rvalue = stmt->rvalue;

    if(!lvalue->accept(*this))
        return false;

    if(!lvalue->isLvalue()){
        notAnLvalueError(lvalue->toString());
        return false;
    }

    if(!rvalue->accept(*this))
        return false;

    if(!areCompatibleTypes(lvalue->getType(), rvalue->getType())){
        typeError(lvalue->getType()->toString(), rvalue->getType()->toString());
        return false;
    }

    return true;
}

bool StaticVisitor::visit(Continue* stmt) {
    if(!pool->isLoopBlock()){
        breakOutsideLoopError();
        return false;
    } else {
        return true;
    }
}

bool StaticVisitor::visit(Break* stmt) {
    if(!pool->isLoopBlock()){
        breakOutsideLoopError();
        return false;
    } else {
        return true;
    }
}

bool StaticVisitor::visit(Return* stmt) {
    auto optExp = stmt->optExp;

    Type* optExpType = MkTypeVoid();
    if(optExp != nullptr){
        bool res = optExp->accept(*this);

        if(!res)
            return false;
        
        optExpType = optExp->getType();
    }

    ClassSymtable* classTable = pool->get(environment->getClassName());
    TableContent tc = classTable->get(environment->getMethodName());
    Type* methodReturnType = tc.type->getMethodHeader()->at(0);
    if(!areCompatibleTypes(optExpType, methodReturnType)){
        methodReturnTypeError(optExpType->toString(), methodReturnType->toString(), environment->getMethodName());
        return false;
    }

   return true;
}

bool StaticVisitor::visit(Skip* stmt){
    return true;
}

bool StaticVisitor::visitMethodHeader(Method* method, ClassSymtable* root, string className){
    string methodName = method->id;
    auto returnType = method->returnType;
    auto parameters = method->parameters;

    if(pool->get(methodName) != nullptr || g_defaultSymbolHandler.isDefaultClass(methodName)){
        classAsMethodNameError(methodName);
        return false;
    }

    if(root->get(methodName).tag != TCNOCONTENT){
        multipleMethodError(className, methodName);
        return false;
    }

    if(returnType->kind == TypeClass & pool->get(returnType->getClassName()) == nullptr){
        classNotDefinedError(returnType->getClassName());
        return false;
    }

    // Adds the method name
    TableContent tcMethodType;
    tcMethodType.tag = TCTYPE;
    tcMethodType.type = method->getType();
    root->insert(methodName, tcMethodType);

    Symtable* methodTable = new Symtable(className, root);
    environment = methodTable;

    // Adds the method params
    auto params = parameters;
    if(params != nullptr)
        for(auto param : *params){
            if(methodTable->get(param->getName()).tag != TCNOCONTENT){
                multiplyDefinedParamError(param->getName(), methodName, className);
                delete methodTable;
                return false;
            }

            if(!this->visit(param))
                return false;
        }

    root->insertMethodTable(methodName, methodTable);
    return true;
}

bool StaticVisitor::visit(Field* field, ClassSymtable* root, string className) {
    auto type = field->type;
    auto name = field->name;
    auto initValue = field->initValue;

    if(root->get(name).tag != TCNOCONTENT){
        multiplyDefinedFieldError(name, className);
        return false;
    }

    if(pool->get(name) != nullptr || g_defaultSymbolHandler.isDefaultClass(name)){
        classAsFieldNameError(name);
        return false;
    }

    if(initValue != nullptr){
        if(!initValue->accept(*this))
            return false;

            if(!areCompatibleTypes(type, initValue->getType())){
                attributeInitValueTypeError(name, type->toString(), initValue->getType()->toString());
                return false;
            }
    }
    
    TableContent tc;
    tc.tag = TCTYPE;
    tc.type = type;
    root->insert(name, tc);

    return true;
}

bool StaticVisitor::visit(Parameter* param) {
    auto type = param->type;
    auto name = param->name;

    if(!canBeInstantiated(type, pool))
        return false;

    if(predefinedId(name) || pool->get(name) != nullptr){
        classAsVariableNameError(name);
        return false;
    }

    if(environment->get(name).tag != TCNOCONTENT) {
        multipleVariableError(name);
        return false;
    }

    environment->insert(name, tableContentFromType(type));

    return true;
}