#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>

using std::string;
class BoolValue;

class Value
{
public:
	~Value() {}
	virtual string getClassName() = 0;
	virtual string toString() = 0;
	virtual int getInt() const {return 0;}
	virtual bool getBool() const {return false;}

	Value* operator[](const int i);
};



class IntValue : public Value {
private:
	int value;
public:
	IntValue();
	IntValue(int v);
	int getInt() const;
	
	string toString();
	string getClassName();

	friend Value* operator<(const Value& v1, const Value& v2);
	friend Value* operator+(const Value& v1, const Value& v2);
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

class StringValue : public Value{
private:
	string value;
public:
	StringValue(string v);
	string getString() const;

	string toString();
	string getClassName();
};

class ArrayValue : public Value{
private:
	Value** value;
	int n;
	ArrayValue(int* dims, int i, int n, string ctor);

public:
	ArrayValue(Value** v, int n);
	ArrayValue(int* dims, int n, string ctor);
	Value** getArray() const;

	string toString();
	string getClassName(); 

	friend class Value;
};

// int operators
Value* operator-(const Value& v1, const Value& v2);
Value* operator-(const Value& v1);
Value* operator*(const Value& v1, const Value& v2);
Value* operator/(const Value& v1, const Value& v2);
Value* operator%(const Value& v1, const Value& v2);

// int and String operators
Value* operator+(const Value& v1, const Value& v2);
Value* operator<(const Value& v1, const Value& v2);
Value* operator<=(const Value& v1, const Value& v2);
Value* operator>(const Value& v1, const Value& v2);
Value* operator>=(const Value& v1, const Value& v2);

// boolean operators
Value* operator!(const Value& v1);
Value* operator||(const Value& v1, const Value& v2);
Value* operator&&(const Value& v1, const Value& v2);

// all types operators
Value* operator==(const Value& v1, const Value& v2);
Value* operator!=(const Value& v1, const Value& v2);

#endif