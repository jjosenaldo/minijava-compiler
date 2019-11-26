#include "activation-record.hpp"
#include "value.hpp"
using std::cout;
using std::endl;
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr,&&l1,nullptr,nullptr);
l0: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp0 = new StringValue("oi, eu tenho ");
cout << tmp0->toString();
}
{
Value* tmp1 = new IntValue(21);
Value* tmp2 = new StringValue( tmp1->toString());
cout << tmp2->toString();
}
{
Value* tmp3 = new StringValue(" anos! e isso é ");
Value* tmp4 = new BoolValue(true);
Value* tmp5 = new StringValue( tmp4->toString());
Value* tmp6 = *tmp3 + *tmp5;
cout << tmp6->toString();
}
rs->pop();
void* tmp7 = rs->top()->getMethodCallPosLabel();
goto *tmp7;
}
l1:
return 0;
}
