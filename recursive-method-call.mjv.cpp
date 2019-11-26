#include "activation-record.hpp"
#include "value.hpp"
using std::cout;
using std::endl;
struct Cat : ClassValue {
Cat() : ClassValue( "Cat"){
initFields();
}
void initFields(){

}
static Value* newCat(){
Cat* c = new Cat();
c->initFields();
return c;
}
};
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr,&&l3,nullptr,nullptr);
l0: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp0 = new Cat();
rs->top()->insertVar("c",tmp0);
}
{
Value* tmp1 = new StringValue("fibo\n");
cout << tmp1->toString();
}
{
Value* tmp2 = rs->top()->lookupStatic("c");
{
if(dynamic_cast<NullValue*>(tmp2) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l5 = new Value*[1];
Value* tmp4 = new IntValue(15);
l5[0] = tmp4;
{
rs->createRecord(nullptr,nullptr,&&l4,dynamic_cast<ClassValue*>(tmp2),nullptr);
rs->top()->insertVar("n",l5[0]);
goto l2;
}
}
l4:
Value* tmp3 = rs->top()->getReturnValue();
rs->pop();
Value* tmp5 = new StringValue( tmp3->toString());
cout << tmp5->toString();
}
{
Value* tmp6 = new StringValue("\n");
cout << tmp6->toString();
}
rs->pop();
void* tmp7 = rs->top()->getMethodCallPosLabel();
goto *tmp7;
}
l1: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp8 = rs->top()->lookupStatic("steps");
Value* tmp9 = new IntValue(0);
Value* tmp10 = *tmp8 > *tmp9;
if(!tmp10->getBool()) goto l6;
{ 
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp11 = new StringValue("yes, steps: ");
Value* tmp12 = rs->top()->lookupStatic("steps");
Value* tmp13 = new StringValue( tmp12->toString());
Value* tmp14 = *tmp11 + *tmp13;
cout << tmp14->toString();
}
Value* tmp15 = rs->top()->getCurrentObject();
{
if(dynamic_cast<NullValue*>(tmp15) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l8 = new Value*[1];
Value* tmp17 = rs->top()->lookupStatic("steps");
Value* tmp18 = new IntValue(1);
Value* tmp19 = *tmp17 - *tmp18;
l8[0] = tmp19;
{
rs->createRecord(nullptr,nullptr,&&l7,dynamic_cast<ClassValue*>(tmp15),nullptr);
rs->top()->insertVar("steps",l8[0]);
goto l1;
}
}
l7:
Value* tmp16 = rs->top()->getReturnValue();
rs->pop();
rs->pop();
} 
} 
l6:;
rs->pop();
void* tmp20 = rs->top()->getMethodCallPosLabel();
goto *tmp20;
}
l2: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp21 = new StringValue("calling fibo with n = ");
cout << tmp21->toString();
}
{
Value* tmp22 = rs->top()->lookupStatic("n");
Value* tmp23 = new StringValue( tmp22->toString());
cout << tmp23->toString();
}
{
Value* tmp24 = new StringValue("\n");
cout << tmp24->toString();
}
{
Value* tmp25 = rs->top()->lookupStatic("n");
Value* tmp26 = new IntValue(0);
Value* tmp27 = *tmp25 == *tmp26;
Value* tmp28 = rs->top()->lookupStatic("n");
Value* tmp29 = new IntValue(1);
Value* tmp30 = *tmp28 == *tmp29;
Value* tmp31 = *tmp27 || *tmp30;
if(!tmp31->getBool()) goto l9;
{ 
{
Value* tmp34 = new IntValue(1);
void* tmp32 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp34); 
goto *tmp32;
}
} 
} 
l9:;
{
Value* tmp35 = rs->top()->getCurrentObject();
{
if(dynamic_cast<NullValue*>(tmp35) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l11 = new Value*[1];
Value* tmp37 = rs->top()->lookupStatic("n");
Value* tmp38 = new IntValue(1);
Value* tmp39 = *tmp37 - *tmp38;
l11[0] = tmp39;
{
rs->createRecord(nullptr,nullptr,&&l10,dynamic_cast<ClassValue*>(tmp35),nullptr);
rs->top()->insertVar("n",l11[0]);
goto l2;
}
}
l10:
Value* tmp36 = rs->top()->getReturnValue();
rs->pop();
rs->top()->insertVar("tmp1",tmp36);
}
{
Value* tmp40 = rs->top()->getCurrentObject();
{
if(dynamic_cast<NullValue*>(tmp40) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l13 = new Value*[1];
Value* tmp42 = rs->top()->lookupStatic("n");
Value* tmp43 = new IntValue(2);
Value* tmp44 = *tmp42 - *tmp43;
l13[0] = tmp44;
{
rs->createRecord(nullptr,nullptr,&&l12,dynamic_cast<ClassValue*>(tmp40),nullptr);
rs->top()->insertVar("n",l13[0]);
goto l2;
}
}
l12:
Value* tmp41 = rs->top()->getReturnValue();
rs->pop();
rs->top()->insertVar("tmp2",tmp41);
}
{
Value* tmp47 = rs->top()->lookupStatic("tmp1");
Value* tmp48 = rs->top()->lookupStatic("tmp2");
Value* tmp49 = *tmp47 + *tmp48;
void* tmp45 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp49); 
goto *tmp45;
}
rs->pop();
void* tmp50 = rs->top()->getMethodCallPosLabel();
goto *tmp50;
}
l3:
return 0;
}
