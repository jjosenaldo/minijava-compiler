#include "activation-record.hpp"
#include "value.hpp"
using std::cout;
using std::endl;
struct TestReturnFlow : ClassValue {
TestReturnFlow() : ClassValue( "TestReturnFlow"){
initFields();
}
void initFields(){

}
static Value* newTestReturnFlow(){
TestReturnFlow* c = new TestReturnFlow();
c->initFields();
return c;
}
};
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr,&&l5,nullptr,nullptr);
l0: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
rs->pop();
void* tmp0 = rs->top()->getMethodCallPosLabel();
goto *tmp0;
}
l1: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp3 = new IntValue(0);
void* tmp1 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp3); 
goto *tmp1;
}
rs->pop();
void* tmp4 = rs->top()->getMethodCallPosLabel();
goto *tmp4;
}
l2: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp5 = rs->top()->lookupStatic("a");
Value* tmp6 = rs->top()->lookupStatic("b");
Value* tmp7 = *tmp5 == *tmp6;
if(!tmp7->getBool()) goto l6;
{ 
{
Value* tmp10 = rs->top()->lookupStatic("a");
void* tmp8 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp10); 
goto *tmp8;
}
} 
} 
l6:;
{
Value* tmp13 = rs->top()->lookupStatic("b");
void* tmp11 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp13); 
goto *tmp11;
}
rs->pop();
void* tmp14 = rs->top()->getMethodCallPosLabel();
goto *tmp14;
}
l3: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp15 = rs->top()->lookupStatic("a");
Value* tmp16 = rs->top()->lookupStatic("b");
Value* tmp17 = *tmp15 == *tmp16;
if(!tmp17->getBool()) goto l7;
{ 
{
Value* tmp20 = rs->top()->lookupStatic("a");
void* tmp18 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp20); 
goto *tmp18;
}
} 
goto l8;
{ 
l7:
{
Value* tmp23 = rs->top()->lookupStatic("b");
void* tmp21 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp23); 
goto *tmp21;
}
} 
} 
l8:;
rs->pop();
void* tmp24 = rs->top()->getMethodCallPosLabel();
goto *tmp24;
}
l4: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
rs->top()->insertVar("temp",new IntValue);
}
{
Value* tmp25 = rs->top()->lookupStatic("b");
Value* tmp26 = rs->top()->lookupStatic("a");
Value* tmp27 = *tmp25 < *tmp26;
if(!tmp27->getBool()) goto l9;
{ 
{
Value* tmp28 = rs->top()->lookupStatic("b");
rs->top()->updateStatic("temp",tmp28);
}
} 
goto l10;
{ 
l9:
{
Value* tmp31 = rs->top()->lookupStatic("b");
Value* tmp32 = rs->top()->lookupStatic("a");
Value* tmp33 = *tmp31 - *tmp32;
void* tmp29 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp33); 
goto *tmp29;
}
} 
} 
l10:;
{
Value* tmp34 = new IntValue(0);
rs->top()->insertVar("diff",tmp34);
}
rs->createRecord(&&l11,&&l12,nullptr,rs->top()->getCurrentObject(),nullptr);
{
l11:
Value* tmp35 = rs->top()->lookupStatic("temp");
Value* tmp36 = rs->top()->lookupStatic("b");
Value* tmp37 = *tmp35 != *tmp36;
if(!tmp37->getBool()) goto l12;
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp38 = rs->top()->lookupStatic("temp");
Value* tmp39 = new IntValue(1);
Value* tmp40 = *tmp38 + *tmp39;
rs->top()->updateStatic("temp",tmp40);
}
{
Value* tmp41 = rs->top()->lookupStatic("diff");
Value* tmp42 = new IntValue(1);
Value* tmp43 = *tmp41 + *tmp42;
rs->top()->updateStatic("diff",tmp43);
}
rs->pop();
goto l11;
}
l12:;
rs->pop();
{
Value* tmp46 = rs->top()->lookupStatic("diff");
void* tmp44 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp46); 
goto *tmp44;
}
rs->pop();
void* tmp47 = rs->top()->getMethodCallPosLabel();
goto *tmp47;
}
l5:
return 0;
}
