#include "src/code-generator/activation-record.hpp"
#include "src/code-generator/value.hpp"
using std::cout;
using std::endl;
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord();
{
Value* _tmp0 = new IntValue(0);
rs->top()->insertVar("a",_tmp0);
}
rs->pop();
return 0;
}
