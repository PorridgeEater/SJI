#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>
#include <iostream>
using namespace std;

class Exception{
	string msg;
public:
	Exception(const string &s);
	void errMessage();
};

#endif