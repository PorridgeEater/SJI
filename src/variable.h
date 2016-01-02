#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class varValue {
public:
	varValue();
	varValue(int);
	varValue(double);
	varValue(string);
	int getValueType();
	int getIntValue();
	double getDoubleValue();
	string getStrValue();
private:
	int valuetype;			// -1 for undefined, 0 for null, 1 for int, 2 for double, 3 for string
	double num_value;
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
