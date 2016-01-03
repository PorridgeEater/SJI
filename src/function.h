#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include "variable.h"
#include "exception.h"

using namespace std;

void splitArgList(const string &argList,vector<string> &v);

void defineFunction(const string name, const string argList, const string content);

VarValue callFunction(const string name, const string argList);



#endif