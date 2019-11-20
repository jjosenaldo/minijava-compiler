#include "src/code-generator/activation-record.hpp"
#include "src/code-generator/value.hpp"
using std::cout;
using std::endl;
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr);
{
rs->top()->insertVar("a",ERROR);
}
rs->pop();
return 0;
}
