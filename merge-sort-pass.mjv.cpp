#include "activation-record.hpp"
#include "value.hpp"
using std::cout;
using std::endl;
struct MergeSort : ClassValue {
MergeSort() : ClassValue( "MergeSort"){
initFields();
}
void initFields(){

}
static Value* newMergeSort(){
MergeSort* c = new MergeSort();
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
Value* tmp0 = new MergeSort();
rs->top()->insertVar("sorter",tmp0);
}
{
Value** tmp1 = new Value*[8];
Value* tmp3 = new IntValue(1);
tmp1[0] = tmp3;
Value* tmp4 = new IntValue(5);
tmp1[1] = tmp4;
Value* tmp5 = new IntValue(3);
tmp1[2] = tmp5;
Value* tmp6 = new IntValue(6);
tmp1[3] = tmp6;
Value* tmp7 = new IntValue(3);
tmp1[4] = tmp7;
Value* tmp8 = new IntValue(845);
tmp1[5] = tmp8;
Value* tmp9 = new IntValue(23);
tmp1[6] = tmp9;
Value* tmp10 = new IntValue(56);
tmp1[7] = tmp10;
Value* tmp2 = new ArrayValue(tmp1,8);
rs->top()->insertVar("v",tmp2);
}
Value* tmp11 = rs->top()->lookupStatic("sorter");
{
if(dynamic_cast<NullValue*>(tmp11) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l6 = new Value*[1];
Value* tmp13 = rs->top()->lookupStatic("v");
l6[0] = tmp13;
{
rs->createRecord(nullptr,nullptr,&&l5,dynamic_cast<ClassValue*>(tmp11),nullptr);
rs->top()->insertVar("arr",l6[0]);
goto l1;
}
}
l5:
Value* tmp12 = rs->top()->getReturnValue();
rs->pop();
{
Value* tmp14 = new IntValue(0);
rs->top()->insertVar("i",tmp14);
}
rs->createRecord(&&l7,&&l8,nullptr,rs->top()->getCurrentObject(),nullptr);
{
l7:
Value* tmp15 = rs->top()->lookupStatic("i");
Value* tmp16 = rs->top()->lookupStatic("v");
Value* tmp17 = new IntValue(dynamic_cast<ArrayValue*>(tmp16)->getN());
Value* tmp18 = *tmp15 < *tmp17;
if(!tmp18->getBool()) goto l8;
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp19 = rs->top()->lookupStatic("v");
Value* tmp20 = rs->top()->lookupStatic("i");
Value* tmp21 = (*tmp19)[tmp20->getInt()];
Value* tmp22 = new StringValue( tmp21->toString());
cout << tmp22->toString();
}
{
Value* tmp23 = new StringValue("\n");
cout << tmp23->toString();
}
{
Value* tmp24 = rs->top()->lookupStatic("i");
Value* tmp25 = new IntValue(1);
Value* tmp26 = *tmp24 + *tmp25;
rs->top()->updateStatic("i",tmp26);
}
rs->pop();
goto l7;
}
l8:;
rs->pop();
rs->pop();
void* tmp27 = rs->top()->getMethodCallPosLabel();
goto *tmp27;
}
l1: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
Value* tmp28 = rs->top()->getCurrentObject();
{
if(dynamic_cast<NullValue*>(tmp28) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l10 = new Value*[2];
Value* tmp30 = rs->top()->lookupStatic("arr");
l10[0] = tmp30;
Value* tmp31 = rs->top()->lookupStatic("arr");
Value* tmp32 = new IntValue(dynamic_cast<ArrayValue*>(tmp31)->getN());
l10[1] = tmp32;
{
rs->createRecord(nullptr,nullptr,&&l9,dynamic_cast<ClassValue*>(tmp28),nullptr);
rs->top()->insertVar("a",l10[0]);
rs->top()->insertVar("n",l10[1]);
goto l3;
}
}
l9:
Value* tmp29 = rs->top()->getReturnValue();
rs->pop();
rs->pop();
void* tmp33 = rs->top()->getMethodCallPosLabel();
goto *tmp33;
}
l2: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp34 = new IntValue(0);
rs->top()->insertVar("i",tmp34);
}
{
Value* tmp35 = new IntValue(0);
rs->top()->insertVar("j",tmp35);
}
{
Value* tmp36 = new IntValue(0);
rs->top()->insertVar("k",tmp36);
}
rs->createRecord(&&l11,&&l12,nullptr,rs->top()->getCurrentObject(),nullptr);
{
l11:
Value* tmp37 = rs->top()->lookupStatic("i");
Value* tmp38 = rs->top()->lookupStatic("left");
Value* tmp39 = *tmp37 < *tmp38;
Value* tmp40 = rs->top()->lookupStatic("j");
Value* tmp41 = rs->top()->lookupStatic("right");
Value* tmp42 = *tmp40 < *tmp41;
Value* tmp43 = *tmp39 && *tmp42;
if(!tmp43->getBool()) goto l12;
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp44 = rs->top()->lookupStatic("l");
Value* tmp45 = rs->top()->lookupStatic("i");
Value* tmp46 = (*tmp44)[tmp45->getInt()];
Value* tmp47 = rs->top()->lookupStatic("r");
Value* tmp48 = rs->top()->lookupStatic("j");
Value* tmp49 = (*tmp47)[tmp48->getInt()];
Value* tmp50 = *tmp46 <= *tmp49;
if(!tmp50->getBool()) goto l13;
{ 
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp51 = rs->top()->lookupStatic("l");
Value* tmp52 = rs->top()->lookupStatic("i");
Value* tmp53 = (*tmp51)[tmp52->getInt()];
int* tmp54 = new int[1];
Value* tmp55 = rs->top()->lookupStatic("k");
tmp54[0] = tmp55->getInt();
Value* tmp57 = rs->top()->lookupStatic("a");
ArrayValue* tmp56 = dynamic_cast<ArrayValue*>(tmp57);
tmp56->setAt(tmp54,1,tmp53);
}
{
Value* tmp58 = rs->top()->lookupStatic("i");
Value* tmp59 = new IntValue(1);
Value* tmp60 = *tmp58 + *tmp59;
rs->top()->updateStatic("i",tmp60);
}
rs->pop();
} 
goto l14;
{ 
l13:
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp61 = rs->top()->lookupStatic("r");
Value* tmp62 = rs->top()->lookupStatic("j");
Value* tmp63 = (*tmp61)[tmp62->getInt()];
int* tmp64 = new int[1];
Value* tmp65 = rs->top()->lookupStatic("k");
tmp64[0] = tmp65->getInt();
Value* tmp67 = rs->top()->lookupStatic("a");
ArrayValue* tmp66 = dynamic_cast<ArrayValue*>(tmp67);
tmp66->setAt(tmp64,1,tmp63);
}
{
Value* tmp68 = rs->top()->lookupStatic("j");
Value* tmp69 = new IntValue(1);
Value* tmp70 = *tmp68 + *tmp69;
rs->top()->updateStatic("j",tmp70);
}
rs->pop();
} 
} 
l14:;
{
Value* tmp71 = rs->top()->lookupStatic("k");
Value* tmp72 = new IntValue(1);
Value* tmp73 = *tmp71 + *tmp72;
rs->top()->updateStatic("k",tmp73);
}
rs->pop();
goto l11;
}
l12:;
rs->pop();
rs->createRecord(&&l15,&&l16,nullptr,rs->top()->getCurrentObject(),nullptr);
{
l15:
Value* tmp74 = rs->top()->lookupStatic("i");
Value* tmp75 = rs->top()->lookupStatic("left");
Value* tmp76 = *tmp74 < *tmp75;
if(!tmp76->getBool()) goto l16;
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp77 = rs->top()->lookupStatic("l");
Value* tmp78 = rs->top()->lookupStatic("i");
Value* tmp79 = (*tmp77)[tmp78->getInt()];
int* tmp80 = new int[1];
Value* tmp81 = rs->top()->lookupStatic("k");
tmp80[0] = tmp81->getInt();
Value* tmp83 = rs->top()->lookupStatic("a");
ArrayValue* tmp82 = dynamic_cast<ArrayValue*>(tmp83);
tmp82->setAt(tmp80,1,tmp79);
}
{
Value* tmp84 = rs->top()->lookupStatic("k");
Value* tmp85 = new IntValue(1);
Value* tmp86 = *tmp84 + *tmp85;
rs->top()->updateStatic("k",tmp86);
}
{
Value* tmp87 = rs->top()->lookupStatic("i");
Value* tmp88 = new IntValue(1);
Value* tmp89 = *tmp87 + *tmp88;
rs->top()->updateStatic("i",tmp89);
}
rs->pop();
goto l15;
}
l16:;
rs->pop();
rs->createRecord(&&l17,&&l18,nullptr,rs->top()->getCurrentObject(),nullptr);
{
l17:
Value* tmp90 = rs->top()->lookupStatic("j");
Value* tmp91 = rs->top()->lookupStatic("right");
Value* tmp92 = *tmp90 < *tmp91;
if(!tmp92->getBool()) goto l18;
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp93 = rs->top()->lookupStatic("r");
Value* tmp94 = rs->top()->lookupStatic("j");
Value* tmp95 = (*tmp93)[tmp94->getInt()];
int* tmp96 = new int[1];
Value* tmp97 = rs->top()->lookupStatic("k");
tmp96[0] = tmp97->getInt();
Value* tmp99 = rs->top()->lookupStatic("a");
ArrayValue* tmp98 = dynamic_cast<ArrayValue*>(tmp99);
tmp98->setAt(tmp96,1,tmp95);
}
{
Value* tmp100 = rs->top()->lookupStatic("k");
Value* tmp101 = new IntValue(1);
Value* tmp102 = *tmp100 + *tmp101;
rs->top()->updateStatic("k",tmp102);
}
{
Value* tmp103 = rs->top()->lookupStatic("j");
Value* tmp104 = new IntValue(1);
Value* tmp105 = *tmp103 + *tmp104;
rs->top()->updateStatic("j",tmp105);
}
rs->pop();
goto l17;
}
l18:;
rs->pop();
rs->pop();
void* tmp106 = rs->top()->getMethodCallPosLabel();
goto *tmp106;
}
l3: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp107 = rs->top()->lookupStatic("n");
Value* tmp108 = new IntValue(2);
Value* tmp109 = *tmp107 < *tmp108;
if(!tmp109->getBool()) goto l19;
{ 
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
void* tmp110 = rs->searchMethodCallLabel(); 
goto *tmp110;
}
rs->pop();
} 
} 
l19:;
{
Value* tmp112 = rs->top()->lookupStatic("n");
Value* tmp113 = new IntValue(2);
Value* tmp114 = *tmp112 / *tmp113;
rs->top()->insertVar("mid",tmp114);
}
{
int* tmp115 = new int[1];
Value* tmp116 = rs->top()->lookupStatic("mid");
tmp115[0] = tmp116->getInt();
Value* tmp117 = new ArrayValue(tmp115,1,IntValue::newInt);
rs->top()->insertVar("l",tmp117);
}
{
int* tmp118 = new int[1];
Value* tmp119 = rs->top()->lookupStatic("n");
Value* tmp120 = rs->top()->lookupStatic("mid");
Value* tmp121 = *tmp119 - *tmp120;
tmp118[0] = tmp121->getInt();
Value* tmp122 = new ArrayValue(tmp118,1,IntValue::newInt);
rs->top()->insertVar("r",tmp122);
}
{
Value* tmp123 = new IntValue(0);
rs->top()->insertVar("i",tmp123);
}
rs->createRecord(&&l20,&&l21,nullptr,rs->top()->getCurrentObject(),nullptr);
{
l20:
Value* tmp124 = rs->top()->lookupStatic("i");
Value* tmp125 = rs->top()->lookupStatic("mid");
Value* tmp126 = *tmp124 < *tmp125;
if(!tmp126->getBool()) goto l21;
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp127 = rs->top()->lookupStatic("a");
Value* tmp128 = rs->top()->lookupStatic("i");
Value* tmp129 = (*tmp127)[tmp128->getInt()];
int* tmp130 = new int[1];
Value* tmp131 = rs->top()->lookupStatic("i");
tmp130[0] = tmp131->getInt();
Value* tmp133 = rs->top()->lookupStatic("l");
ArrayValue* tmp132 = dynamic_cast<ArrayValue*>(tmp133);
tmp132->setAt(tmp130,1,tmp129);
}
{
Value* tmp134 = rs->top()->lookupStatic("i");
Value* tmp135 = new IntValue(1);
Value* tmp136 = *tmp134 + *tmp135;
rs->top()->updateStatic("i",tmp136);
}
rs->pop();
goto l20;
}
l21:;
rs->pop();
rs->createRecord(&&l22,&&l23,nullptr,rs->top()->getCurrentObject(),nullptr);
{
l22:
Value* tmp137 = rs->top()->lookupStatic("i");
Value* tmp138 = rs->top()->lookupStatic("n");
Value* tmp139 = *tmp137 < *tmp138;
if(!tmp139->getBool()) goto l23;
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
{
Value* tmp140 = rs->top()->lookupStatic("a");
Value* tmp141 = rs->top()->lookupStatic("i");
Value* tmp142 = (*tmp140)[tmp141->getInt()];
int* tmp143 = new int[1];
Value* tmp144 = rs->top()->lookupStatic("i");
Value* tmp145 = rs->top()->lookupStatic("mid");
Value* tmp146 = *tmp144 - *tmp145;
tmp143[0] = tmp146->getInt();
Value* tmp148 = rs->top()->lookupStatic("r");
ArrayValue* tmp147 = dynamic_cast<ArrayValue*>(tmp148);
tmp147->setAt(tmp143,1,tmp142);
}
{
Value* tmp149 = rs->top()->lookupStatic("i");
Value* tmp150 = new IntValue(1);
Value* tmp151 = *tmp149 + *tmp150;
rs->top()->updateStatic("i",tmp151);
}
rs->pop();
goto l22;
}
l23:;
rs->pop();
Value* tmp152 = rs->top()->getCurrentObject();
{
if(dynamic_cast<NullValue*>(tmp152) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l25 = new Value*[2];
Value* tmp154 = rs->top()->lookupStatic("l");
l25[0] = tmp154;
Value* tmp155 = rs->top()->lookupStatic("mid");
l25[1] = tmp155;
{
rs->createRecord(nullptr,nullptr,&&l24,dynamic_cast<ClassValue*>(tmp152),nullptr);
rs->top()->insertVar("a",l25[0]);
rs->top()->insertVar("n",l25[1]);
goto l3;
}
}
l24:
Value* tmp153 = rs->top()->getReturnValue();
rs->pop();
Value* tmp156 = rs->top()->getCurrentObject();
{
if(dynamic_cast<NullValue*>(tmp156) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l27 = new Value*[2];
Value* tmp158 = rs->top()->lookupStatic("r");
l27[0] = tmp158;
Value* tmp159 = rs->top()->lookupStatic("n");
Value* tmp160 = rs->top()->lookupStatic("mid");
Value* tmp161 = *tmp159 - *tmp160;
l27[1] = tmp161;
{
rs->createRecord(nullptr,nullptr,&&l26,dynamic_cast<ClassValue*>(tmp156),nullptr);
rs->top()->insertVar("a",l27[0]);
rs->top()->insertVar("n",l27[1]);
goto l3;
}
}
l26:
Value* tmp157 = rs->top()->getReturnValue();
rs->pop();
Value* tmp162 = rs->top()->getCurrentObject();
{
if(dynamic_cast<NullValue*>(tmp162) != nullptr){
std::cerr << "ERROR: you cannot call a method on a null object!\n";
exit(0);
}
Value** l29 = new Value*[5];
Value* tmp164 = rs->top()->lookupStatic("a");
l29[0] = tmp164;
Value* tmp165 = rs->top()->lookupStatic("l");
l29[1] = tmp165;
Value* tmp166 = rs->top()->lookupStatic("r");
l29[2] = tmp166;
Value* tmp167 = rs->top()->lookupStatic("mid");
l29[3] = tmp167;
Value* tmp168 = rs->top()->lookupStatic("n");
Value* tmp169 = rs->top()->lookupStatic("mid");
Value* tmp170 = *tmp168 - *tmp169;
l29[4] = tmp170;
{
rs->createRecord(nullptr,nullptr,&&l28,dynamic_cast<ClassValue*>(tmp162),nullptr);
rs->top()->insertVar("a",l29[0]);
rs->top()->insertVar("l",l29[1]);
rs->top()->insertVar("r",l29[2]);
rs->top()->insertVar("left",l29[3]);
rs->top()->insertVar("right",l29[4]);
goto l2;
}
}
l28:
Value* tmp163 = rs->top()->getReturnValue();
rs->pop();
rs->pop();
void* tmp171 = rs->top()->getMethodCallPosLabel();
goto *tmp171;
}
l4:
return 0;
}
