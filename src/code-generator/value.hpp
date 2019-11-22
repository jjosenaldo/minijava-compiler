#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>
using std::string;

enum EnumValue{
    EV_IntValue,
    EV_StringValue,
    EV_BoolValue,
    EV_ArrayValue
};

class BoolValue;

/*
	Suggested solution:

	template<typename T>
	class Value {
		...

		vitual T getValue() = 0;
	}

	class IntValue : public Value<int> {
		...

		int getValue() { return value; }
	}
*/

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

	friend IntValue* operator-(const IntValue& v1, const IntValue& v2);
	friend IntValue* operator-(const IntValue& v1);
	friend IntValue* operator*(const IntValue& v1, const IntValue& v2);
	friend IntValue* operator/(const IntValue& v1, const IntValue& v2);
	friend IntValue* operator%(const IntValue& v1, const IntValue& v2);

	template<typename Val>
	friend Val* operator+(const Val& v1, const Val& v2);
	template<typename Val>
	friend Val* operator<(const Val& v1, const Val& v2);
	template<typename Val>
	friend Val* operator<=(const Val& v1, const Val& v2);
	template<typename Val>
	friend Val* operator>(const Val& v1, const Val& v2);
	template<typename Val>
	friend Val* operator>=(const Val& v1, const Val& v2);

	template<typename Val>
	friend BoolValue* operator==(const Val& v1, const Val& v2);
	template<typename Val>
	friend BoolValue* operator!=(const Val& v1, const Val& v2);
};

class BoolValue : public Value {
private:
	bool value;
public:
	BoolValue();
	BoolValue(bool v);
	bool getBool() const;

	string toString();
	string getClassName();

	friend BoolValue* operator!(const BoolValue& v1);
	friend BoolValue* operator||(const BoolValue& v1, const BoolValue& v2);
	friend BoolValue* operator&&(const BoolValue& v1, const BoolValue& v2);

	template<typename Val>
	friend BoolValue* operator==(const Val& v1, const Val& v2);
	template<typename Val>
	friend BoolValue* operator!=(const Val& v1, const Val& v2);
};

class StringValue : public Value {
private:
	string value;
public:
	StringValue();
	StringValue(string v);
	string getString() const;

	string toString();
	string getClassName();

	template<typename Val>
	friend Val* operator+(const Val& v1, const Val& v2);
	template<typename Val>
	friend Val* operator<(const Val& v1, const Val& v2);
	template<typename Val>
	friend Val* operator<=(const Val& v1, const Val& v2);
	template<typename Val>
	friend Val* operator>(const Val& v1, const Val& v2);
	template<typename Val>
	friend Val* operator>=(const Val& v1, const Val& v2);

	template<typename Val>
	friend BoolValue* operator==(const Val& v1, const Val& v2);
	template<typename Val>
	friend BoolValue* operator!=(const Val& v1, const Val& v2);
};

// class ClassValue : public Value {
// private:
// 	map<string, Value*> fields;
// 	string classname;
// public:
// 	ClassValue();
// 	~ClassValue();
// };

class ArrayValue : public Value{
private:
	Value** value;
	int n;
	ArrayValue(int* dims, int i, int n, EnumValue ev);

public:
	ArrayValue(Value** v, int n);
	ArrayValue(int* dims, int n, EnumValue ev);
	Value** getArray() const;

	string toString();
	string getClassName();

	friend class Value;

	template<typename Val>
	friend BoolValue* operator==(const Val& v1, const Val& v2);
	template<typename Val>
	friend BoolValue* operator!=(const Val& v1, const Val& v2);
};

#endif