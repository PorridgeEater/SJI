#define eps 1e-12

#include <cmath>
#include "variable.h"

ActRecManager actRecManager;



// implement varValue
varValue::varValue() {
	valuetype = -1;
}

varValue::varValue(double x) {
	if (abs(x-(int)x) < eps) {
		valuetype = 1;
		int_value = (long long)x;
	} else {
		valuetype = 2;
		double_value = x;
	}
}

varValue::varValue(string x) {
	valuetype = 3;
	str_value = x;
}

int varValue::getValueType() {
	return valuetype;
}

long long varValue::getIntValue() {
	return int_value;
}

double varValue::getDoubleValue() {
	return double_value;
}

string varValue::getStrValue() {
	return str_value;
}

void varValue::print() {
	cout << "valuetype = " << valuetype << "\t";
	if (valuetype == 1)
		cout << "int value = " << int_value << endl;
	else if (valuetype == 2)
		cout << "double value = " << double_value << endl;
	else if (valuetype == 3)
		cout << "string value = " << str_value << endl;
	else
		cout << "undefined or error" << endl;
}

varValue varValue::operator+(const varValue& x) {
	string tmp;
	stringstream ss;

	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(this->int_value + x.int_value);
				break;
			case 2:
				return varValue(this->int_value + x.double_value);
				break;
			case 3:
				ss << this->int_value;
				ss >> tmp;
				return varValue(tmp + x.str_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(this->double_value + x.int_value);
				break;
			case 2:
				return varValue(this->double_value + x.double_value);
				break;
			case 3:
				ss << this->double_value;
				ss >> tmp;
				return varValue(tmp + x.str_value);
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
				return varValue(this->str_value + x.str_value);
				break;
			default:
				break;
		}
		ss >> tmp;
		return varValue(this->str_value + tmp);
	}
}

varValue varValue::operator-(const varValue& x) {
	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(this->int_value - x.int_value);
				break;
			case 2:
				return varValue(this->int_value - x.double_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(this->double_value - x.int_value);
				break;
			case 2:
				return varValue(this->double_value - x.double_value);
				break;
			default:
				break;
		}
	}
}

varValue varValue::operator*(const varValue& x) {
	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(this->int_value * x.int_value);
				break;
			case 2:
				return varValue(this->int_value * x.double_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(this->double_value * x.int_value);
				break;
			case 2:
				return varValue(this->double_value * x.double_value);
				break;
			default:
				break;
		}
	}
}

varValue varValue::operator/(const varValue& x) {
	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(double(this->int_value) / x.int_value);
				break;
			case 2:
				return varValue(this->int_value / x.double_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(this->double_value / x.int_value);
				break;
			case 2:
				return varValue(this->double_value / x.double_value);
				break;
			default:
				break;
		}
	}
}

varValue varValue::operator%(const varValue& x) {
	if ( this->valuetype == 1 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(this->int_value % x.int_value);
				break;
			case 2:
				return varValue(fmod(this->int_value, x.double_value));
				break;
			default:
				break;
		}
	} else if ( this->valuetype == 2 ) {
		switch ( x.valuetype ) {
			case 1:
				return varValue(fmod(this->double_value, x.int_value));
				break;
			case 2:
				return varValue(fmod(this->double_value, x.double_value));
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
