#include "variable.h"


varValue::varValue(double):num_value(num_value), valuetype(2) {
}

ActRec::ActRec() {
}

int ActRec::getSize() {
	return mapVar.size();
}

void ActRec::addVar(string varName, varValue val) {
	mapVar[varName] = val;	
}

varValue ActRec::getValue(string varName) {
	varValue tmp;
	tmp.valuetype = -1;
	if (mapVar.count(varName))
		tmp = mapVar[varName];
	return tmp;
}



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
		if (resValue.valuetype != -1)
			break;
	}
	return resValue;
}

ActRec& ActRecManager::top() {
	return vecActRec.back();
	// here return the reference, so we use &
}
