#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include "variable.h"
#include "exception.h"
//#include "interpreter.h"

using namespace std;

class Function{
public:
	string name,content;
	vector<string> arg;

	void print();
};

class FunctionList{
//暂时不支持嵌套定义函数，如果把这个类加入到ARmanager当中应该就可以
private:
	vector<Function> list;
public:
	int find(const string &name);
	void add(const Function &func);
	bool get(const string &name,Function &func);
};
extern FunctionList funcList;

void splitArgList(const string &argList,vector<string> &v);

void defineFunction(const string name, const string argList, const string content);

VarValue callFunction(const string name, const string argList);



#endif