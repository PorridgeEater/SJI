#include "function.h"
#include "interpreter.h"
#include "calculator.h"

void func_splitArgList(const string &argList,vector<string> &v){
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

void defineFunction(const string name, const string argList, const string content){
	Function func(name,argList,content);
	actRecManager.addVar(name,VarValue(func));
}

VarValue callFunction(const string name, const string argList){
	//cerr<<"################## callFunction"<<endl;
	Function func = actRecManager.getFunc(name);
	//func.print();
	ActRec ar;
	vector<string> arg;
	func_splitArgList(argList,arg);
	VarValue var;
	for (int i=0;i<func.arg.size();i++)
		ar.addVar(func.arg[i]);
	VarValue argObj = VarValue(Object());
	char tmpName[100];
	for (int i=0;i<arg.size();i++){
		var=getExpResult(arg[i]);
		sprintf(tmpName,"%d",i);
		argObj.addMember(tmpName,var);
		if (i<func.arg.size()){
			ar.addVar(func.arg[i],var);
		}
	}
	ar.addVar("arguments",argObj);
	actRecManager.insertAR(ar);
	VarValue ret;
	try {
		ret = interpreter(func.content);
	} catch (VarValue var){
		//cout << "catch: " << var.toString() << endl;
		actRecManager.deleteAR();
		return var;
	}
	actRecManager.deleteAR();
	return ret;
}
