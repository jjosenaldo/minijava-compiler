#include "types.h"
#include <stdio.h>

void main(){
    Type t1 = MkTypeVoid();
    Type t2 = MkTypeInt();
    Type t3 = MkTypeInt();
    TypeList list = MkTypeList();
    addTypeToList(&list, &t1);
    addTypeToList(&list, &t2);
    //addTypeToList(&list, &t3);
    printTypeList(&list);
    
}