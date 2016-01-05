#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>

#define UNDEFINED_TYPE -1
#define NULL_TYPE 0
#define INT_TYPE 1
#define DOUBLE_TYPE 2
#define STRING_TYPE 3
#define OBJECT_TYPE 4
#define FUNC_TYPE 5

using namespace std;

class Function{
public:
	string name,content;
	vector<string> arg;
	void print();
	Function();
	Function(const string name, const string argList, const string content);
	string toString();
};

class VarValue;
typedef VarValue* PVarValue;

class Object{
public:
	string name;
	map<string,PVarValue> memberMap;
	void addMember(const string& memName,const VarValue& var);
	PVarValue operator[](const string& name);
	string toString();
	string toString(bool array_type);
};


class VarValue {
private:
	int valuetype;			// -1 for undefined, 0 for null, 1 for int, 2 for double, 3 for string
	long long int_value;
	double double_value;
	string str_value;
	Object obj_value;
	Function func_value;

	bool array_type = 0;

public:
	VarValue();
	VarValue(double);
	VarValue(string);
	VarValue(Object);
	VarValue(Object, bool array_type);
	VarValue(Function);
	int getValueType();
	long long getIntValue();
	double getDoubleValue();
	string getStrValue();
	Function getFuncValue();
	void print();
	bool toBool();
	string toString();
	void addMember(const string& name,const VarValue& val);

	PVarValue operator[](const string&);

	// overload arithmetic operators
	VarValue operator +(const VarValue&);
	VarValue operator -(const VarValue&);
	VarValue operator *(const VarValue&);
	VarValue operator /(const VarValue&);
	VarValue operator %(const VarValue&);
	VarValue operator <<(const VarValue&);
	VarValue operator >>(const VarValue&);
	
	// overload assignment operators
	//VarValue operator =(const VarValue&);
	VarValue operator +=(const VarValue&);
	VarValue operator -=(const VarValue&);
	VarValue operator *=(const VarValue&);
	VarValue operator /=(const VarValue&);
	VarValue operator %=(const VarValue&);
	VarValue operator <<=(const VarValue&);
	VarValue operator >>=(const VarValue&);

	// overload logical operators
	bool operator ==(const VarValue&);
	bool operator !=(const VarValue&);
	bool operator <(const VarValue&);
	bool operator <=(const VarValue&);
	bool operator >(const VarValue&);
	bool operator >=(const VarValue&);

};

class ActRec {
public:
	ActRec();
	int getSize();
	void addVar(string varName, VarValue val=VarValue());
	VarValue getValue(string varName);
	VarValue* getValuePointer(string varName);

private:
	map<string, VarValue> mapVar;
};

class ActRecManager {
public:
	int getSize();
	void insertAR(ActRec ar);
	bool deleteAR();
	void setVar(string varName, VarValue val);
	void addVar(string varName, VarValue val=VarValue());
	VarValue acquireValue(string varName);
	VarValue* acquireValuePointer(string varName);
	Function getFunc(const string &name);
	ActRec& top();	// pay attention to copy construct
	void setVarMember(string varName, string index, VarValue val); 
private:
	vector<ActRec> vecActRec;
};

extern ActRecManager actRecManager;

#endif
