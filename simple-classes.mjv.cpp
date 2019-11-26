#include "activation-record.hpp"
#include "value.hpp"
using std::cout;
using std::endl;
struct Mammal : ClassValue {
Mammal() : ClassValue( "Mammal"){
initFields();
}
void initFields(){
fields->emplace("teats", new IntValue);

}
static Value* newMammal(){
Mammal* c = new Mammal();
c->initFields();
return c;
}
};
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr,&&l1,nullptr,nullptr);
l0: {
rs->createRecord(nullptr,nullptr,nullptr,rs->top()->getCurrentObject(),nullptr);
rs->pop();
void* tmp0 = rs->top()->getMethodCallPosLabel();
goto *tmp0;
}
l1:
return 0;
}
