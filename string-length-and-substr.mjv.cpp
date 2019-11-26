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
Value* tmp0 = new StringValue("oi");
Value* tmp1 = new StringValue("tudo");
Value* tmp2 = *tmp0 + *tmp1;
Value* tmp3 = new StringValue("bom");
Value* tmp4 = *tmp2 + *tmp3;
Value* tmp5 = new IntValue(dynamic_cast<StringValue*>(tmp4)->getString().length());
Value* tmp6 = new StringValue( tmp5->toString());
cout << tmp6->toString();
}
{
Value* tmp7 = new StringValue("\n");
cout << tmp7->toString();
}
{
Value* tmp8 = new StringValue("o rato roeu a ropa do rei de roma e a rainha com raiva roeu o resto");
rs->top()->insertVar("a",tmp8);
}
{
Value* tmp9 = rs->top()->lookupStatic("a");
Value* tmp11 = new IntValue(10);
Value* tmp12 = new IntValue(20);
Value* tmp10 = new StringValue(dynamic_cast<StringValue*>(tmp9)->getString().substr(dynamic_cast<IntValue*>(tmp11)->getInt(),dynamic_cast<IntValue*>(tmp12)->getInt()));
cout << tmp10->toString();
}
{
Value* tmp13 = new StringValue("\n");
cout << tmp13->toString();
}
rs->pop();
void* tmp14 = rs->top()->getMethodCallPosLabel();
goto *tmp14;
}
l1:
return 0;
}
