#define eps 1e-12

#include <cmath>
#include "variable.h"
#include "exception.h"

ActRecManager actRecManager;

// implement VarValue
VarValue::VarValue() {
	valuetype = -1;
}

VarValue::VarValue(double x) {
	if (abs(x-(int)x) < eps) {
		valuetype = 1;
		int_value = (long long)x;
	} else {
		valuetype = 2;
		double_value = x;
	}
}

VarValue::VarValue(string x) {
	valuetype = 3;
	str_value = x;
}

int VarValue::getValueType() {
	return valuetype;
}

long long VarValue::getIntValue() {
	return int_value;
}

double VarValue::getDoubleValue() {
	return double_value;
}

string VarValue::getStrValue() {
	return str_value;
}

bool VarValue::toBool(){
	if (valuetype == UNDEFINED_TYPE || valuetype == NULL_TYPE)
		return false;
	if (valuetype == INT_TYPE)
		return int_value!=0;
	if (valuetype == DOUBLE_TYPE)
		return double_value!=0;
	if (valuetype == STRING_TYPE)
		return str_value.length()!=0;
}

string VarValue::toString(){
	if (valuetype == UNDEFINED_TYPE)
		return "undefined";
	if (valuetype == NULL_TYPE)
		return "null";
	if (valuetype == INT_TYPE){
		char tmp[100];
		sprintf(tmp,"%lld",int_value);
		return tmp;
	}
	if (valuetype == DOUBLE_TYPE){
		string tmp;
		stringstream ss;
		ss<<double_value;
		ss>>tmp;
		return tmp;
	}
	if (valuetype == STRING_TYPE)
		return str_value;
}

void VarValue::print() {
	cout << "valuetype = " << valuetype << "\t";
	if (valuetype == INT_TYPE)
		cout << "int value = " << int_value << endl;
	else if (valuetype == DOUBLE_TYPE)
		cout << "double value = " << double_value << endl;
	else if (valuetype == STRING_TYPE)
		cout << "string value = " << str_value << endl;
	else
		cout << "undefined or error" << endl;
}

VarValue VarValue::operator+(const VarValue& x) {
	string tmp;
	stringstream ss;

	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(this->int_value + x.int_value);
				break;
			case 2:
				return VarValue(this->int_value + x.double_value);
				break;
			case 3:
				ss << this->int_value;
				ss >> tmp;
				return VarValue(tmp + x.str_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(this->double_value + x.int_value);
				break;
			case 2:
				return VarValue(this->double_value + x.double_value);
				break;
			case 3:
				ss << this->double_value;
				ss >> tmp;
				return VarValue(tmp + x.str_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 3 ) {
		switch ( x.valuetype ) {
			case 1:
				ss << x.int_value;
				break;
			case 2:
				ss << x.double_value;
				break;
			case 3:
				return VarValue(this->str_value + x.str_value);
				break;
			default:
				break;
		}
		ss >> tmp;
		return VarValue(this->str_value + tmp);
	}
}

VarValue VarValue::operator-(const VarValue& x) {
	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(this->int_value - x.int_value);
				break;
			case 2:
				return VarValue(this->int_value - x.double_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(this->double_value - x.int_value);
				break;
			case 2:
				return VarValue(this->double_value - x.double_value);
				break;
			default:
				break;
		}
	}
}

VarValue VarValue::operator*(const VarValue& x) {
	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(this->int_value * x.int_value);
				break;
			case 2:
				return VarValue(this->int_value * x.double_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(this->double_value * x.int_value);
				break;
			case 2:
				return VarValue(this->double_value * x.double_value);
				break;
			default:
				break;
		}
	}
}

VarValue VarValue::operator/(const VarValue& x) {
	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(double(this->int_value) / x.int_value);
				break;
			case 2:
				return VarValue(this->int_value / x.double_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(this->double_value / x.int_value);
				break;
			case 2:
				return VarValue(this->double_value / x.double_value);
				break;
			default:
				break;
		}
	}
}

VarValue VarValue::operator%(const VarValue& x) {
	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(this->int_value % x.int_value);
				break;
			case 2:
				return VarValue(fmod(this->int_value, x.double_value));
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return VarValue(fmod(this->double_value, x.int_value));
				break;
			case 2:
				return VarValue(fmod(this->double_value, x.double_value));
				break;
			default:
				break;
		}
	}
}

// implement ActRec
ActRec::ActRec() {}

int ActRec::getSize() {
	return mapVar.size();
}

void ActRec::addVar(string varName, VarValue val) {
	mapVar[varName] = val;	
}

VarValue ActRec::getValue(string varName) {
	if (mapVar.count(varName))
		return mapVar[varName];
	else throw Exception("No such a variable in this scope.");
}

VarValue* ActRec::getValuePointer(string varName) {
	if (mapVar.count(varName))
		return &(mapVar[varName]);
	else throw Exception("No such a variable in this scope.");
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

void ActRecManager::addVar(string varName, VarValue val) {
	int size = getSize();
	VarValue resValue;
	while (size--) {
		try{
			resValue = vecActRec[size].getValue(varName);
			vecActRec[size].addVar(varName, val);
			return;
		} catch (Exception e) {
			continue;
		}
	}
	top().addVar(varName, val);	
}

VarValue ActRecManager::acquireValue(string varName) {
	int size = getSize();
	VarValue resValue;
	while (size--) {
		try{
			resValue = vecActRec[size].getValue(varName);
			return resValue;
		} catch (Exception e) {
			continue;
		}
	}
	throw Exception("No such a variable \""+varName+"\".");
}

VarValue* ActRecManager::acquireValuePointer(string varName) {
	int size = getSize();
	while (size--) {
		try{
			vecActRec[size].getValue(varName);
			return vecActRec[size].getValuePointer(varName);
		} catch (Exception e) {
			continue;
		}
	}
	throw Exception("No such a variable \""+varName+"\".");
}

ActRec& ActRecManager::top() {
	return vecActRec.back();
	// here return the reference, so we use &
}
