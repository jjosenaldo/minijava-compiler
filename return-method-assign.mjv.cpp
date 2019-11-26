#include "activation-record.hpp"
#include "value.hpp"
using std::cout;
using std::endl;
struct Animal : ClassValue {
Animal() : ClassValue( "Animal"){
initFields();
}
void initFields(){

}
static Value* newAnimal(){
Animal* c = new Animal();
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
Value* tmp0 = new Animal();
rs->top()->insertVar("animal",tmp0);
}
{
Value* tmp1 = rs->top()->lookupStatic("animal");
{
if(dynamic_cast<NullValue*>(tmp1) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l4 = new Value*[1];
Value* tmp3 = new StringValue("oi");
l4[0] = tmp3;
{
rs->createRecord(nullptr,nullptr,&&l3,dynamic_cast<ClassValue*>(tmp1),nullptr);
rs->top()->insertVar("var",l4[0]);
goto l1;
}
}
l3:
Value* tmp2 = rs->top()->getReturnValue();
rs->pop();
rs->top()->insertVar("a",tmp2);
}
{
Value* tmp4 = rs->top()->lookupStatic("a");
Value* tmp5 = new IntValue(1);
Value* tmp6 = *tmp4 + *tmp5;
rs->top()->insertVar("b",tmp6);
}
{
Value* tmp7 = rs->top()->lookupStatic("b");
Value* tmp8 = new StringValue( tmp7->toString());
cout << tmp8->toString();
}
rs->pop();
void* tmp9 = rs->top()->getMethodCallPosLabel();
goto *tmp9;
}
l1: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp10 = new IntValue(2);
rs->top()->insertVar("x",tmp10);
}
{
Value* tmp13 = rs->top()->lookupStatic("x");
Value* tmp14 = new IntValue(1);
Value* tmp15 = *tmp13 + *tmp14;
void* tmp11 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp15); 
goto *tmp11;
}
rs->pop();
void* tmp16 = rs->top()->getMethodCallPosLabel();
goto *tmp16;
}
l2:
return 0;
}
