#include "src/code-generator/activation-record.hpp"
#include "src/code-generator/value.hpp"
using std::cout;
using std::endl;
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord();
{
Value* _tmp0 = new IntValue(1);
rs->top()->insertVar("a",_tmp0);
}
{
Value* _tmp0 = new IntValue(1);
Value* _tmp1 = - *_tmp0;
Value* _a = rs->top()->lookupVarVal("a");
Value* _tmp2 = *_tmp1 + *_a;
rs->top()->insertVar("b",_tmp2);
}
{
Value* _a = rs->top()->lookupVarVal("a");
Value* _b = rs->top()->lookupVarVal("b");
Value* _tmp0 = *_a < *_b;
rs->top()->insertVar("c",_tmp0);
}
rs->pop();
return 0;
}
