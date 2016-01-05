#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
static const int ITS_MEMBERVAR = 3;




struct Operator {
	static const int MAX_SIZE = 3;

	char t[MAX_SIZE];
	int size;
	Operator() { size=0; }
	Operator(char c) { t[0]=c; size=1; }
	Operator(char a, char b) { t[0]=a; t[1]=b; size=2; }
	Operator(string s) {
		if (s.size()>MAX_SIZE) throw Exception("Unknown operator " + s + ".");  //assert(s.size()<=MAX_SIZE);
		size = s.size();
		for (int i=0; i<size; i++) t[i] = s[i];
	}
	Operator(const char s[]) {
		for (int &i=size=0; s[i]; i++) {
			if (i==MAX_SIZE) {
				t[i]=0;
				throw Exception("Unknown operator " + string(t) + ".");
			}
			t[i] = s[i];
		}
	}
	operator string() {
		string ret="";
		for (int i=0; i<size; i++) ret+=t[i];
		return ret;
	}
	char &operator[](int d) { assert(d<size); return t[d]; }
	const char &operator[](int d) const { assert(d<size); return t[d]; }
	bool operator==(const Operator &a) const {
		if (size != a.size) return 0;
		bool flag=0;
		for (int i=0; i<size; i++)
			if (t[i] != a[i]) return 0;
		return 1;
	}
	bool operator!=(const Operator &a) const {
		return !(*this==a);
	}
};
ostream &operator<<(ostream &out, const Operator &t) {
	for (int i=0; i<t.size; i++)
		out<<t[i];
	return out;
}





bool isDigit(char c) {
	return c>='0' && c<='9';
}
bool isCharacter(char c) {
	return (c>='a'&&c<='z') || (c>='A'&&c<='Z');
}
bool isOperator(Operator op) {
	return (op =='+' || op =='-' || op =='*' || op =='/' || op =='%'
		|| op =="<<" || op ==">>"
		|| op =='<' || op =="<=" || op =='>' || op ==">="
		|| op =="==" || op =="!="
		|| op =='=' || op =="+=" || op =="-=" || op =="*=" || op =="/=" || op =="%=" || op =="<<=" || op ==">>="
		|| op =='.'
		);
}
bool isSpace(char c) {
	return c==' ' || c=='\t' || c=='\n';
}
double stringToDouble(string s) {  //只支持十进制，不支持负数
	double ret = 0.0;
	for (int i=0; i<s.size(); i++) ret = ret*10 + s[i]-'0';
	return ret;
}
bool isLeftBracket(char c) {
	return c=='[' || c=='{';
}
bool isRightBracket(char c) {
	return c==']' || c=='}';
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
	string nextVar();
	string nextExpr(char left, char right);
	void nextColon();
	void nextComma(char right);
	Object nextObject();
	Object nextArray();
};

struct NumOrOp {
	int type;
	VarValue num;
	VarValue *var;
	Operator op;
	string name;
	NumOrOp(VarValue a):num(a), type(ITS_NUM) {}
	NumOrOp(VarValue *a):var(a), type(ITS_VAR), num(*a) {}
	NumOrOp(Operator c):op(c), type(ITS_OP), num(UNDEFINED) {}
	NumOrOp(string s):name(s),type(ITS_MEMBERVAR) {}

};
ostream &operator<<(ostream &out, NumOrOp t) {
	if (t.type == ITS_NUM) return (t.num).print(), out;
	if (t.type == ITS_VAR) return (*t.var).print(), out;
	if (t.type == ITS_MEMBERVAR) return out<<t.name<<endl;
	return out<<t.op<<endl;
}
ostream &operator<<(ostream &out, vector<Operator> t) {
	out<<"----------------------------------vector<Operator>:  Start.\n";
	for (auto tt : t) out<<string(tt)<<endl;
	out<<"----------------------------------vector<Operator>:  End.\n";
	return out;
}
ostream &operator<<(ostream &out, vector<NumOrOp> t) {
	out<<"----------------------------------vector<NumOrOp>:  Start.\n";
	for (auto tt : t) out<<tt<<endl;
	out<<"----------------------------------vector<NumOrOp>:  End.\n";
	return out;
}


MyStream::MyStream(string expr):expr(expr), p(0) {}
bool MyStream::hasNext() {
	while (p < expr.size() && isSpace(expr[p])) p++;
	return p != expr.size();// && expr[p] != ';';
}
string MyStream::next() {
	hasNext();

	string ret = "";

	int type = nextType();
	if (type == WRONG_TYPE) return ret+=expr[p++];

	if (type == OPERATOR_TYPE && (p<expr.size()-1 && isOperator(Operator(expr[p], expr[p+1])))) {
		ret=ret+expr[p]+expr[p+1];
		p+=2;
		return ret;
	}
	if (type == OPERATOR_TYPE
		|| type == LEFT_BRACKET_TYPE
		|| type == RIGHT_BRACKET_TYPE) return ret+=expr[p++];

	if (type == NUMBER_TYPE) {
		int tmp = 0;
		for (; p<expr.size() && (isDigit(expr[p]) || expr[p]=='.'); ret+=expr[p++]) {
			if (expr[p] == '.') tmp++;
			if (tmp > 1) throw Exception("next: Unexpected token: .");
		}
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
		int _t = 0;
		for (int q=p; q<expr.size(); q++) {
			if (expr[q] == '(') { _t = 1; break; }
			if (expr[q] == '[') { _t = 2; break; }
		}

		bool ins0 = 0, ins1 = 0;
		if (_t == 1) {
			ret += "1 ";

			int tmp = 0;  bool flag = 0;
			for (; p<expr.size(); ) {
				if (expr[p] == '\"') {
					if (ins0) ins0 = 0;
					else if (!ins1) ins0 = 1;
				}
				if (expr[p] == '\'') {
					if (ins1) ins1 = 0;
					else if (!ins0) ins1 = 1;
				}
				if (ins0 || ins1) { ret+=expr[p++]; continue; }  //如果在字符串内，那么直接加上这个字符就好

				if (expr[p] == '(') flag = 1, tmp++, ret+=" ", p++;
				else if (expr[p] == ')') tmp--, p++;
				else ret+=expr[p++];
				if (flag && tmp == 0) break;
			}
		}
		else {
			ret += "2 ";

			int tmp = 0;  bool flag = 0;
			for (; p<expr.size(); ) {
				if (expr[p] == '\"') {
					if (ins0) ins0 = 0;
					else if (!ins1) ins0 = 1;
				}
				if (expr[p] == '\'') {
					if (ins1) ins1 = 0;
					else if (!ins0) ins1 = 1;
				}
				if (ins0 || ins1) { ret+=expr[p++]; continue; }  //如果在字符串内，那么直接加上这个字符就好

				if (expr[p] == '[') flag = 1, tmp++, ret+=" ", p++;
				else if (expr[p] == ']') tmp--, p++;
				else ret+=expr[p++];
				if (flag && tmp == 0) break;
			}
		}
		return ret;
	}

	if (type == VARIABLE_TYPE) {
		for (; p<expr.size() && (isCharacter(expr[p]) || isDigit(expr[p])); ret+=expr[p++]);
		return ret;
	}
	return "";
}
int MyStream::nextType() {
	if (expr[p] == '(' || expr[p] == '{' || expr[p] == '[') return LEFT_BRACKET_TYPE;
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
	if (p<expr.size()-1 && isOperator(Operator(expr[p], expr[p+1]))) return OPERATOR_TYPE;  //先判断两个字符的运算符
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
			else if (expr[q] == '[') {
				int tmp = 1;
				for (q++; q<expr.size(); q++) {
					if (expr[q] == '[') tmp++;
					if (expr[q] == ']') tmp--;
					if (tmp == 0) return FUNCTION_TYPE;
				}
				return WRONG_TYPE;
			}
			else if (isOperator(expr[q]) || isSpace(expr[q]) || expr[q]==')') return VARIABLE_TYPE;
			// else if (!isCharacter(expr[q]) && !isDigit(expr[q])) return WRONG_TYPE;
			else if (!isCharacter(expr[q]) && !isDigit(expr[q])) return VARIABLE_TYPE;
		}
		return VARIABLE_TYPE;
	}
	return WRONG_TYPE;
}

void MyStream::nextColon() {
	for (; p<expr.size() && expr[p]!=':'; p++)
		if (!isSpace(expr[p])) throw Exception((string)"nextColon1: Unexpected token: " + expr[p]);
	if (expr[p]==':') p++;
	else throw Exception((string)"nextColon2: Unexpected token: " + expr[p]);
}
void MyStream::nextComma(char right) {
	for (; p<expr.size() && expr[p]!=',' && expr[p]!=right; p++)
		if (!isSpace(expr[p])) throw Exception((string)"nextComma1: Unexpected token: " + expr[p]);
	if (expr[p] == ',') p++;
	else if (expr[p] == right) ;
	else throw Exception((string)"nextComma2: Unexpected token: " + expr[p]);
}
string MyStream::nextVar() {
	string ret = "";
	for (; p<expr.size() && (isCharacter(expr[p]) || isDigit(expr[p])); ret+=expr[p++]);
	return ret;
}
string MyStream::nextExpr(char left, char right) {
	bool ins0 = 0, ins1 = 0;
	vector<char> bracket; bracket.push_back(left);
	int judge[256][256] = {0}; memset(judge,0,sizeof(judge));
	judge['['][']'] = judge['{']['}'] = 1;
	judge['[']['}'] = judge['{'][']'] = -1;

	string ret = "";

	for (; p<expr.size(); ) {
		if (expr[p] == '\"') {
			if (ins0) ins0 = 0;
			else if (!ins1) ins0 = 1;
		}
		if (expr[p] == '\'') {
			if (ins1) ins1 = 0;
			else if (!ins0) ins1 = 1;
		}
		if (ins0 || ins1) { ret+=expr[p++]; continue; }  //如果在字符串内，那么直接加上这个字符就好

		if (isRightBracket(expr[p])) {
			switch (judge[bracket[bracket.size()-1]][expr[p]]) {
				case -1: throw Exception("Unmatched brackets."); break;
				case 0: bracket.push_back(expr[p]); break;
				case 1: bracket.pop_back(); break;
				default: break;
			}
		}
		if (isLeftBracket(expr[p]))
			bracket.push_back(expr[p]);
		if (expr[p] == ',' && bracket.size() == 1) return ret;
		if (expr[p] == right && bracket.size() == 0) return ret;
		// if (expr[p] == ',' || (expr[p] == right && bracket.size()==0)) return ret;
		ret+=expr[p++];
	}
	hasNext();
	if (expr[p]!=right) throw Exception((string)"nextExpr: Unexpected token: " + ret+expr[p]+expr);
	if (bracket.size()>0) throw Exception((string)"Uncaught SyntaxError");
	return ret;
}
Object MyStream::nextObject() {
	if (expr[p] != '{') throw Exception((string)"Object definition failed.");
	next();
	Object ret;
	while (hasNext() && _next() != "}") {
		// cout<<nextType()<<endl;
		// cout<<"type="<<(nextType())<<" "<<expr[p]<<" "<<_next()<<endl;
		if (nextType() != VARIABLE_TYPE) throw Exception("nextObject: Unexpected token: " + next() + ".");
		string var = nextVar();
		nextColon();
		ret.addMember(var, getExpResult(nextExpr('{','}')));
		nextComma('}');
	}
	if (!hasNext() || _next() != "}") throw Exception("\"}\" Expected.");
	next();
	// VarValue(ret).print();
	// VarValue(ret)["name"]->print();
	return ret;
}
Object MyStream::nextArray() {
	if (expr[p] != '[') throw Exception((string)"Array definition failed.");
	next();
	Object ret;
	for (int i=0; hasNext() && _next() != "]"; i++) {
		if (nextType() != VARIABLE_TYPE && nextType() != NUMBER_TYPE && nextType() != STRING_TYPE2 && nextType() != FUNCTION_TYPE && nextType() != LEFT_BRACKET_TYPE)
			throw Exception("nextArray: Unexpected token: " + next() + ".");

		stringstream ss; ss<<i; string var; ss>>var;
		ret.addMember(var, getExpResult(nextExpr('[',']')));
		nextComma(']');
	}
	if (!hasNext() || _next() != "]") throw Exception("\"]\" Expected.");
	next();
	// VarValue(ret).print();
	// VarValue(ret)["name"]->print();
	return ret;
}
string MyStream::_next() {
	int _p = p;
	string s = next();
	p = _p;
	return s;
}





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

int getPd(Operator op) {
	if (op == '(') return -100;  //这是必要的...
	if (op == '=' || op == "+=" || op == "-=" || op == "*=" || op == "/=" || op == "%=" || op == "<<=" || op == ">>=") return -14;
	if (op == "==" || op == "!=") return -7;
	if (op == '<' || op =="<=" || op =='>' || op ==">=") return -6;
	if (op == "<<" || op == ">>") return -5;
	if (op == '+' || op == '-') return -4;
	if (op == '*' || op == '/' || op == '%') return -3;
	if (op == '.') return -1;
	if (op == ')') return 0;  //这是必要的...
	return -1;
}
static int cmpOp(Operator c1, Operator c2) {
	return getPd(c1) - getPd(c2);
}

void cal(vector<NumOrOp> &nums, Operator ch) {
	NumOrOp _b = nums[nums.size()-1]; VarValue *pb = nums[nums.size()-1].var, b = nums[nums.size()-1].num; nums.pop_back();
	NumOrOp _a = nums[nums.size()-1]; VarValue *pa = nums[nums.size()-1].var, a = nums[nums.size()-1].num; nums.pop_back();
	// a.print(); cout<<a.getStrValue().size()<<endl; cout<<ch<<endl; b.print(); cout<<b.getStrValue().size()<<endl; cout<<endl;
	VarValue c;

	if (ch == ".") {
		if (_a.type == ITS_VAR) nums.push_back( (*pa)[_b.name] );
		else					nums.push_back( a[_b.name] );
	}
	else {
		if (ch == '+') c=a+b;
		else if (ch == "-") c=a-b;
		else if (ch == "*") c=a*b;
		else if (ch == "/") c=a/b;
		else if (ch == "%") c=a%b;
		else if (ch == "<") c=a<b;
		else if (ch == "<=") c=a<=b;
		else if (ch == ">") c=a>b;
		else if (ch == ">=") c=a>=b;
		else if (ch == "<<") c=a<<b;
		else if (ch == ">>") c=a>>b;
		else if (ch == "==") c=(a==b);
		else if (ch == "!=") c=(a!=b);
		else if (ch == "=" || ch == "+=" || ch == "-=" || ch == "*=" || ch == "/=" || ch == "%=") {
			if (_a.type != ITS_VAR)
				throw Exception("Invalid left-hand side in assignment.");
			if (ch == "=") c=(*pa=b);
			else if (ch == "+=") c=(*pa+=b);
			else if (ch == "-=") c=(*pa-=b);
			else if (ch == "*=") c=(*pa*=b);
			else if (ch == "/=") c=(*pa/=b);
			else if (ch == "%=") c=(*pa%=b);
			else if (ch == "<<=") c=(*pa<<=b);
			else if (ch == ">>=") c=(*pa>>=b);
		}
		else throw Exception("Unknown operator: " + (string)ch);
		nums.push_back(c);
		// c.print(); cout<<c.getStrValue().size()<<endl; cout<<endl<<endl;
	}
}
static VarValue calSuffix(const vector<NumOrOp> &suf) {
	vector<NumOrOp> nums;
	for (int i=0; i<suf.size(); i++)
		if (suf[i].type == ITS_NUM || suf[i].type == ITS_VAR || suf[i].type == ITS_MEMBERVAR)  //
			nums.push_back(suf[i]);
		else {
			try {
				cal(nums, suf[i].op);
			} catch (Exception e) {
				nums.push_back(VarValue(string("NaN")));
			}
		}
	if (nums.size() > 1) throw Exception("More than one result value.");// assert(nums.size() == 1);
	if (nums.size() == 0) return UNDEFINED;  //表达式为空
	return ITS_VAR ? *nums[nums.size()-1].var : nums[nums.size()-1].num;
}


/*  用于获取表达式值的函数。若表达式有错会返回UNDEFINED。(没有处理空格)  */
VarValue getExpResult(string expr) {
	vector<NumOrOp> suf;
	// vector<char> ops;
	vector<Operator> ops;

	MyStream in = MyStream(expr);
	if (!in.hasNext()) return UNDEFINED;  //表达式为空，则返回UNDEFINED

	{
		int d = expr.find("=");
		// cout<<expr<<" haha1"<<endl;
		if (in.nextType() == VARIABLE_TYPE) {
		in.next();
		string s = in.next();
		if (Operator("=") == s) {
			string s1 = expr.substr(0, d), s2 = expr.substr(d+1, expr.size()-d-1);
			if (s1.find("[") != string::npos) {
				//nothing
			}
			else {
				actRecManager.setVar(s1=MyStream(s1).next(), getExpResult(s2));
				return *actRecManager.acquireValuePointer(s1);
			}
		}
		}
		in = MyStream(expr);
		// cout<<expr<<" haha2\n";
	}


	int type, preType = MIN_INT;
	for (; in.hasNext(); preType=type) {
		type = in.nextType();
		// cout<<"haha"<<endl;
		// cout<<"type="<<type<<" preType="<<preType<<" | "<<in._next()<<endl;
		if (!isValid(preType, type)) throw Exception("getExpResult: Unexpected token: " + in.next());  //表达式有问题

		if (type == LEFT_BRACKET_TYPE && in._next() == "{") {
			suf.push_back(NumOrOp( VarValue(in.nextObject()) ));
		}
		else if (type == LEFT_BRACKET_TYPE && in._next() == "[") {
			suf.push_back(NumOrOp( VarValue(in.nextArray(), 1) ));
		}
		else if (type == OPERATOR_TYPE || type == LEFT_BRACKET_TYPE || type == RIGHT_BRACKET_TYPE) {
			Operator c = in.next();
			// cout<<"\n\n!!!!!!!!!! (1)"<<ops<<" operator is "<<c<<endl;
			if (ops.size() == 0 || c == '(') ops.push_back(c);
			else {
				Operator c0 = ops[ops.size()-1];
				if (c0 == '(' && c==')') ops.pop_back();
				else if (c0 == '(') ops.push_back(c);
				else if (c == ')') {
					for (; ops[ops.size()-1]!='('; suf.push_back(NumOrOp( ops[ops.size()-1] )), ops.pop_back()) ;
						// puts("haha");
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

			if (c == ".") {
				if ((type=in.nextType()) != VARIABLE_TYPE)
					throw Exception("getExpResult: '.': Unexpected token: " + in.next());
				suf.push_back(NumOrOp( in.next() ));
				// cout<<suf<<" haha\n"<<ops<<endl;
			}
			// cout<<"\n\n!!!!!!!!!! (2)"<<ops<<endl;
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
			string s = in.next();
			int _t = s[0]-48; s=s.substr(2, s.size()-2);
			int d = s.find(" ");
			string name = s.substr(0, d), arglist = s.substr(d, s.size()-d);
			if (_t == 1) {
				suf.push_back(NumOrOp( callFunction(name, arglist) ));
			}
			else {
				// (*actRecManager.acquireValuePointer(name)).print();
				// cout<<name<<" "<<arglist<<" "<<getExpResult(arglist).toString()<<endl;
				suf.push_back(NumOrOp( (*actRecManager.acquireValuePointer(name))[ getExpResult(arglist).toString() ] ));
				// cout<<name<<" "<<arglist<<" "<<getExpResult(arglist).toString()<<endl;
			}
		}
		else {  /*  未知错误  */
			throw Exception("Unknown error.");
			return UNDEFINED;
		}
	}

	while (ops.size()) suf.push_back(NumOrOp( ops[ops.size()-1] )), ops.pop_back();
	// if (expr.find('i') !=string::npos) cout<<"!!!!!!!---------!!!!!!!"<<calSuffix(suf)<<endl;
	// suf[0].num.print();
	// if (expr.find("[")!=string::npos) {
	// 	cout<<expr<<" haha "<<suf.size()<<endl;
	// 	suf[0].var->print();
	// 	suf[2].var->print();
	// 	calSuffix(suf).print();
	// }
	return calSuffix(suf);
}
