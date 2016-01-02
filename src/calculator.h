/*  没法测试，所以就先写这么多了  */
/*  
	TODO:
		a++;
		a=a+1;
		-a;
*/


#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__


#include <vector>
#include "variable.h"
#include "variable.h"

bool isDigit(char c);
bool isCharacter(char c);
bool isOperator(char c);
double stringToDouble(string s);

varValue getValue(string expr);

#endif
