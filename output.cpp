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
rs->createRecord(nullptr,nullptr,&&l3);
l0: {
rs->createRecord(nullptr,nullptr,nullptr);
{
Value* tmp0 = new Cat();
rs->top()->insertVar("c",tmp0);
}
{
rs->createRecord(nullptr,nullptr,&&l4);
Value* tmp0 = new IntValue(1);
rs->top()->insertVar("a",tmp0);
goto l2;
}
l4:
rs->pop();
void* tmp1 = rs->top()->getReturnLabel();
rs->pop();
goto *tmp1;
}
l1: {
rs->createRecord(nullptr,nullptr,nullptr);
{
Value* tmp0 = new StringValue("socorr");
cout << tmp0->toString() << endl;
}
rs->pop();
void* tmp0 = rs->top()->getReturnLabel();
rs->pop();
goto *tmp0;
}
l2: {
rs->createRecord(nullptr,nullptr,nullptr);
{
Value* _a = rs->top()->lookupVarVal("a");
Value* tmp0 = new StringValue( _a->toString());
cout << tmp0->toString() << endl;
}
rs->pop();
void* tmp0 = rs->top()->getReturnLabel();
rs->pop();
goto *tmp0;
}
l3:
return 0;
}
