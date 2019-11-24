#include "src/code-generator/activation-record.hpp"
#include "src/code-generator/value.hpp"
using std::cout;
using std::endl;
struct Main : ClassValue {
Main() : ClassValue( "Main"){}
};
struct Cat : ClassValue {
Cat() : ClassValue( "Cat"){}
};
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr,&&l2);
l0: {
rs->createRecord(nullptr,nullptr,nullptr);
{
Value* tmp0 = new Cat();
rs->top()->insertVar("c",tmp0);
}
{
rs->createRecord(nullptr,nullptr,&&l3);
Value* tmp0 = new IntValue(10);
rs->top()->insertVar("steps",tmp0);
goto l1;
}
l3:
rs->pop();
void* tmp1 = rs->top()->getReturnLabel();
rs->pop();
goto *tmp1;
}
l1: {
rs->createRecord(nullptr,nullptr,nullptr);
{
Value* _steps = rs->top()->lookupVarVal("steps");
Value* tmp0 = new IntValue(0);
Value* tmp1 = *_steps > *tmp0;
if(!tmp1->getBool()) goto l4;
rs->createRecord(nullptr,nullptr,nullptr);
{
Value* tmp2 = new StringValue("yes, steps:");
Value* _steps = rs->top()->lookupVarVal("steps");
Value* tmp3 = new StringValue( _steps->toString());
Value* tmp4 = *tmp2 + *tmp3;
cout << tmp4->toString() << endl;
}
{
rs->createRecord(nullptr,nullptr,&&l5);
Value* _steps = rs->top()->lookupVarVal("steps");
Value* tmp0 = new IntValue(1);
Value* tmp1 = *_steps - *tmp0;
rs->top()->insertVar("steps",tmp1);
goto l1;
}
l5:
rs->pop();
l4:;
}
rs->pop();
void* tmp2 = rs->top()->getReturnLabel();
rs->pop();
goto *tmp2;
}
l2:
return 0;
}
