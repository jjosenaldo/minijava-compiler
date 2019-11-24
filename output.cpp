#include "src/code-generator/activation-record.hpp"
#include "src/code-generator/value.hpp"
using std::cout;
using std::endl;
struct Main : ClassValue {
};
struct Cat : ClassValue {
};
int main(){
RecordStack* rs = new RecordStack();
