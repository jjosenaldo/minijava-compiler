#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>

using std::string;

class Value
{
public:
	Value() {}
	~Value() {}
	virtual string toString() = 0;
	virtual Value* operator+(Value &) = 0;
};

class IntValue : public Value {
private:
	int value;
public:
	IntValue(int v);
	int getInt();
	string toString();
	Value* operator+(Value &b);
};

#endif
