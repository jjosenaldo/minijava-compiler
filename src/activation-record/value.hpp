#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>

using std::string;

class Value
{
public:
	Value() {}
	~Value() {}
	virtual int getValue(){return 0;}
	virtual string toString() = 0;
};

class IntValue : public Value {
private:
	int value;
public:
	IntValue(int v);
	int getValue();
	string toString();
};



#endif