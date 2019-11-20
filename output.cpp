#include "src/code-generator/activation-record.hpp"
#include "src/code-generator/value.hpp"
using std::cout;
using std::endl;
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr);
{
Value* tmp0 = new StringValue("eu so feio? ");
Value* tmp1 = new BoolValue(true);
Value* tmp2 = new StringValue( tmp1->toString());
Value* tmp3 = *tmp0 + *tmp2;
cout << tmp3->toString() << endl;
}
rs->pop();
return 0;
}
