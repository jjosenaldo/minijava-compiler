#include "src/code-generator/activation-record.hpp"
#include "src/code-generator/value.hpp"
using std::cout;
using std::endl;
struct Main : ClassValue {
};
struct Test : ClassValue {
};
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr,&&l2);
l0: {
rs->createRecord(nullptr,nullptr,nullptr);
{
Value* tmp0 = rs->allocate(Test());
rs->top()->insertVar("t",tmp0);
}
{
rs->createRecord(nullptr,nullptr,&&l3);
Value* tmp0 = new StringValue("Junio");
rs->top()->insertVar("str",tmp0);
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
Value* tmp0 = new StringValue("Meu nome é");
Value* _str = rs->top()->lookupVarVal("str");
Value* tmp1 = *tmp0 + *_str;
Value* tmp2 = new StringValue("\n");
Value* tmp3 = *tmp1 + *tmp2;
cout << tmp3->toString() << endl;
}
rs->pop();
void* tmp0 = rs->top()->getReturnLabel();
rs->pop();
goto *tmp0;
}
l2:
return 0;
}
