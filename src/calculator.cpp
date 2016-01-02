#include <cassert>
#include <cstdio>
#include <cstdlib>
#include "variable.h"
#include "function.h"
#include "calculator.h"
#include "exception.h"
#define dbg(x) cout<<#x<<" "<<x<<endl


extern ActRecManager actRecManager;



static const int MIN_INT = 0x80000000;

//  增加一个operator，要修改isOperator、getPd、cal
//  增加一个type，要修改TYPE_MAXNUM、typePair、nextType、next
static const int WRONG_TYPE = -1;
static const int OPERATOR_TYPE = 0;
static const int NUMBER_TYPE = 1;
static const int VARIABLE_TYPE = 2;
static const int FUNCTION_TYPE = 3;
static const int LEFT_BRACKET_TYPE = 4;
static const int RIGHT_BRACKET_TYPE = 5;
static const int STRING_TYPE2 = 6;
//负号的添加
static const int TYPE_MAXNUM = 7;
const VarValue UNDEFINED;// = (VarValue){-1, 0.0, ""};  //??

static const int ITS_VAR = 0;
static const int ITS_NUM = 1;
static const int ITS_OP = 2;


bool isDigit(char c) {
	return c>='0' && c<='9';
}
bool isCharacter(char c) {
	return (c>='a'&&c<='z') || (c>='A'&&c<='Z');
}
bool isOperator(char c) {
	return c=='+' || c=='-' || c=='*' || c=='/' || c=='%' || c=='=';
}
bool isSpace(char c) {
	return c==' ' || c=='\t';
}
double stringToDouble(string s) {  //只支持十进制，不支持负数
	double ret = 0.0;
	for (int i=0; i<s.size(); i++) ret = ret*10 + s[i]-'0';
	return ret;
}


struct MyStream {
	string expr;
	int p;
	MyStream(string expr);
	bool hasNext();
	string next();
	string _next();
	int nextType();
	bool hasExtraExp();
};

struct NumOrOp {
	int type;
	VarValue num;
	VarValue *var;
	char op;
	NumOrOp(VarValue a);
	NumOrOp(VarValue *a);
	NumOrOp(char c);
};
ostream &operator<<(ostream &out, NumOrOp t) {
	if (t.type == ITS_NUM) return out<<(t.num).getIntValue()<<endl;
	return out<<t.op<<endl;
}


MyStream::MyStream(string expr):expr(expr), p(0) {}
bool MyStream::hasNext() {
	while (p < expr.size() && expr[p] == ' ') p++;
	return p != expr.size();// && expr[p] != ';';
}
string MyStream::next() {
	string ret = "";

	int type = nextType();
	if (type == WRONG_TYPE) return "";

	if (type == OPERATOR_TYPE
		|| type == LEFT_BRACKET_TYPE
		|| type == RIGHT_BRACKET_TYPE) return ret+=expr[p++];

	if (type == NUMBER_TYPE) {
		for (; p<expr.size() && (isDigit(expr[p]) || expr[p]=='.'); ret+=expr[p++]);
		return ret;
	}
	if (type == STRING_TYPE2) {
		if (expr[p] == '\"') {  //"..."
			for (p++; p<expr.size();) {
				if (expr[p] == '\"' && expr[p-1] != '\\') break;
				ret += expr[p++];
			}
			p++;
		}
		else {  //'...'
			for (p++; p<expr.size();) {
				if (expr[p] == '\'' && expr[p-1] != '\\') break;
				ret += expr[p++];
			}
			p++;
		}
		return ret;
	}

	if (type == FUNCTION_TYPE) {
		int tmp = 0;  bool flag = 0;
		for (; p<expr.size(); ) {
			if (expr[p] == '(') flag = 1, tmp++, ret+=" ", p++;
			else if (expr[p] == ')') tmp--, p++;
			else ret+=expr[p++];
			if (flag && tmp == 0) break;
		}
		return ret;
	}

	if (type == VARIABLE_TYPE) {
		for (; p<expr.size() && (isCharacter(expr[p]) || isDigit(expr[p])); ret+=expr[p++]);
		return ret;
	}
}
int MyStream::nextType() {
	if (expr[p] == '(') return LEFT_BRACKET_TYPE;
	if (expr[p] == ')') return RIGHT_BRACKET_TYPE;

	/*  字符串  */
	if (expr[p] == '\"') {
		for (int q=p+1; q<expr.size(); q++)
			if (expr[q] == '\"' && expr[q-1] != '\\') return STRING_TYPE2;
		return WRONG_TYPE;
	}
	if (expr[p] == '\'') {
		for (int q=p+1; q<expr.size(); q++)
			if (expr[q] == '\'' && expr[q-1] != '\\') return STRING_TYPE2;
		return WRONG_TYPE;
	}

	/*  如果这一位是数字，那后面跟的可能是整形或浮点型  */
	if (isDigit(expr[p])) {
		int dotNum = 0;
		for (int q=p+1; q<expr.size(); q++)
			if (!isDigit(expr[q]))
				if (expr[q] == '.') dotNum++;
				else break;
		if (dotNum > 1) return WRONG_TYPE;
		return NUMBER_TYPE;
	}

	/*  如果这一位是操作符，那这就肯定是操作符  */  //非单字符操作符??
	if (isOperator(expr[p])) return OPERATOR_TYPE;

	/*  如果这一位是字符，那后面跟的可能是函数或变量  */
	if (isCharacter(expr[p])) {
		for (int q=p+1; q<expr.size(); q++) {
			if (expr[q] == '(') {
				int tmp = 1;
				for (q++; q<expr.size(); q++) {
					if (expr[q] == '(') tmp++;
					if (expr[q] == ')') tmp--;
					if (tmp == 0) return FUNCTION_TYPE;
				}
				return WRONG_TYPE;
			}
			else if (isOperator(expr[q]) || isSpace(expr[q]) || expr[q]==')') return VARIABLE_TYPE;
			else if (!isCharacter(expr[q]) && !isDigit(expr[q])) return WRONG_TYPE;
		}
		return VARIABLE_TYPE;
	}
	return WRONG_TYPE;
}
bool MyStream::hasExtraExp() {
	while (p < expr.size() && expr[p] == ' ') p++;
	// if (p < expr.size() && expr[p] == ';') {
	// 	p++;
	// 	while (p < expr.size() && expr[p] == ' ') p++;
	// }
	return p != expr.size();
}
string MyStream::_next() {
	int _p = p;
	string s = next();
	p = _p;
	return s;
}


NumOrOp::NumOrOp(VarValue a):num(a), type(ITS_NUM) {}
NumOrOp::NumOrOp(VarValue *a):var(a), type(ITS_VAR), num(*a) {}
NumOrOp::NumOrOp(char c):op(c), type(ITS_OP), num(UNDEFINED) {}




static bool typePair[TYPE_MAXNUM][TYPE_MAXNUM] = {  //typePair[preType][type]
	0, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 1, 0,
	1, 0, 0, 0, 0, 1, 0,
	1, 0, 0, 0, 0, 1, 0,
	0, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 1, 0,
	1, 0, 0, 0, 0, 1, 0,
};
//TODO [FUNCTION_TYPE][LEFT_BRACKET_TYPE]可能需要加上特判
//TODO [...][LEFT_BRACKET_TYPE]可能需要加上特判
//TODO [RIGHT_BRACKET_TYPE][...]可能需要加上特判

static bool isValid(int preType, int type) {
	if (type == WRONG_TYPE) return 0;
	if (preType == MIN_INT) return 1;
	return typePair[preType][type];
}

int getPd(char c) {
	// if (c == '(') return -1;
	if (c == '=') return 0;
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/' || c == '%') return 2;
	// if (c == ')') return 3;
	return -1;
}
static int cmpOp(char c1, char c2) {
	return getPd(c1) - getPd(c2);
}

// void cal(vector<VarValue> &nums, char ch) {
// 	VarValue b = nums[nums.size()-1]; nums.pop_back();
// 	VarValue a = nums[nums.size()-1]; nums.pop_back();
// 	// a.print(); cout<<a.getStrValue().size()<<endl; cout<<ch<<endl; b.print(); cout<<b.getStrValue().size()<<endl; cout<<endl;
// 	VarValue c;
// 	switch (ch) {
// 	case '+': c=a+b; break;
// 	case '-': c=a-b; break;
// 	case '*': c=a*b; break;
// 	case '/': c=a/b; break;
// 	case '%': c=a%b; break;
// 	default: break;
// 	}
// 	nums.push_back(c);
// 	// c.print(); cout<<c.getStrValue().size()<<endl; cout<<endl<<endl;
// }
// static VarValue calSuffix(const vector<NumOrOp> &suf) {
// 	vector<VarValue> nums;
// 	for (int i=0; i<suf.size(); i++)
// 		if (suf[i].type == ITS_NUM) nums.push_back(suf[i].num);
// 		else cal(nums, suf[i].op);
// 	assert(nums.size() == 1);
// 	return nums[nums.size()-1];
// }
void cal(vector<NumOrOp> &nums, char ch) {
	NumOrOp _b = nums[nums.size()-1]; VarValue *pb = nums[nums.size()-1].var, b = nums[nums.size()-1].num; nums.pop_back();
	NumOrOp _a = nums[nums.size()-1]; VarValue *pa = nums[nums.size()-1].var, a = nums[nums.size()-1].num; nums.pop_back();
	// a.print(); cout<<a.getStrValue().size()<<endl; cout<<ch<<endl; b.print(); cout<<b.getStrValue().size()<<endl; cout<<endl;
	VarValue c;
	switch (ch) {
	case '+': c=a+b; break;
	case '-': c=a-b; break;
	case '*': c=a*b; break;
	case '/': c=a/b; break;
	case '%': c=a%b; break;
	case '=':
		if (_a.type != ITS_VAR)
			throw Exception("Invalid left-hand side in assignment.");
		c=(*pa=b); break; //TODO 加上赋值
	default: break;
	}
	nums.push_back(c);
	// c.print(); cout<<c.getStrValue().size()<<endl; cout<<endl<<endl;
}
static VarValue calSuffix(const vector<NumOrOp> &suf) {
	vector<NumOrOp> nums;
	for (int i=0; i<suf.size(); i++)
		if (suf[i].type == ITS_NUM || suf[i].type == ITS_VAR) nums.push_back(suf[i]);
		else cal(nums, suf[i].op);
	throw Exception("More than one result value.");// assert(nums.size() == 1);
	return ITS_VAR ? *nums[nums.size()-1].var : nums[nums.size()-1].num;
}


/*  用于获取表达式值的函数。若表达式有错会返回UNDEFINED。(没有处理空格)  */
VarValue getExpResult(string expr) {
	// if (expr.size() == 0) {
	// 	ret.valuetype = -1;
	// 	return ret;
	// }

	// puts("!!!!!!!!!!!!!");
	// cout<<expr<<endl;

	if (expr.size() == 0) return UNDEFINED;  //表达式为空，则返回UNDEFINED
	vector<NumOrOp> suf;
	vector<char> ops;

	MyStream in = MyStream(expr);
	int type, preType = MIN_INT;
	for (; in.hasNext(); preType=type) {
		type = in.nextType();
		// cout<<"haha"<<endl;
		// cout<<"type="<<type<<" preType="<<preType<<" | "<<in._next()<<endl;
		if (!isValid(preType, type)) throw Exception("Unexpected token: " + string(in.next()));  //表达式有问题

		if (type == OPERATOR_TYPE || type == LEFT_BRACKET_TYPE || type == RIGHT_BRACKET_TYPE) {
			char c = in.next()[0];
			if (ops.size() == 0 || c == '(') ops.push_back(c);
			else {
				char c0 = ops[ops.size()-1];
				if (c0 == '(' && c==')') ops.pop_back();
				else if (c0 == '(') ops.push_back(c);
				else if (c == ')') {
					for (; ops[ops.size()-1]!='('; suf.push_back(NumOrOp( ops[ops.size()-1] )), ops.pop_back()) ;
					ops.pop_back();
				}
				else {
					while (cmpOp(c, ops[ops.size()-1]) <= 0) {  //c应该在ops[ops.size()-1]后面执行
						suf.push_back(NumOrOp( ops[ops.size()-1] ));  ops.pop_back();
						if (ops.size() == 0) break;
					}
					ops.push_back(c);
				}
			}
		}
		else if (type == NUMBER_TYPE) {
			string s = in.next();
			if (s.find('.') != string::npos) {  //double
				double num = atof(s.c_str());
				suf.push_back(NumOrOp( VarValue(num) ));
			}
			else {  //int
				int num = atoi(s.c_str());
				suf.push_back(NumOrOp( VarValue(num) ));
			}
		}
		else if (type == STRING_TYPE2) {
			suf.push_back(NumOrOp( VarValue(in.next()) ));
		}
		else if (type == VARIABLE_TYPE) {
			// puts("haha");
			// suf.push_back(NumOrOp( actRecManager.acquireValue(in.next()) ));
			suf.push_back(NumOrOp( actRecManager.acquireValuePointer(in.next()) ));
			// puts("haha");
		}
		else if (type == FUNCTION_TYPE) {
			//TODO 异常处理

			//要加上f(1)[2]之类情况的判断??
			string s = in.next();
			int d = s.find(" ");
			string name = s.substr(0, d), arglist = s.substr(d, s.size()-d);
			suf.push_back(NumOrOp( callFunction(name, arglist) ));
		}
		// else if (type == LEFT_BRACKET_TYPE) {
		// 	suf.push_back(NumOrOp( getExpResult(in.next()) ));
		// }
		// else if (type == RIGHT_BRACKET_TYPE) {  /*  前面没有左括号却有了右括号，错误  */
		// 	return UNDEFINED;
		// }
		else {  /*  未知错误  */
			throw Exception("Unknown error.");
			return UNDEFINED;
		}
	}
	// puts("Ready to cal");
	if (in.hasExtraExp()) throw Exception("Extra expression");  /*  分号后面还有表达式，错误  */

	// puts("Start to cal");

	while (ops.size()) suf.push_back(NumOrOp( ops[ops.size()-1] )), ops.pop_back();
	// suf[0].num.print();
	// calSuffix(suf).print();
	return calSuffix(suf);
}
