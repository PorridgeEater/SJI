#include "variable.h"


static const int MIN_INT = 0x80000000;

//  增加一个type，要修改TYPE_MAXNUM、typePair
static const int WRONG_TYPE = -1;
static const int OPERATOR_TYPE = 0;
static const int NUMBER_TYPE = 1;
static const int VARIABLE_TYPE = 2;
static const int FUNCTION_TYPE = 3;
static const int LEFT_BRACKET_TYPE = 4;
static const int RIGHT_BRACKET_TYPE = 5;
//负号的添加
static const int TYPE_MAXNUM = 6;
static const varValue UNDEFINED = (varValue){-1, 0.0, ""};

static const int ITS_NUM = 1;
static const int ITS_OP = 2;


bool isDigit(char c) {
	return c>='0' && c<='9';
}
bool isCharacter(char c) {
	return (c>='a'&&c<='z') || (c>='A'&&c<='Z');
}
bool isOperator(char c) {
	return c=='+' || c=='-' || c=='*' || c=='/';
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
	int nextType();
};

struct NumOrOp {
	int type;
	varValue num;
	char op;
	NumOrOp(varValue a);
	NumOrOp(char c);
};


MyStream::MyStream(string expr):expr(expr) { p=0; }
bool MyStream::hasNext() {
	return p != expr.size();
}
string MyStream::next() {
	string ret = "";

	int type = nextType();
	if (type == WRONG_TYPE) return "";

	if (type == OPERATOR_TYPE
		|| type == LEFT_BRACKET_TYPE
		|| type == RIGHT_BRACKET_TYPE) return ret+=expr[p++];

	if (type == NUMBER_TYPE) {
		for (; p<expr.size() && isDigit(expr[p]); ret+=expr[p++]);
		return ret;
	}

	if (type == FUNCTION_TYPE) {
		int tmp = 0;  bool flag = 0;
		for (; p<expr.size(); ) {
			if (expr[p] == '(') flag = 1, tmp++;
			if (expr[p] == ')') tmp--;
			ret+=expr[p++];
			if (flag && tmp == 0) break;
		}
		return ret;
	}
}
int MyStream::nextType() {
	if (expr[p] == '(') return LEFT_BRACKET_TYPE;
	if (expr[p] == ')') return RIGHT_BRACKET_TYPE;

	/*  如果这一位是数字，那后面跟的肯定是数字  */
	if (isDigit(expr[p])) return NUMBER_TYPE;

	/*  如果这一位是操作符，那这就肯定是操作符  */
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
			else if (isOperator(expr[q])) return VARIABLE_TYPE;
			else if (!isCharacter(expr[q])) return WRONG_TYPE;
		}
		return VARIABLE_TYPE;
	}
	return WRONG_TYPE;
}


NumOrOp::NumOrOp(varValue a) { num = a; type = ITS_NUM; }
NumOrOp::NumOrOp(char c) { op = c; type = ITS_OP; }




static bool typePair[TYPE_MAXNUM][TYPE_MAXNUM] = {  //typePair[preType][type]
	0, 1, 1, 1, 1, 0,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	0, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 1,
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
	if (c == '(') return 0;
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/' || c == '%') return 2;
	if (c == ')') return 3;
	return -1;
}
static int cmpOp(char c1, char c2) {
	return getPd(c1) - getPd(c2);
}

void cal(vector<varValue> &nums, char c) {
	switch (c) {
	case '+':
		//..
		break;
	case '-':
		break;
	case '*':
		break;
	case '/':
		break;
	default:
		break;
	}
}
static varValue calSuffix(const vector<NumOrOp> &suf) {
	vector<varValue> nums;
	for (int i=0; i<suf.size(); i++)
		if (suf[i].type == ITS_NUM) nums.push_back(suf[i].num);
		else cal(nums, suf[i].op);
	return nums[nums.size()-1];  //??
}


/*  用于获取表达式值的函数。若表达式有错会返回UNDEFINED。(没有处理空格)  */
varValue getValue(string expr) {
	// if (expr.size() == 0) {
	// 	ret.valuetype = -1;
	// 	return ret;
	// }
	if (expr.size() == 0) return UNDEFINED;
	vector<NumOrOp> suf;
	vector<char> ops;

	MyStream in = MyStream(expr);
	int preType = MIN_INT;
	while (in.hasNext()) {
		int type = in.nextType();
		if (!isValid(preType, type)) return UNDEFINED;

		if (type == OPERATOR_TYPE) {
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
			suf.push_back(NumOrOp( varValue(stringToDouble(in.next())) ));
		}
		else if (type == VARIABLE_TYPE) {
			suf.push_back(NumOrOp( ActRecManager.acquireValue(in.next()) ));
		}
		else if (type == FUNCTION_TYPE) {
			//要加上f(1)[2]之类情况的判断??
			//suf.push_back(NumOrOp(  ));
		}
		else if (type == LEFT_BRACKET_TYPE) {
			suf.push_back(NumOrOp( getValue(in.next()) ));
		}
		else if (type == RIGHT_BRACKET_TYPE) {
			return UNDEFINED;
		}
		else {
			return UNDEFINED;
		}
	}
	while (ops.size()) suf.push_back(NumOrOp( ops[ops.size()-1] )), ops.pop_back();
	return calSuffix(suf);
}
