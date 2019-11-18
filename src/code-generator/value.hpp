#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>

using std::string;
class BoolValue;

class Value
{
public:
	Value() {}
	~Value() {}
	virtual string getClassName() = 0;
	virtual string toString() = 0;

	virtual int getInt() const {return 0;}
	virtual bool getBool() const {return false;}
};

class IntValue : public Value {
private:
	int value;
public:
	IntValue(int v);
	int getInt() const;
	
	string toString();
	string getClassName();

	friend BoolValue* operator<(const Value& v1, const Value& v2);
	friend IntValue* operator+(const Value& v1, const Value& v2);
};

class BoolValue : public Value{
private:
	bool value;
public:
	BoolValue(bool v);
	bool getBool() const;

	string toString();
	string getClassName();
};

IntValue* operator+(const Value& v1, const Value& v2);
BoolValue* operator<(const Value& v1, const Value& v2);

#endif
