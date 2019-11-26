#include "activation-record.hpp"
#include "value.hpp"
using std::cout;
using std::endl;
struct Main : ClassValue {
Main() : ClassValue( "Main"){
initFields();
}
void initFields(){

}
static Value* newMain(){
Main* c = new Main();
c->initFields();
return c;
}
};
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
rs->createRecord(nullptr,nullptr,&&l2,nullptr);
l0: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject());
{
Value* tmp0 = new Test();
rs->top()->insertVar("t",tmp0);
}
{
Value* _t = rs->top()->lookupStatic("t");
if(dynamic_cast<NullValue*>(_t) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
{
rs->createRecord(nullptr,nullptr,&&l3,dynamic_cast<ClassValue*>(_t));
Value* tmp0 = new StringValue("Junio");
rs->top()->insertVar("str",tmp0);
goto l1;
}
}
l3:
rs->pop();
void* tmp0 = rs->top()->getReturnLabel();
rs->pop();
goto *tmp0;
}
l1: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject());
{
Value* tmp0 = new StringValue("Meu nome é");
Value* _str = rs->top()->lookupStatic("str");
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
