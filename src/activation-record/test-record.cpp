#include <iostream>
#include "activation-record.hpp"

int main(int argc, char const *argv[]) {
	RecordStack *rs = new RecordStack;

	rs->createRecord();
	rs->top()->insertVar("args", nullptr);
	rs->top()->insertVar("a", 10);

	rs->createRecord();
	rs->top()->insertVar("b", 0);
	rs->pop();

	rs->top()->insertVar("c", rs->top()->getVarVal("a")); 

	rs->top()->updateVar("a", 2);
	rs->pop();

	return 0;
}