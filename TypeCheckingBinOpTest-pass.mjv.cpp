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
rs->createRecord(nullptr,nullptr,&&l4,nullptr,nullptr);
l0: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp0 = new IntValue(1);
rs->top()->insertVar("int_a",tmp0);
}
{
Value* tmp1 = new IntValue(1);
rs->top()->insertVar("int_b",tmp1);
}
{
Value* tmp2 = new BoolValue(true);
rs->top()->insertVar("bool_a",tmp2);
}
{
Value* tmp3 = new BoolValue(true);
rs->top()->insertVar("bool_b",tmp3);
}
{
Value* tmp4 = rs->top()->lookupStatic("int_a");
Value* tmp5 = rs->top()->lookupStatic("int_b");
Value* tmp6 = *tmp4 + *tmp5;
rs->top()->insertVar("int_c",tmp6);
}
{
Value* tmp7 = rs->top()->lookupStatic("int_a");
Value* tmp8 = rs->top()->lookupStatic("int_b");
Value* tmp9 = *tmp7 - *tmp8;
rs->top()->updateStatic("int_c",tmp9);
}
{
Value* tmp10 = new Cat();
rs->top()->insertVar("a",tmp10);
}
{
Value* tmp11 = rs->top()->lookupStatic("a");
rs->top()->insertVar("b",tmp11);
}
{
Value* tmp12 = new Animal();
rs->top()->insertVar("b1",tmp12);
}
{
Value** tmp13 = new Value*[3];
Value** tmp15 = new Value*[2];
Value* tmp17 = new Cat();
tmp15[0] = tmp17;
Value* tmp18 = new Animal();
tmp15[1] = tmp18;
Value* tmp16 = new ArrayValue(tmp15,2);
tmp13[0] = tmp16;
Value* tmp19 = new NullValue()
;tmp13[1] = tmp19;
Value** tmp20 = new Value*[1];
Value* tmp22 = new NullValue()
;tmp20[0] = tmp22;
Value* tmp21 = new ArrayValue(tmp20,1);
tmp13[2] = tmp21;
Value* tmp14 = new ArrayValue(tmp13,3);
rs->top()->insertVar("an",tmp14);
}
{
Value* tmp23 = rs->top()->lookupStatic("an");
Value** tmp24 = new Value*[3];
Value** tmp26 = new Value*[2];
Value* tmp28 = new Cat();
tmp26[0] = tmp28;
Value* tmp29 = new Animal();
tmp26[1] = tmp29;
Value* tmp27 = new ArrayValue(tmp26,2);
tmp24[0] = tmp27;
Value* tmp30 = new NullValue()
;tmp24[1] = tmp30;
Value** tmp31 = new Value*[1];
Value* tmp33 = new NullValue()
;tmp31[0] = tmp33;
Value* tmp32 = new ArrayValue(tmp31,1);
tmp24[2] = tmp32;
Value* tmp25 = new ArrayValue(tmp24,3);
Value* tmp34 = *tmp23 == *tmp25;
rs->top()->insertVar("bool_x",tmp34);
}
{
Value* tmp35 = rs->top()->lookupStatic("int_a");
Value* tmp36 = rs->top()->lookupStatic("int_b");
Value* tmp37 = *tmp35 * *tmp36;
rs->top()->updateStatic("int_c",tmp37);
}
{
Value* tmp38 = rs->top()->lookupStatic("int_a");
Value* tmp39 = rs->top()->lookupStatic("int_b");
Value* tmp40 = *tmp38 / *tmp39;
rs->top()->updateStatic("int_c",tmp40);
}
{
Value* tmp41 = rs->top()->lookupStatic("int_a");
Value* tmp42 = rs->top()->lookupStatic("int_b");
Value* tmp43 = *tmp41 % *tmp42;
rs->top()->updateStatic("int_c",tmp43);
}
{
Value* tmp44 = rs->top()->lookupStatic("bool_a");
Value* tmp45 = rs->top()->lookupStatic("bool_b");
Value* tmp46 = *tmp44 && *tmp45;
rs->top()->insertVar("bool_c",tmp46);
}
{
Value* tmp47 = rs->top()->lookupStatic("bool_a");
Value* tmp48 = rs->top()->lookupStatic("bool_b");
Value* tmp49 = *tmp47 || *tmp48;
rs->top()->updateStatic("bool_c",tmp49);
}
{
Value* tmp50 = rs->top()->lookupStatic("int_a");
Value* tmp51 = rs->top()->lookupStatic("int_b");
Value* tmp52 = *tmp50 == *tmp51;
rs->top()->updateStatic("bool_c",tmp52);
}
{
Value* tmp53 = rs->top()->lookupStatic("int_a");
Value* tmp54 = rs->top()->lookupStatic("int_b");
Value* tmp55 = *tmp53 != *tmp54;
rs->top()->updateStatic("bool_c",tmp55);
}
{
Value* tmp56 = rs->top()->lookupStatic("int_a");
Value* tmp57 = rs->top()->lookupStatic("int_b");
Value* tmp58 = *tmp56 < *tmp57;
rs->top()->updateStatic("bool_c",tmp58);
}
{
Value* tmp59 = rs->top()->lookupStatic("int_a");
Value* tmp60 = rs->top()->lookupStatic("int_b");
Value* tmp61 = *tmp59 <= *tmp60;
rs->top()->updateStatic("bool_c",tmp61);
}
{
Value* tmp62 = rs->top()->lookupStatic("int_a");
Value* tmp63 = rs->top()->lookupStatic("int_b");
Value* tmp64 = *tmp62 > *tmp63;
rs->top()->updateStatic("bool_c",tmp64);
}
{
rs->top()->insertVar("bool_d",new BoolValue);
}
{
Value* tmp65 = rs->top()->lookupStatic("an");
Value* tmp66 = new NullValue()
;Value* tmp67 = *tmp65 == *tmp66;
rs->top()->updateStatic("bool_c",tmp67);
}
{
Value* tmp68 = new NullValue()
;Value* tmp69 = rs->top()->lookupStatic("an");
Value* tmp70 = *tmp68 != *tmp69;
rs->top()->updateStatic("bool_c",tmp70);
}
{
int* tmp71 = new int[2];
Value* tmp72 = new IntValue(4);
tmp71[0] = tmp72->getInt();
Value* tmp73 = new IntValue(3);
tmp71[1] = tmp73->getInt();
Value* tmp74 = new ArrayValue(tmp71,2,IntValue::newInt);
rs->top()->insertVar("arr_a",tmp74);
}
{
int* tmp75 = new int[1];
Value* tmp76 = new IntValue(4);
tmp75[0] = tmp76->getInt();
Value* tmp77 = new ArrayValue(tmp75,1,IntValue::newInt);
rs->top()->insertVar("arr_b",tmp77);
}
rs->pop();
void* tmp78 = rs->top()->getMethodCallPosLabel();
goto *tmp78;
}
l1: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp79 = new StringValue("eat\n");
cout << tmp79->toString();
}
rs->pop();
void* tmp80 = rs->top()->getMethodCallPosLabel();
goto *tmp80;
}
l2: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp81 = new StringValue("meow\n");
cout << tmp81->toString();
}
rs->pop();
void* tmp82 = rs->top()->getMethodCallPosLabel();
goto *tmp82;
}
l3: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp85 = new BoolValue(true);
void* tmp83 = rs->searchMethodCallLabel(); 
rs->top()->setReturnValue(tmp85); 
goto *tmp83;
}
rs->pop();
void* tmp86 = rs->top()->getMethodCallPosLabel();
goto *tmp86;
}
l4:
return 0;
}
