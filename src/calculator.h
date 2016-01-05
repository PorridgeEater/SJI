/*  没法测试，所以就先写这么多了  */
/*  
	TODO:
		a++;
		a=a+1;  //??
		-a; !a;
		&&
		?:  //应该要用递归来做


	可以实现的：
		单目
		,
		?:
		
		括号内暂时不能有带有括号的字符串

*/


#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__


#include <vector>
#include "variable.h"
#include "variable.h"

bool isDigit(char c);
bool isCharacter(char c);
double stringToDouble(string s);

VarValue getExpResult(string expr);

#endif
