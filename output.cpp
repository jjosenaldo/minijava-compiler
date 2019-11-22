#include "src/code-generator/activation-record.hpp"
#include "src/code-generator/value.hpp"
using std::cout;
using std::endl;
struct Main : ClassValue {
};
struct Mammal : ClassValue {
int teats;
};
int main(){
RecordStack* rs = new RecordStack();
rs->createRecord(nullptr,nullptr);
rs->pop();
return 0;
}
