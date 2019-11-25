#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

enum EnumValue{
    EV_IntValue,
    EV_StringValue,
    EV_BoolValue,
    EV_ArrayValue,
	EV_ClassValue
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
protected:
	string className;

public:
	~Value() {}
	virtual string toString() {return "";}
	virtual int getInt() const {return 0;}
	virtual bool getBool() const {return false;}
	string getClassName(){return className;}

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

	static Value* newInt(){return new IntValue();}

	friend Value* operator-(const Value& v1, const Value& v2);
	friend Value* operator-(const Value& v1);
	friend Value* operator*(const Value& v1, const Value& v2);
	friend Value* operator/(const Value& v1, const Value& v2);
	friend Value* operator%(const Value& v1, const Value& v2);

	friend Value* operator+(const Value& v1, const Value& v2);
	friend Value* operator<(const Value& v1, const Value& v2);
	friend Value* operator<=(const Value& v1, const Value& v2);
	friend Value* operator>(const Value& v1, const Value& v2);
	friend Value* operator>=(const Value& v1, const Value& v2);

	friend Value* operator==(const Value& v1, const Value& v2);
	friend Value* operator!=(const Value& v1, const Value& v2);
};

class BoolValue : public Value {
private:
	bool value;
public:
	BoolValue();
	BoolValue(bool v);
	bool getBool() const;

	string toString();

	static Value* newBool(){return new BoolValue();}

	friend Value* operator!(const Value& v1);
	friend Value* operator||(const BoolValue& v1, const BoolValue& v2);
	friend Value* operator&&(const BoolValue& v1, const BoolValue& v2);

	friend Value* operator==(const Value& v1, const Value& v2);
	friend Value* operator!=(const Value& v1, const Value& v2);
};

class StringValue : public Value {
private:
	string value;
public:
	StringValue();
	StringValue(string v);
	string getString() const;

	string toString();

	static Value* newInt(){return new StringValue();}

	friend Value* operator+(const Value& v1, const Value& v2);
	friend Value* operator<(const Value& v1, const Value& v2);
	friend Value* operator<=(const Value& v1, const Value& v2);
	friend Value* operator>(const Value& v1, const Value& v2);
	friend Value* operator>=(const Value& v1, const Value& v2);

	friend Value* operator==(const Value& v1, const Value& v2);
	friend Value* operator!=(const Value& v1, const Value& v2);
};

class ClassValue : public Value {
protected:
	string actualClassName;
	string apparentClassName;
	unordered_map<string, Value*>* fields;
public:
	ClassValue(string className);

	Value* get(string field);
	void set(string field, Value* value);

	virtual void initFields() {}

	friend Value* operator==(const Value& v1, const Value& v2);
	friend Value* operator!=(const Value& v1, const Value& v2);
};

class ArrayValue : public Value{
private:
	Value** value;
	int n;
	ArrayValue(int* dims, int i, int n, Value* ctor() = nullptr);

public:
	ArrayValue(Value** v, int n);
	ArrayValue(int* dims, int n, Value* ctor() = nullptr);
	Value** getArray() const;

	string toString();

	friend class Value;

	friend Value* operator==(const Value& v1, const Value& v2);
	friend Value* operator!=(const Value& v1, const Value& v2);
};

class NullValue : public Value{
public:
	friend Value* operator==(const Value& v1, const Value& v2);
	friend Value* operator!=(const Value& v1, const Value& v2);

	string toString(){return "null";}
};

// int
Value* operator-(const Value& v1, const Value& v2);
Value* operator-(const Value& v1);
Value* operator*(const Value& v1, const Value& v2);
Value* operator/(const Value& v1, const Value& v2);
Value* operator%(const Value& v1, const Value& v2);

// String and int
Value* operator+(const Value& v1, const Value& v2);
Value* operator<(const Value& v1, const Value& v2);
Value* operator<=(const Value& v1, const Value& v2);
Value* operator>(const Value& v1, const Value& v2);
Value* operator>=(const Value& v1, const Value& v2);
// bool
Value* operator!(const Value& v1);
Value* operator||(const BoolValue& v1, const BoolValue& v2);
Value* operator&&(const BoolValue& v1, const BoolValue& v2);

// all
Value* operator==(const Value& v1, const Value& v2);
Value* operator!=(const Value& v1, const Value& v2);

#endif