#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "variable.h"
#include "function.h"
#include "calculator.h"
#include "interpreter.h"
#include "exception.h"

int main(int argc, char const *argv[])
{
	/*
	actRecManager.insertAR(ActRec());
	actRecManager.addVar("abc");
	VarValue *vp = actRecManager.acquireValuePointer("abc");
	VarValue x(233);
	*vp=x;
	actRecManager.acquireValue("abc").print();
	actRecManager.deleteAR();
	cerr<<"######################################"<<endl;
	*/
	try{
	    ifstream in("test.js");
	    stringstream buffer;
	    buffer << in.rdbuf();
	    actRecManager.insertAR(ActRec());
	    interpreter(buffer.str());
	    actRecManager.deleteAR();
	} catch (Exception e){
		e.errMessage();
	}
    return 0;
}