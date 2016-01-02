#include "variable.h"
#include "calculator.h"
#include "function.h"

// //variable test
// int main()
// {
// 	string queryName;
// 	ActRec testAR1;
// 	ActRec testAR2;
// 	ActRec testAR3;

// 	VarValue testvv1(5);
// 	VarValue testvv2("hello");
// 	VarValue testvv3(2.5);

// 	VarValue testvv4(10);
// 	VarValue testvv5(" world");
// 	VarValue testvv6(7.5);

// 	VarValue receivevv;

// 	ActRecManager testARM;

// 	// test var calculation
	
// 	// test +

// 		// test int + int
// 	cout << "TEST INT + INT" << endl;
// 	receivevv = testvv1 + testvv4;
// 	receivevv.print();
// 		// test int + double
// 	cout << "TEST INT + DOUBLE" << endl;
// 	receivevv = testvv1 + testvv3;
// 	receivevv.print();
// 		// test int + string
// 	cout << "TEST INT + STRING" << endl;
// 	receivevv = testvv1 + testvv2;
// 	receivevv.print();
// 		// test double + int
// 	cout << "TEST DOUBLE + INT" << endl;
// 	receivevv = testvv3 + testvv4;
// 	receivevv.print();
// 		// test double + double
// 	cout << "TEST DOUBLE + DOUBLE" << endl;
// 	receivevv = testvv3 + testvv6;
// 	receivevv.print();
// 		// test double + string
// 	cout << "TEST DOUBLE + STRING" << endl;
// 	receivevv = testvv3 + testvv5;
// 	receivevv.print();
// 		// test string + int
// 	cout << "TEST STRING + INT" << endl;
// 	receivevv = testvv2 + testvv4;
// 	receivevv.print();
// 		// test string + double
// 	cout << "TEST STRING + DOUBLE" << endl;
// 	receivevv = testvv5 + testvv6;
// 	receivevv.print();
// 		// test string + string
// 	cout << "TEST STRING + STRING" << endl;
// 	receivevv = testvv2 + testvv5;
// 	receivevv.print();

// 	cout << endl << "------------------------" << endl << endl;

// 	// test -

// 		// test int - int
// 	cout << "TEST INT - INT" << endl;
// 	receivevv = testvv1 - testvv4;
// 	receivevv.print();
// 		// test int - double
// 	cout << "TEST INT - DOUBLE" << endl;
// 	receivevv = testvv1 - testvv3;
// 	receivevv.print();
// 		// test int - string
// 	cout << "TEST INT - STRING" << endl;
// 	receivevv = testvv1 - testvv2;
// 	receivevv.print();
// 		// test double - int
// 	cout << "TEST DOUBLE - INT" << endl;
// 	receivevv = testvv3 - testvv4;
// 	receivevv.print();
// 		// test double - double
// 	cout << "TEST DOUBLE - DOUBLE" << endl;
// 	receivevv = testvv3 - testvv6;
// 	receivevv.print();
// 		// test double - string
// 	cout << "TEST DOUBLE - STRING" << endl;
// 	receivevv = testvv3 - testvv5;
// 	receivevv.print();
// 		// test string - int
// 	cout << "TEST STRING - INT" << endl;
// 	receivevv = testvv2 - testvv4;
// 	receivevv.print();
// 		// test string - double
// 	cout << "TEST STRING - DOUBLE" << endl;
// 	receivevv = testvv5 - testvv6;
// 	receivevv.print();
// 		// test string - string
// 	cout << "TEST STRING - STRING" << endl;
// 	receivevv = testvv2 - testvv5;
// 	receivevv.print();

// 	cout << endl << "------------------------" << endl << endl;

// 	// test *

// 		// test int * int
// 	cout << "TEST INT * INT" << endl;
// 	receivevv = testvv1 * testvv4;
// 	receivevv.print();
// 		// test int * double
// 	cout << "TEST INT * DOUBLE" << endl;
// 	receivevv = testvv1 * testvv3;
// 	receivevv.print();
// 		// test int * string
// 	cout << "TEST INT * STRING" << endl;
// 	receivevv = testvv1 * testvv2;
// 	receivevv.print();
// 		// test double * int
// 	cout << "TEST DOUBLE * INT" << endl;
// 	receivevv = testvv3 * testvv4;
// 	receivevv.print();
// 		// test double * double
// 	cout << "TEST DOUBLE * DOUBLE" << endl;
// 	receivevv = testvv3 * testvv6;
// 	receivevv.print();
// 		// test double * string
// 	cout << "TEST DOUBLE * STRING" << endl;
// 	receivevv = testvv3 * testvv5;
// 	receivevv.print();
// 		// test string * int
// 	cout << "TEST STRING * INT" << endl;
// 	receivevv = testvv2 * testvv4;
// 	receivevv.print();
// 		// test string * double
// 	cout << "TEST STRING * DOUBLE" << endl;
// 	receivevv = testvv5 * testvv6;
// 	receivevv.print();
// 		// test string * string
// 	cout << "TEST STRING * STRING" << endl;
// 	receivevv = testvv2 * testvv5;
// 	receivevv.print();

// 	cout << endl << "------------------------" << endl << endl;

// 	// test /

// 		// test int / int
// 	cout << "TEST INT / INT" << endl;
// 	receivevv = testvv1 / testvv4;
// 	receivevv.print();
// 		// test int / double
// 	cout << "TEST INT / DOUBLE" << endl;
// 	receivevv = testvv1 / testvv3;
// 	receivevv.print();
// 		// test int / string
// 	cout << "TEST INT / STRING" << endl;
// 	receivevv = testvv1 / testvv2;
// 	receivevv.print();
// 		// test double / int
// 	cout << "TEST DOUBLE / INT" << endl;
// 	receivevv = testvv3 / testvv4;
// 	receivevv.print();
// 		// test double / double
// 	cout << "TEST DOUBLE / DOUBLE" << endl;
// 	receivevv = testvv3 / testvv6;
// 	receivevv.print();
// 		// test double / string
// 	cout << "TEST DOUBLE / STRING" << endl;
// 	receivevv = testvv3 / testvv5;
// 	receivevv.print();
// 		// test string / int
// 	cout << "TEST STRING / INT" << endl;
// 	receivevv = testvv2 / testvv4;
// 	receivevv.print();
// 		// test string / double
// 	cout << "TEST STRING / DOUBLE" << endl;
// 	receivevv = testvv5 / testvv6;
// 	receivevv.print();
// 		// test string / string
// 	cout << "TEST STRING / STRING" << endl;
// 	receivevv = testvv2 / testvv5;
// 	receivevv.print();

// 	cout << endl << "------------------------" << endl << endl;

// 	// test %

// 		// test int % int
// 	cout << "TEST INT \% INT" << endl;
// 	receivevv = testvv1 % testvv4;
// 	receivevv.print();
// 		// test int % double
// 	cout << "TEST INT \% DOUBLE" << endl;
// 	receivevv = testvv1 % testvv3;
// 	receivevv.print();
// 		// test int % string
// 	cout << "TEST INT \% STRING" << endl;
// 	receivevv = testvv1 % testvv2;
// 	receivevv.print();
// 		// test double / int
// 	cout << "TEST DOUBLE \% INT" << endl;
// 	receivevv = testvv3 % testvv4;
// 	receivevv.print();
// 		// test double / double
// 	cout << "TEST DOUBLE \% DOUBLE" << endl;
// 	receivevv = testvv6 % testvv3;
// 	receivevv.print();
// 		// test double / string
// 	cout << "TEST DOUBLE \% STRING" << endl;
// 	receivevv = testvv3 % testvv5;
// 	receivevv.print();
// 		// test string / int
// 	cout << "TEST STRING \% INT" << endl;
// 	receivevv = testvv2 % testvv4;
// 	receivevv.print();
// 		// test string / double
// 	cout << "TEST STRING \% DOUBLE" << endl;
// 	receivevv = testvv5 % testvv6;
// 	receivevv.print();
// 		// test string / string
// 	cout << "TEST STRING \% STRING" << endl;
// 	receivevv = testvv2 % testvv5;
// 	receivevv.print();

// 	cout << endl << "------------------------" << endl << endl;

// 	(VarValue("abc") + VarValue(" ") + VarValue("b")).print();

// /*
// 	// test addVar func, success!
// 	testAR1.addVar("testvar", testvv1);
// 	testAR1.addVar("testvar2", testvv2);
// 	testAR2.addVar("testvar", testvv1);
// 	testAR2.addVar("testvar2", testvv2);
// 	cout << "TEST ADDVAR" << endl;
// 	cout << "AR1's size = " << testAR1.getSize() << endl;
// 	cout << "AR2's size = " << testAR2.getSize() << endl;
// 	cout << endl;

// 	// test getValue with exist varName, success!	
// 	cout << "TEST GETVALUE" << endl;
// 	queryName = "testvar";
// 	receivevv = testAR1.getValue(queryName);
// 	cout << "query for AR1's " << queryName << endl;
// 	cout << "valuetype = " << receivevv.getValueType() << endl;
// 	cout << "value = " << receivevv.getIntValue() << endl;
// 	queryName = "testvar2";
// 	receivevv = testAR1.getValue(queryName);
// 	cout << "query for AR1's " << queryName << endl;
// 	cout << "valuetype = " << receivevv.getValueType() << endl;
// 	cout << "value = " << receivevv.getStrValue() << endl;
// 	cout << endl;

// 	// test add the same name var, will update the value, success!
// 	queryName = "testvar";
// 	testAR1.addVar(queryName, testvv3);
// 	receivevv = testAR1.getValue(queryName);
// 	cout << "TEST UPDATE VALUE" << endl;
// 	cout << "update for AR1's " << queryName << endl;
// 	cout << "valuetype = " << receivevv.getValueType() << endl;
// 	cout << "value = " << receivevv.getDoubleValue() << endl;
// 	cout << endl;

// 	// test getValue with non-exist varName, success!
// 	// non-exist var will return valuetype -1
// 	receivevv = testAR1.getValue("undefine");
// 	cout << "TEST GET NON-EXIST VALUE" << endl;
// 	cout << "valuetype = " << receivevv.getValueType() << endl;
// 	cout << endl;

// 	cout << "----------------------------" << endl << endl;

// 	// test inserting an activity record, success!
// 	// testAR1(double 2.15 | string hello)
// 	// testAR2(int 5 | string hello)
// 	testARM.insertAR(testAR1);
// 	testARM.insertAR(testAR2);
// 	cout << "TEST INSERT AN ACTIVITY RECORD" << endl;
// 	cout << "stack size = " << testARM.getSize() << endl;
// 	cout << endl;

// 	// test acquire the value through name in ARManager, success!
// 	// we can find that it get the value from the stack top AR
// 	receivevv = testARM.acquireValue("testvar");
// 	cout << "TEST GET VALUE IN ActRecManager" << endl;
// 	cout << "valuetype = " << receivevv.getValueType() << endl;
// 	cout << "value = " << receivevv.getIntValue() << endl;
// 	cout << endl;

// 	// test add a variable in the top Activity Record
// 	cout << "top size = " << testARM.top().getSize() << endl;
// 	testARM.addVar("testvar3", testvv3);
// 	cout << "top size = " << testARM.top().getSize() << endl;

// 	// now the testAR2 will have values (testvar int 5 | testvar2 string hello | testvar3 double 2.15)
// 	receivevv = testARM.acquireValue("testvar3");
// 	cout << "TEST ADD VARIABLE IN THE TOP AR" << endl;
	
// 	cout << "valuetype = " << receivevv.getValueType() << endl;
// 	cout << "value = " << receivevv.getDoubleValue() << endl;
// 	cout << endl;

// 	// test delete the top activity record, success!
// 	testARM.deleteAR();
// 	cout << "TEST POP THE ACTIVITY RECORD STACK" << endl;
// 	cout << "stack size = " << testARM.getSize() << endl;
// */	


// 	return 0;
// }

//calculator test

extern ActRecManager actRecManager;
int main() {
	//getExpResult("1+1.0/2").print();
	//getExpResult("20*(10/3+1)%79").print();

	// getExpResult("\"haha\" + \" \" + \'c\' + \" \" + 123").print();
	//(VarValue("1234") + VarValue("aaa bbb ccc") + VarValue("a")).print();


	/*  变量的测试  */
	// VarValue testvv1(5);
	// VarValue testvv2("hello");
	// VarValue testvv3(2.5);
	// ActRec testAR1;
	// testAR1.addVar("testvar", testvv1);
	// testAR1.addVar("testvar2", testvv2);
	// testAR1.addVar("testvar3", testvv3);
	// // cout << "TEST ADDVAR" << endl;
	// // cout << "AR1's size = " << testAR1.getSize() << endl;
	// // cout << endl;
	// actRecManager.insertAR(testAR1);


	// getExpResult("  testvar + (\' \' + testvar2) + \' \' + (1/2*6%2 + testvar3)  ").print();

	// getExpResult(" 0.0 ").print();

	//TODO  函数的测试
	return 0;
}