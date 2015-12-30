#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Function{
	string name,content;
	vector<string> arg;
};

class FunctionList{
//暂时不支持嵌套定义函数，如果把这个类加入到ARmanager当中应该就可以
private:
	vector<Function> list;
public:
	int find(const string &name){
		for (int i=0;i<list.size();i++){
			if (list[i].name==name) return i;
		}
		return -1;
	}
	void add(const Function &func){
		int t=find(func.name);
		if (t>=0) list[t]=func;
		else list.push_back(func);
	}
	bool get(const string &name,Function &func){
		int t=find(name);
		if (t>=0){
			func=list[t];
			return true;
		}
		else return false; 
	}
} funcList;

bool splitArgList(const string &s,vector<string> &v){
	if (s[0]!='(' || s.end()!=')') return false;
	for (int i=1,last=1,l=argList.length();i<l;i++){
		if (s[i]==',' || i==l-1){
			if (i<=last+1) return false;
			v.push_back(s.substr(last+1,i-last-1));
			last=i;
		}
	}
	return true;
}

bool defineFunction(const string name, const string argList, const string content){
	Function func;
	func.name=name;
	func.content=content;
	if (!splitArgList(argList,func.arg))
		return false;
	funcList.add(func);
	return true;
}

bool callFunction(const string name, const string argList, Variable &ret){
	Function func;
	if (!funcList.get(name,func)) return false;
	ActivationRecord ar;
	vector<string> arg;
	if (!splitArgList(argList,arg))
		return false;
	Variable var;
	for (int i=0;i<arg.size();i++){
		if (i<func.arg.size()){
			if (!varManager.top().getValue(arg[i],var))
				return false;
			ar.addVar(func.arg[i],var);
		}
		else{
			String s;
			sprintf(s,"argument[%d]",i);
			ar.addVar(s,var);
		}
	}
	return interpreter(func.content,ar);
	//需要interperter接受到ar之后做一个ARstack.push(ar)的操作
}

int main(){
	freopen("1.js","r",stdin);

	defineFunction();

	return 0;
}