#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class varValue {
public:
	varValue();
	varValue(double);
	varValue(string);
	int getValueType();
	long long getIntValue();
	double getDoubleValue();
	string getStrValue();
	void print();

	varValue operator+(const varValue&);
	varValue operator-(const varValue&);
	varValue operator*(const varValue&);
	varValue operator/(const varValue&);
	varValue operator%(const varValue&);

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
	void addVar(string varName, varValue val);
	varValue getValue(string varName);
private:
	map<string, varValue> mapVar;	
};

class ActRecManager {
public:
	int getSize();
	void insertAR(ActRec ar);
	bool deleteAR();
	void addVar(string varName, varValue val);
	varValue acquireValue(string varName);
	ActRec& top();	// pay attention to copy construct
private:
	vector<ActRec> vecActRec;
};

#endif
