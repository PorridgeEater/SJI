#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

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

	VarValue operator+(const VarValue&);
	VarValue operator-(const VarValue&);
	VarValue operator*(const VarValue&);
	VarValue operator/(const VarValue&);
	VarValue operator%(const VarValue&);

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
	void addVar(string varName, VarValue val);
	VarValue getValue(string varName);
private:
	map<string, VarValue> mapVar;	
};

class ActRecManager {
public:
	int getSize();
	void insertAR(ActRec ar);
	bool deleteAR();
	void addVar(string varName, VarValue val);
	VarValue acquireValue(string varName);
	ActRec& top();	// pay attention to copy construct
private:
	vector<ActRec> vecActRec;
};

extern ActRecManager actRecManager;

#endif
