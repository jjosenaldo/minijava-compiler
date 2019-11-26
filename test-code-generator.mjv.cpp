#include "activation-record.hpp"
#include "value.hpp"
using std::cout;
using std::endl;
struct Test : ClassValue {
Test() : ClassValue( "Test"){
initFields();
}
void initFields(){

}
static Value* newTest(){
Test* c = new Test();
c->initFields();
return c;
}
};
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr,&&l2,nullptr,nullptr);
l0: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp0 = new Test();
rs->top()->insertVar("t",tmp0);
}
Value* tmp1 = rs->top()->lookupStatic("t");
{
if(dynamic_cast<NullValue*>(tmp1) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l4 = new Value*[1];
Value* tmp3 = new StringValue("Junior");
l4[0] = tmp3;
{
rs->createRecord(nullptr,nullptr,&&l3,dynamic_cast<ClassValue*>(tmp1),nullptr);
rs->top()->insertVar("str",l4[0]);
goto l1;
}
}
l3:
Value* tmp2 = rs->top()->getReturnValue();
rs->pop();
rs->pop();
void* tmp4 = rs->top()->getMethodCallPosLabel();
goto *tmp4;
}
l1: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp5 = new StringValue("Meu nome é ");
Value* tmp6 = rs->top()->lookupStatic("str");
Value* tmp7 = *tmp5 + *tmp6;
Value* tmp8 = new StringValue("\n");
Value* tmp9 = *tmp7 + *tmp8;
cout << tmp9->toString();
}
rs->pop();
void* tmp10 = rs->top()->getMethodCallPosLabel();
goto *tmp10;
}
l2:
return 0;
}
