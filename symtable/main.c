#include "types.h"
#include <stdio.h>

int main(){
    Type* t1 = MkTypeVoid();
    Type* t2 = MkTypeInt();
    Type* t3 = MkTypeInt();
    TypeList* list = MkTypeList();
    addTypeToList(list, t1);
    addTypeToList(list, t2);
    addTypeToList(list, t3);
    printTypeList(list);

    return 0;
}