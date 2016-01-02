#include "function.h"
#include "interpreter.h"

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

int FunctionList::find(const string &name){
	for (int i=0;i<list.size();i++){
		if (list[i].name==name) return i;
	}
	return -1;
}
void FunctionList::add(const Function &func){
	int t=find(func.name);
	if (t>=0) list[t]=func;
	else list.push_back(func);
}
bool FunctionList::get(const string &name,Function &func){
	int t=find(name);
	if (t>=0){
		func=list[t];
		return true;
	}
	else return false; 
}

FunctionList funcList;

void splitArgList(const string &argList,vector<string> &v){
	char tmp[100];
	int cnt=0;
	for (int i=0,l=argList.length();i<l;i++)
		if (argList[i]!=' ') tmp[cnt++]=argList[i];
	tmp[cnt]='\0';
	string s(tmp);
	for (int i=0,last=-1,l=s.length();i<=l;i++){
		if (i==l || s[i]==','){
			if (i<=last+1) throw Exception("Arguments are wrong.");
			v.push_back(s.substr(last+1,i-last-1));
			last=i;
		}
	}
}

void defineFunction(const string name, const string argList, const string content){
	Function func;
	func.name=name;
	func.content=content;
	splitArgList(argList,func.arg);
	funcList.add(func);
}

VarValue callFunction(const string name, const string argList){
	cerr<<"#### callFunction"<<endl;
	Function func;
	if (!funcList.get(name,func)) throw Exception("No such a function.");
	func.print();
	ActRec ar;
	vector<string> arg;
	splitArgList(argList,arg);
	VarValue var;
	for (int i=0;i<func.arg.size();i++)
		ar.addVar(func.arg[i]);
	for (int i=0;i<arg.size();i++){
		if (i<func.arg.size()){
			var=actRecManager.acquireValue(arg[i]);
			ar.addVar(func.arg[i],var);
		}
		else{
			char tmpName[100];
			sprintf(tmpName,"argument[%d]",i);
			ar.addVar(tmpName,var);
		}
	}
	actRecManager.insertAR(ar);
	VarValue ret = interpreter(func.content);
	actRecManager.deleteAR();
	return ret;
}
