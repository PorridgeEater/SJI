#define eps 1e-12

#include <cmath>
#include "variable.h"
#include "exception.h"

ActRecManager actRecManager;

inline bool hasDigit(string s) {
	for ( int i=0, len=s.length(); i<len; i++ ) {
		if ( s[i]>='0' && s[i]<='9' )
			return true;
	}
	return false;
} 

void Function::print(){
	cerr<<"Function info :"<<endl;
	cerr<<"name : "<<name<<endl;
	cerr<<"content : "<<content<<endl;
	cerr<<"arg : ";
	for (int i=0;i<arg.size();i++)
		cerr<<arg[i]<<" ";
	cerr<<endl;
	cerr<<"-------------------"<<endl;
}

// implement VarValue
VarValue::VarValue() {
	valuetype = UNDEFINED_TYPE;
}

VarValue::VarValue(double x) {
	if ( abs(x-(int)x) < eps ) {
		valuetype = INT_TYPE;
		int_value = (long long)x;
	} else {
		valuetype = DOUBLE_TYPE;
		double_value = x;
	}
}

VarValue::VarValue(string x) {
	valuetype = STRING_TYPE;
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

bool VarValue::toBool() {
	switch ( valuetype ) {
		case UNDEFINED_TYPE:
		case NULL_TYPE:
			return false;
			break;
		case INT_TYPE:
			return int_value!=0;
			break;
		case DOUBLE_TYPE:
			return double_value!=0;
			break;
		case STRING_TYPE:
			return str_value.length()!=0;
			break;
		default:
			throw Exception("invalid valuetype!");
			break;
	}
}

string VarValue::toString() {
	switch ( valuetype ) {
		case UNDEFINED_TYPE:
			return "undefined";
			break;
		case NULL_TYPE:
			return "null";
			break;
		case INT_TYPE:
		{
			char tmp[100];
			sprintf(tmp, "%lld", int_value);
			return tmp;
			break;
		}
		case DOUBLE_TYPE:
		{
			string t;
			stringstream ss;
			ss << double_value;
			ss >> t;
			return t;
			break;
		}
		case STRING_TYPE:
			return str_value;
			break;
		default:
			throw Exception("Invalid valuetype!");
			break;
	}
}

void VarValue::print() {
	cout << "valuetype = " << valuetype << "\t";
	cout << "value = " << toString() << endl;
}

VarValue VarValue::operator +(const VarValue& x) {
	string tmp;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value + x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value + x.double_value);
				break;
			case STRING_TYPE:
				ss << this->int_value;
				ss >> tmp;
				return VarValue(tmp + x.str_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == DOUBLE_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->double_value + x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->double_value + x.double_value);
				break;
			case STRING_TYPE:
				ss << this->double_value;
				ss >> tmp;
				return VarValue(tmp + x.str_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
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
	} else {
		throw Exception("invalid valuetype for +");
	}
}

VarValue VarValue::operator -(const VarValue& x) {
	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value - x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value - x.double_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == DOUBLE_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->double_value - x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->double_value - x.double_value);
				break;
			default:
				break;
		}
	} else {
		throw Exception("invalid valuetype for -");
	}
}

VarValue VarValue::operator *(const VarValue& x) {
	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value * x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value * x.double_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == DOUBLE_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->double_value * x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->double_value * x.double_value);
				break;
			default:
				break;
		}
	} else {
		throw Exception("invalid valuetype for *");
	}
}

VarValue VarValue::operator /(const VarValue& x) {
	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(double(this->int_value) / x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value / x.double_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == DOUBLE_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->double_value / x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->double_value / x.double_value);
				break;
			default:
				break;
		}
	} else {
		throw Exception("invalid valuetype for /");
	}
}

VarValue VarValue::operator %(const VarValue& x) {
	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value % x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(fmod(this->int_value, x.double_value));
				break;
			default:
				break;
		}
	} else if ( this->valuetype == DOUBLE_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(fmod(this->double_value, x.int_value));
				break;
			case DOUBLE_TYPE:
				return VarValue(fmod(this->double_value, x.double_value));
				break;
			default:
				break;
		}
	} else {
		throw Exception("invalid valuetype for \%");
	}
}

VarValue VarValue::operator =(const VarValue& x) {
	return x;
}

VarValue VarValue::operator *=(const VarValue& x) {
	return x;
}

VarValue VarValue::operator /=(const VarValue& x) {
	return x;
}

VarValue VarValue::operator %=(const VarValue& x) {
	return x;
}

VarValue VarValue::operator -=(const VarValue& x) {
	return x;
}

VarValue VarValue::operator <<=(const VarValue& x) {
	return x;
}

VarValue VarValue::operator >>=(const VarValue& x) {
	return x;
}


bool VarValue::operator ==(const VarValue& x) {
	if ( this->valuetype == STRING_TYPE && x.valuetype == STRING_TYPE ) {
		return (this->str_value == x.str_value);
	} else {
		double m, n;
		stringstream ss;			
		if ( this->valuetype == INT_TYPE )
			m = this->int_value;
		else if ( this->valuetype == DOUBLE_TYPE )
			m = this->double_value;
		else if ( this->valuetype == STRING_TYPE ) {
			if ( hasDigit(this->str_value) ) {
				ss << this->str_value;
				ss >> m;
			} else {
				return false;
			}
		}
		if ( x.valuetype == INT_TYPE )
			n = x.int_value;
		else if ( x.valuetype == DOUBLE_TYPE )
			n = x.double_value;
		else if ( x.valuetype == STRING_TYPE ) {
			if ( hasDigit(x.str_value) ) {
				ss << x.str_value;
				ss >> n;
			} else {
				return false;
			}
		}
		if ( abs(m-n) < eps ) {
			return true;
		} else {
			return false;
		}
	}
}

bool VarValue::operator !=(const VarValue& x) {
	if ( this->valuetype == STRING_TYPE && x.valuetype == STRING_TYPE ) {
		return (this->str_value != x.str_value);
	} else {
		double m, n;
		stringstream ss;			
		if ( this->valuetype == INT_TYPE )
			m = this->int_value;
		else if ( this->valuetype == DOUBLE_TYPE )
			m = this->double_value;
		else if ( this->valuetype == STRING_TYPE ) {
			if ( hasDigit(this->str_value) ) {
				ss << this->str_value;
				ss >> m;
			} else {
				return true;
			}
		}
		if ( x.valuetype == INT_TYPE )
			n = x.int_value;
		else if ( x.valuetype == DOUBLE_TYPE )
			n = x.double_value;
		else if ( x.valuetype == STRING_TYPE ) {
			if ( hasDigit(x.str_value) ) {
				ss << x.str_value;
				ss >> n;
			} else {
				return true;
			}
		}
		if ( abs(m-n) < eps ) {
			return false;
		} else {
			return true;
		}
	}
}

bool VarValue::operator <(const VarValue& x) {
	if ( this->valuetype == STRING_TYPE && x.valuetype == STRING_TYPE ) {
		return (this->str_value < x.str_value);
	} else {
		double m, n;
		stringstream ss;			
		if ( this->valuetype == INT_TYPE )
			m = this->int_value;
		else if ( this->valuetype == DOUBLE_TYPE )
			m = this->double_value;
		else if ( this->valuetype == STRING_TYPE ) {
			if ( hasDigit(this->str_value) ) {
				ss << this->str_value;
				ss >> m;
			} else {
				return false;
			}
		}
		if ( x.valuetype == INT_TYPE )
			n = x.int_value;
		else if ( x.valuetype == DOUBLE_TYPE )
			n = x.double_value;
		else if ( x.valuetype == STRING_TYPE ) {
			if ( hasDigit(x.str_value) ) {
				ss << x.str_value;
				ss >> n;
			} else {
				return false;
			}
		}
		if ( n - m > eps ) {
			return true;
		} else {
			return false;
		}
	}
}

bool VarValue::operator >(const VarValue& x) {
	if ( this->valuetype == STRING_TYPE && x.valuetype == STRING_TYPE ) {
		return (this->str_value > x.str_value);
	} else {
		double m, n;
		stringstream ss;			
		if ( this->valuetype == INT_TYPE )
			m = this->int_value;
		else if ( this->valuetype == DOUBLE_TYPE )
			m = this->double_value;
		else if ( this->valuetype == STRING_TYPE ) {
			if ( hasDigit(this->str_value) ) {
				ss << this->str_value;
				ss >> m;
			} else {
				return false;
			}
		}
		if ( x.valuetype == INT_TYPE )
			n = x.int_value;
		else if ( x.valuetype == DOUBLE_TYPE )
			n = x.double_value;
		else if ( x.valuetype == STRING_TYPE ) {
			if ( hasDigit(x.str_value) ) {
				ss << x.str_value;
				ss >> n;
			} else {
				return false;
			}
		}
		if ( m - n > eps ) {
			return true;
		} else {
			return false;
		}
	}
}

// implement ActRec
ActRec::ActRec() {}

int ActRec::getSize() {
	return mapVar.size();
}

int ActRec::findFunc(const string &name){
	for (int i=0;i<funcList.size();i++){
		if (funcList[i].name==name) return i;
	}
	return -1;
}
void ActRec::addFunc(const Function &func){
	int t=findFunc(func.name);
	if (t>=0) funcList[t]=func;
	else funcList.push_back(func);
}
Function ActRec::getFunc(const string &name){
	int t=findFunc(name);
	if (t>=0){
		return funcList[t];
	}
	else throw Exception("No such a function \""+name+"\"."); 
}


void ActRec::addVar(string varName, VarValue val) {
	mapVar[varName] = val;	
}

VarValue ActRec::getValue(string varName) {
	if (mapVar.count(varName))
		return mapVar[varName];
	else 
		throw Exception("No such a variable in this scope.");
}

VarValue* ActRec::getValuePointer(string varName) {
	if (mapVar.count(varName))
		return &(mapVar[varName]);
	else 
		throw Exception("No such a variable in this scope.");
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


void ActRecManager::addFunc(const Function &func) {
	top().addFunc(func);	
}

Function ActRecManager::getFunc(const string &name) {
	int size = getSize();
	Function func;
	while (size--) {
		try{
			func = vecActRec[size].getFunc(name);
			return func;
		} catch (Exception e) {
			continue;
		}
	}
	throw Exception("No such a function \""+name+"()\".");
}

void ActRecManager::setVar(string varName, VarValue val) {
	int size = getSize();
	VarValue resValue;
	while (size--) {
		try {
			resValue = vecActRec[size].getValue(varName);
			vecActRec[size].addVar(varName, val);
			return;
		} catch (Exception e) {
			continue;
		}
	}
	addVar(varName, val);
}

void ActRecManager::addVar(string varName, VarValue val) {
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
