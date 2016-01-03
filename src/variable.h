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

using namespace std;

class Function{
public:
	string name,content;
	vector<string> arg;

	void print();
};


class VarValue {
public:
	VarValue();
	VarValue(double);
	VarValue(string);
	int getValueType();
	long long getIntValue();
	double getDoubleValue();
	string getStrValue();
	void print();
	bool toBool();
	string toString();

	// overload arithmetic operators
	VarValue operator +(const VarValue&);
	VarValue operator -(const VarValue&);
	VarValue operator *(const VarValue&);
	VarValue operator /(const VarValue&);
	VarValue operator %(const VarValue&);
	
	// overload logical operators
	bool operator ==(const VarValue&);
	bool operator <(const VarValue&);

private:
	int valuetype;			// -1 for undefined, 0 for null, 1 for int, 2 for double, 3 for string
	long long int_value;
	double double_value;
	string str_value;
};

class ActRec {
public:
	ActRec();
	int getSize();
	void addVar(string varName, VarValue val=VarValue());
	VarValue getValue(string varName);
	VarValue* getValuePointer(string varName);

	int findFunc(const string &name);
	void addFunc(const Function &func);
	Function getFunc(const string &name);

private:
	map<string, VarValue> mapVar;
	vector<Function> funcList;
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
	void addFunc(const Function &func);
	ActRec& top();	// pay attention to copy construct
private:
	vector<ActRec> vecActRec;
};

extern ActRecManager actRecManager;

#endif
