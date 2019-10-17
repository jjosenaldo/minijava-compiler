#include "type/type.hpp"
#include <iostream>


using std::cout;
using std::endl;

int main(){
    Type* t1 = MkTypeInt();
    Type* t2 = MkTypeBoolean();
    Type* t3 = MkTypeClass("Cat");

    printType(t1); cout << endl;
    printType(t2); cout << endl;
    printType(t3); cout << endl;

    return 0;
}