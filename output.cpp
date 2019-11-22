#include "src/code-generator/activation-record.hpp"
#include "src/code-generator/value.hpp"
using std::cout;
using std::endl;
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr);
{
int* tmp0 = new int[1];
Value* tmp1 = new IntValue(2);
tmp0[0] = tmp1->getInt();
Value* tmp2 = new ArrayValue(tmp0,1, "a");
rs->top()->insertVar("a",tmp2);
}
{
Value* _a = rs->top()->lookupVarVal("a");
Value* tmp0 = new IntValue(2);
Value* tmp1 = (*_a)[tmp0->getInt()];
Value* tmp2 = new StringValue( tmp1->toString());
cout << tmp2->toString() << endl;
}
rs->pop();
return 0;
}
