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
    ifstream in("test.js");
    stringstream buffer;
    buffer << in.rdbuf();
    actRecManager.insertAR(ActRec());
    interpreter(buffer.str());
    actRecManager.deleteAR();
    return 0;
}