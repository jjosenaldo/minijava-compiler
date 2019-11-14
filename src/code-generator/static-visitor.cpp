#include "global.hpp"
#include "expression.hpp"
#include "static-visitor.hpp"

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
        if(dim->accept(*this))
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