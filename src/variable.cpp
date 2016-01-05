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

inline int allDigit(string s) {
	int dot;
	dot = 0;
	for ( int i=0, len=s.length(); i<len; i++ ) {
		if ( s[i] == '.' ) {
			dot++;
			if ( dot > 1 )
				return -1;
		} else if ( s[i]<'0' || s[i]>'9' ) {
			return -1;
		}
	}
	if ( dot == 0 )
		return 0;
	else if ( dot == 1 )
		return 1;
	return -1;
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

Function::Function(){}

void splitArgList(const string &argList,vector<string> &v){
	char tmp[100];
	int cnt=0;
	for (int i=0,l=argList.length();i<l;i++)
		if (argList[i]!=' ') tmp[cnt++]=argList[i];
	tmp[cnt]='\0';
	string s(tmp);
	if (s.length()==0) return;
	for (int i=0,last=-1,l=s.length();i<=l;i++){
		if (i==l || s[i]==','){
			if (i<=last+1) throw Exception("Arguments are wrong.");
			v.push_back(s.substr(last+1,i-last-1));
			last=i;
		}
	}
}

Function::Function(const string name, const string argList, const string content){
	this->name=name;
	this->content=content;
	splitArgList(argList,this->arg);
}

string Function::toString(){
	string ret=name+"(";
	if (arg.size()>0) ret=ret+arg[0];
	for (int i=1;i<arg.size();i++)
		ret=ret+", "+arg[i];
	ret=ret+") {";
	ret=ret+content+"}";
	return ret;
}


void Object::addMember(const string& memName,const VarValue& var){
	VarValue *pv = new VarValue();
	*pv=var;
	memberMap[memName]=pv;	
}

PVarValue Object::operator[](const string& name){
	return memberMap[name];
}

string Object::toString(){
	auto it=memberMap.begin();
	string ret = "Object {";
	ret= ret + it->first + ": " + (it->second)->toString();
	for (++it;it!=memberMap.end();++it){
		ret = ret + ", " + it->first + ": " + (it->second)->toString();
	}
	ret = ret + "}";
	return ret;
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

VarValue::VarValue(Object x){
	valuetype=OBJECT_TYPE;
	obj_value=x;
}

VarValue::VarValue(Function x){
	valuetype=FUNC_TYPE;
	func_value=x;
}

void VarValue::addMember(const string& name,const VarValue& val){
	if (valuetype==OBJECT_TYPE) {
		obj_value.addMember(name,val);
	}
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

Function VarValue::getFuncValue() {
	return func_value;
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
		case OBJECT_TYPE:
			return true;
			break;
		case FUNC_TYPE:
			return true;
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
		case OBJECT_TYPE:
			return obj_value.toString();
			break;
		case FUNC_TYPE:
			return func_value.toString();
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

PVarValue VarValue::operator[](const string& name){
	if (valuetype!=OBJECT_TYPE){
		obj_value.addMember(name,VarValue());
	};
	return obj_value[name];
}

VarValue VarValue::operator +(const VarValue& x) {
	string tmp;
	stringstream ss;

	if ( this->valuetype == UNDEFINED_TYPE ) {
		switch ( x.valuetype ) {
			case UNDEFINED_TYPE:
				return VarValue(this->toString() + "undefined");
				break;
			case INT_TYPE:
				ss << x.int_value;
				ss >> tmp;
				return VarValue(this->toString() + tmp);
				break;
			case DOUBLE_TYPE:
				ss << x.double_value;
				ss >> tmp;
				return VarValue(this->toString() + tmp);
				break;
			case STRING_TYPE:
				return VarValue(this->toString() + x.str_value);
				break;
			default:
				break;
		}
	} else if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case UNDEFINED_TYPE:
				return VarValue(this->toString() + "undefined");
				break;
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
			case UNDEFINED_TYPE:
				return VarValue(this->toString() + "undefined");
				break;
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
			case UNDEFINED_TYPE:
				return VarValue(this->toString() + "undefined");
				break;
			case INT_TYPE:
				ss << x.int_value;
				break;
			case DOUBLE_TYPE:
				ss << x.double_value;
				break;
			case STRING_TYPE:
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
	return VarValue();
}

VarValue VarValue::operator -(const VarValue& x) {
	double tmp;
	double tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value - x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value - x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value - tmp);
				} else {
					throw Exception("NaN Error");
				}
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
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value - tmp);
				} else {
					throw Exception("NaN Error");
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 ) {
			ss << this->str_value;
			ss >> tmp;
			switch ( x.valuetype ) {
				case INT_TYPE:
					return VarValue(tmp - x.int_value);
					break;
				case DOUBLE_TYPE:
					return VarValue(tmp - x.double_value);
					break;
				case STRING_TYPE:
					if ( allDigit(x.str_value) != -1 ) {
						ss.clear();
						ss.str("");
						ss << x.str_value;
						ss >> tmp2;
						return VarValue(tmp - tmp2);
					} else {
						throw Exception("NaN Error");
					}
					break;
				default:
					break;
			}
		} else {
			throw Exception("NaN Error");
		}
	} else {
		throw Exception("invalid valuetype for -");
	}
	return VarValue();
}

VarValue VarValue::operator *(const VarValue& x) {
	double tmp;
	double tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value * x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value * x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value * tmp);
				} else {
					throw Exception("NaN Error");
				}
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
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
						ss << x.str_value;
						ss >> tmp;
						return VarValue(this->int_value * tmp);
				} else {
					throw Exception("NaN Error");
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 ) {
			ss << this->str_value;
			ss >> tmp;
			switch ( x.valuetype ) {
				case INT_TYPE:
					return VarValue(tmp * x.int_value);
					break;
				case DOUBLE_TYPE:
					return VarValue(tmp * x.double_value);
					break;
				case STRING_TYPE:
					if ( allDigit(x.str_value) != -1 ) {
						ss.clear();
						ss.str("");
						ss << x.str_value;
						ss >> tmp2;
						return VarValue(tmp * tmp2);
					} else {
						throw Exception("NaN Error");
					}
					break;
				default:
					break;
			}
		} else {
			throw Exception("NaN Error");
		}
	} else {
		throw Exception("invalid valuetype for *");
	}
	return VarValue();
}

VarValue VarValue::operator /(const VarValue& x) {
	double tmp;
	double tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(double(this->int_value) / x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value / x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value / tmp);
				} else {
					throw Exception("NaN Error");
				}
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
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value / tmp);
				} else {
					throw Exception("NaN Error");
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 ) {
			ss << this->str_value;
			ss >> tmp;
			switch ( x.valuetype ) {
				case INT_TYPE:
					return VarValue(tmp * x.int_value);
					break;
				case DOUBLE_TYPE:
					return VarValue(tmp * x.double_value);
					break;
				case STRING_TYPE:
					if ( allDigit(x.str_value) != -1 ) {
						ss.clear();
						ss.str("");
						ss << x.str_value;
						ss >> tmp2;
						return VarValue(tmp / tmp2);
					} else {
						throw Exception("NaN Error");
					}
					break;
				default:
					break;
			}
		} else {
			throw Exception("NaN Error");
		}
	} else {
		throw Exception("invalid valuetype for /");
	}
	return VarValue();
}

VarValue VarValue::operator %(const VarValue& x) {
	int int_tmp;
	int int_tmp2;
	double tmp;
	double tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value % x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(fmod(this->int_value, x.double_value));
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					if ( allDigit(x.str_value) == 0 ) {
						ss >> int_tmp;
						return VarValue(this->int_value % int_tmp);
					} else if ( allDigit(x.str_value) == 1 ) {
						ss >> tmp;
						return VarValue(fmod(this->int_value, tmp));
					}
				} else {
					throw Exception("NaN Error");
				}
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
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(fmod(this->int_value, tmp));
				} else {
					throw Exception("NaN Error");
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 && allDigit(x.str_value) != -1 ) {
			if ( allDigit(this->str_value) == 0 && allDigit(x.str_value) == 0 ) {
				ss << this->str_value;
				ss >> int_tmp;
				ss.clear();
				ss.str("");
				ss << x.str_value;
				ss >> int_tmp2;
				return VarValue(int_tmp % int_tmp2);
			} else {
				ss << this->str_value;
				ss >> tmp;
				ss.clear();
				ss.str("");
				ss << x.str_value;
				ss >> tmp2;
				return VarValue(fmod(tmp, tmp2));
			}
		} else {
			throw Exception("NaN Error");
		}
	} else {
		throw Exception("invalid valuetype for \%");
	}
	return VarValue();
}

VarValue VarValue::operator <<(const VarValue& x) {
	int int_tmp;
	int int_tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value << x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value << (int)x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> int_tmp;
					return VarValue(this->int_value << int_tmp);
				} else {
					// if str_value contains letters, the result will be 0
					return VarValue();
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == DOUBLE_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue((int)this->double_value << x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue((int)this->double_value << (int)x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> int_tmp;
					return VarValue((int)this->double_value << (int)int_tmp);
				} else {
					// if str_value contains letters, the result will be 0
					return VarValue();
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 && allDigit(x.str_value) != -1 ) {
			ss << this->str_value;
			ss >> int_tmp;
			ss.clear();
			ss.str("");
			ss << x.str_value;
			ss >> int_tmp2;
			return VarValue(int_tmp << int_tmp2);
		} else {
			return VarValue();
		}
	} else {
		throw Exception("NaN Error");
	}
	return VarValue();
}

VarValue VarValue::operator >>(const VarValue& x) {
	int int_tmp;
	int int_tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value >> x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value >> (int)x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> int_tmp;
					return VarValue(this->int_value >> int_tmp);
				} else {
					// if str_value contains letters, the result will be 0
					return VarValue();
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == DOUBLE_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue((int)this->double_value >> x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue((int)this->double_value >> (int)x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> int_tmp;
					return VarValue((int)this->double_value >> (int)int_tmp);
				} else {
					// if str_value contains letters, the result will be 0
					return VarValue();
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 && allDigit(x.str_value) != -1 ) {
			ss << this->str_value;
			ss >> int_tmp;
			ss.clear();
			ss.str("");
			ss << x.str_value;
			ss >> int_tmp2;
			return VarValue(int_tmp >> int_tmp2);
		} else {
			return VarValue();
		}
	} else {
		throw Exception("NaN Error");
	}
	return VarValue();
}

/*
VarValue VarValue::operator =(const VarValue& x) {
	if ( x.valuetype == INT_TYPE )
		return VarValue(x.int_value);
	else if ( x.valuetype == DOUBLE_TYPE )
		return VarValue(x.double_value);
	else if ( x.valuetype == STRING_TYPE )
		return VarValue(x.str_value);
	else 
		return VarValue();
}*/

VarValue VarValue::operator +=(const VarValue& x) {
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
			case INT_TYPE:
				ss << x.int_value;
				break;
			case DOUBLE_TYPE:
				ss << x.double_value;
				break;
			case STRING_TYPE:
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
	return VarValue();
}

VarValue VarValue::operator -=(const VarValue& x) {
	double tmp;
	double tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value - x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value - x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value - tmp);
				} else {
					throw Exception("NaN Error");
				}
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
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value - tmp);
				} else {
					throw Exception("NaN Error");
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 ) {
			ss << this->str_value;
			ss >> tmp;
			switch ( x.valuetype ) {
				case INT_TYPE:
					return VarValue(tmp - x.int_value);
					break;
				case DOUBLE_TYPE:
					return VarValue(tmp - x.double_value);
					break;
				case STRING_TYPE:
					if ( allDigit(x.str_value) != -1 ) {
						ss.clear();
						ss.str("");
						ss << x.str_value;
						ss >> tmp2;
						return VarValue(tmp - tmp2);
					} else {
						throw Exception("NaN Error");
					}
					break;
				default:
					break;
			}
		} else {
			throw Exception("NaN Error");
		}
	} else {
		throw Exception("invalid valuetype for -");
	}
	return VarValue();
}

VarValue VarValue::operator *=(const VarValue& x) {
	double tmp;
	double tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value * x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value * x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value * tmp);
				} else {
					throw Exception("NaN Error");
				}
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
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
						ss << x.str_value;
						ss >> tmp;
						return VarValue(this->int_value * tmp);
				} else {
					throw Exception("NaN Error");
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 ) {
			ss << this->str_value;
			ss >> tmp;
			switch ( x.valuetype ) {
				case INT_TYPE:
					return VarValue(tmp * x.int_value);
					break;
				case DOUBLE_TYPE:
					return VarValue(tmp * x.double_value);
					break;
				case STRING_TYPE:
					if ( allDigit(x.str_value) != -1 ) {
						ss.clear();
						ss.str("");
						ss << x.str_value;
						ss >> tmp2;
						return VarValue(tmp * tmp2);
					} else {
						throw Exception("NaN Error");
					}
					break;
				default:
					break;
			}
		} else {
			throw Exception("NaN Error");
		}
	} else {
		throw Exception("invalid valuetype for *");
	}
	return VarValue();
}

VarValue VarValue::operator /=(const VarValue& x) {
	double tmp;
	double tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(double(this->int_value) / x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value / x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value / tmp);
				} else {
					throw Exception("NaN Error");
				}
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
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(this->int_value / tmp);
				} else {
					throw Exception("NaN Error");
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 ) {
			ss << this->str_value;
			ss >> tmp;
			switch ( x.valuetype ) {
				case INT_TYPE:
					return VarValue(tmp * x.int_value);
					break;
				case DOUBLE_TYPE:
					return VarValue(tmp * x.double_value);
					break;
				case STRING_TYPE:
					if ( allDigit(x.str_value) != -1 ) {
						ss.clear();
						ss.str("");
						ss << x.str_value;
						ss >> tmp2;
						return VarValue(tmp / tmp2);
					} else {
						throw Exception("NaN Error");
					}
					break;
				default:
					break;
			}
		} else {
			throw Exception("NaN Error");
		}
	} else {
		throw Exception("invalid valuetype for /");
	}
	return VarValue();
}

VarValue VarValue::operator %=(const VarValue& x) {
	int int_tmp;
	int int_tmp2;
	double tmp;
	double tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value % x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(fmod(this->int_value, x.double_value));
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					if ( allDigit(x.str_value) == 0 ) {
						ss >> int_tmp;
						return VarValue(this->int_value % int_tmp);
					} else if ( allDigit(x.str_value) == 1 ) {
						ss >> tmp;
						return VarValue(fmod(this->int_value, tmp));
					}
				} else {
					throw Exception("NaN Error");
				}
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
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> tmp;
					return VarValue(fmod(this->int_value, tmp));
				} else {
					throw Exception("NaN Error");
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 && allDigit(x.str_value) != -1 ) {
			if ( allDigit(this->str_value) == 0 && allDigit(x.str_value) == 0 ) {
				ss << this->str_value;
				ss >> int_tmp;
				ss.clear();
				ss.str("");
				ss << x.str_value;
				ss >> int_tmp2;
				return VarValue(int_tmp % int_tmp2);
			} else {
				ss << this->str_value;
				ss >> tmp;
				ss.clear();
				ss.str("");
				ss << x.str_value;
				ss >> tmp2;
				return VarValue(fmod(tmp, tmp2));
			}
		} else {
			throw Exception("NaN Error");
		}
	} else {
		throw Exception("invalid valuetype for \%");
	}
	return VarValue();
}


VarValue VarValue::operator <<=(const VarValue& x) {
	int int_tmp;
	int int_tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value << x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value << (int)x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> int_tmp;
					return VarValue(this->int_value << int_tmp);
				} else {
					// if str_value contains letters, the result will be 0
					return VarValue();
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == DOUBLE_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue((int)this->double_value << x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue((int)this->double_value << (int)x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> int_tmp;
					return VarValue((int)this->double_value << (int)int_tmp);
				} else {
					// if str_value contains letters, the result will be 0
					return VarValue();
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 && allDigit(x.str_value) != -1 ) {
			ss << this->str_value;
			ss >> int_tmp;
			ss.clear();
			ss.str("");
			ss << x.str_value;
			ss >> int_tmp2;
			return VarValue(int_tmp << int_tmp2);
		} else {
			return VarValue();
		}
	} else {
		throw Exception("NaN Error");
	}
	return VarValue();
}

VarValue VarValue::operator >>=(const VarValue& x) {
	int int_tmp;
	int int_tmp2;
	stringstream ss;

	if ( this->valuetype == INT_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue(this->int_value >> x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue(this->int_value >> (int)x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> int_tmp;
					return VarValue(this->int_value >> int_tmp);
				} else {
					// if str_value contains letters, the result will be 0
					return VarValue();
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == DOUBLE_TYPE ) {
		switch ( x.valuetype ) {
			case INT_TYPE:
				return VarValue((int)this->double_value >> x.int_value);
				break;
			case DOUBLE_TYPE:
				return VarValue((int)this->double_value >> (int)x.double_value);
				break;
			case STRING_TYPE:
				if ( allDigit(x.str_value) != -1 ) {
					ss << x.str_value;
					ss >> int_tmp;
					return VarValue((int)this->double_value >> (int)int_tmp);
				} else {
					// if str_value contains letters, the result will be 0
					return VarValue();
				}
				break;
			default:
				break;
		}
	} else if ( this->valuetype == STRING_TYPE ) {
		if ( allDigit(this->str_value) != -1 && allDigit(x.str_value) != -1 ) {
			ss << this->str_value;
			ss >> int_tmp;
			ss.clear();
			ss.str("");
			ss << x.str_value;
			ss >> int_tmp2;
			return VarValue(int_tmp >> int_tmp2);
		} else {
			return VarValue();
		}
	} else {
		throw Exception("NaN Error");
	}
	return VarValue();
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
			if ( allDigit(this->str_value) ) {
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
			if ( allDigit(x.str_value) ) {
				ss.clear();
				ss.str("");
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
				ss.clear();
				ss.str("");
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
				ss.clear();
				ss.str("");
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

bool VarValue::operator <=(const VarValue& x) {
	if ( this->valuetype == STRING_TYPE && x.valuetype == STRING_TYPE ) {
		return (this->str_value <= x.str_value);
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
				ss.clear();
				ss.str("");
				ss << x.str_value;
				ss >> n;
			} else {
				return false;
			}
		}
		if ( m - n > eps ) {
			return false;
		} else {
			return true;
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
				ss.clear();
				ss.str("");
				ss << x.str_value;
				ss >> n;
			} else {
				return false;
			}
		}
		if ( n - m > eps ) {
			return false;
		} else {
			return true;
		}
	}
}

bool VarValue::operator >=(const VarValue& x) {
	if ( this->valuetype == STRING_TYPE && x.valuetype == STRING_TYPE ) {
		return (this->str_value >= x.str_value);
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
				ss.clear();
				ss.str("");
				ss << x.str_value;
				ss >> n;
			} else {
				return false;
			}
		}
		if ( n - n > eps ) {
			return false;
		} else {
			return true;
		}
	}
}

// implement ActRec
ActRec::ActRec() {}

int ActRec::getSize() {
	return mapVar.size();
}


void ActRec::addVar(string varName, VarValue val) {
	//cerr<<"addVar "<<varName<<endl;
	mapVar[varName] = val;	
}

VarValue ActRec::getValue(string varName) {
	//cerr<<"getValue() "<<varName<<endl;
	if (mapVar.count(varName)){
		return mapVar[varName];
		//cerr<<"has"<<endl;
	}
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


Function ActRecManager::getFunc(const string &name) {
	try{
		VarValue var = acquireValue(name);
		if (var.getValueType()!=FUNC_TYPE){
			throw Exception(name+"() is not a function.");
		}
		else return var.getFuncValue();
	} catch (Exception e){
		throw Exception("No such a function \""+name+"()\".");
	}
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

void ActRecManager::setVarMember(string varName, string index, VarValue val) {
	VarValue* vp= acquireValuePointer(varName);
	vp->addMember(index,val);
}

void ActRecManager::addVar(string varName, VarValue val) {
	//cerr<<"top().addVar "<<varName<<endl;
	//cerr<<"len = "<<varName.length()<<endl;
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
