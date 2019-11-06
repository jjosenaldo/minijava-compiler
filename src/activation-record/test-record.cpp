#include <iostream>
#include "activation-record.hpp"

#define LOOKUP(x) rs->top()->lookupVarVal(x)

int main(int argc, char const *argv[]) {
	RecordStack *rs = new RecordStack;

	rs->createRecord();
	rs->top()->insertVar("args", nullptr);
	rs->top()->insertVar("a", 1);

	rs->createRecord();
	rs->top()->insertVar("a", 2);
	rs->top()->insertVar("b", LOOKUP("a"));
	rs->pop();

	rs->top()->insertVar("b", LOOKUP("a")); 
	rs->pop();

	return 0;
}