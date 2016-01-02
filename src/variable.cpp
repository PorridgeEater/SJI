#include "variable.h"

// implement varValue
varValue::varValue() {
	valuetype = -1;
}

varValue::varValue(int x) {
	valuetype = 1;
	num_value = x;
}

varValue::varValue(double x) {
	valuetype = 2;
	num_value = x;
}

varValue::varValue(string x) {
	valuetype = 3;
	str_value = x;
}

int varValue::getValueType() {
	return valuetype;
}

int varValue::getIntValue() {
	return (int)num_value;
}

double varValue::getDoubleValue() {
	return num_value;
}

string varValue::getStrValue() {
	return str_value;
}

// implement ActRec
ActRec::ActRec() {}

int ActRec::getSize() {
	return mapVar.size();
}

void ActRec::addVar(string varName, varValue val) {
	mapVar[varName] = val;	
}

varValue ActRec::getValue(string varName) {
	varValue tmp;
	if (mapVar.count(varName))
		tmp = mapVar[varName];
	return tmp;
}

// implement ActRecManager
int ActRecManager::getSize() {
	return vecActRec.size();
}

void ActRecManager::insertAR(ActRec ar) {
	vecActRec.push_back(ar);
}

bool ActRecManager::deleteAR() {
	bool res = false;
	if ( getSize() != 0 ) {
		vecActRec.pop_back();	
		res = true;
	}
	return res;
}

void ActRecManager::addVar(string varName, varValue val) {
	top().addVar(varName, val);	
}

varValue ActRecManager::acquireValue(string varName) {
	int size = getSize();
	varValue resValue;
	while (size--) {
		resValue = vecActRec[size].getValue(varName);
		if (resValue.getValueType() != -1)
			break;
	}
	return resValue;
}

ActRec& ActRecManager::top() {
	return vecActRec.back();
	// here return the reference, so we use &
}
