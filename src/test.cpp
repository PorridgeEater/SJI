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

/* test == success! */

	// VarValue int_a(5);
	// VarValue int_b(5);
	// VarValue int_c(6);
	// VarValue int_d(10);

	// VarValue double_a(5.12);
	// VarValue double_b(5.12);
	// VarValue double_c(6.23);
	// VarValue double_d(10.00);

	// VarValue str_a("abc");
	// VarValue str_b("abc");
	// VarValue str_c("5");
	// VarValue str_d("5.00");
	// VarValue str_e("5.12");
	// 	// INT == INT
	// cout << "INT == INT" << endl;
	// cout << (int_a == int_b) << endl;
	// cout << (int_a == int_c) << endl;
	// 	// INT == DOUBLE
	// cout << "INT == DOUBLE" << endl;
	// cout << (int_a == double_a) << endl;
	// cout << (int_d == double_d) << endl;
	// 	// INT == STRING
	// cout << "INT == STRING" << endl;
	// cout << (int_a == str_a) << endl;		
	// cout << (int_a == str_c) << endl;
	// cout << (int_a == str_d) << endl;
	// 	// DOUBLE == DOUBLE
	// cout << "DOUBLE == DOUBLE" << endl;
	// cout << (double_a == double_b) << endl;
	// cout << (double_a == double_c) << endl;
	// 	// DOUBLE == STRING
	// cout << "DOUBLE == STRING" << endl;
	// cout << (double_a == str_d) << endl;
	// cout << (double_a == str_e) << endl;
	// 	// STRING == STRING
	// cout << "STRING == STRING" << endl;
	// cout << (str_a == str_b) << endl;
	// cout << (str_a == str_c) << endl;
	// cout << (str_c == str_d) << endl;


/* test < success! */

	// VarValue int_a(5);
	// VarValue int_b(5);
	// VarValue int_c(6);
	// VarValue int_d(10);

	// VarValue double_a(5.12);
	// VarValue double_b(5.12);
	// VarValue double_c(6.23);
	// VarValue double_d(10.00);

	// VarValue str_a("abc");
	// VarValue str_b("abc");
	// VarValue str_c("5");
	// VarValue str_d("5.00");
	// VarValue str_e("10.12");
	// VarValue str_f("abcdef");
	// VarValue str_g("bcd");
	// 	// INT == INT
	// cout << "INT < INT" << endl;
	// cout << (int_a < int_b) << endl;
	// cout << (int_a < int_c) << endl;
	// 	// INT < DOUBLE
	// cout << "INT < DOUBLE" << endl;
	// cout << (int_a < double_a) << endl;
	// cout << (int_d < double_d) << endl;
	// 	// INT < STRING
	// cout << "INT < STRING" << endl;
	// cout << (int_a < str_a) << endl;		
	// cout << (int_a < str_c) << endl;
	// cout << (int_a < str_e) << endl;
	// 	// DOUBLE < DOUBLE
	// cout << "DOUBLE < DOUBLE" << endl;
	// cout << (double_a < double_b) << endl;
	// cout << (double_a < double_c) << endl;
	// 	// DOUBLE < STRING
	// cout << "DOUBLE < STRING" << endl;
	// cout << (double_a < str_d) << endl;
	// cout << (double_a < str_e) << endl;
	// 	// STRING < STRING
	// cout << "STRING < STRING" << endl;
	// cout << (str_a < str_b) << endl;
	// cout << (str_a < str_c) << endl;
	// cout << (str_c < str_d) << endl;
	// cout << (str_f < str_g) << endl;


	/* test > success! */
/*
	VarValue int_a(5);
	VarValue int_b(4);
	VarValue int_c(6);
	VarValue int_d(10);

	VarValue double_a(5.12);
	VarValue double_b(5.12);
	VarValue double_c(6.23);
	VarValue double_d(10.00);


	VarValue str_a("abc");
	VarValue str_b("abc");
	VarValue str_c("5");
	VarValue str_d("5.00");
	VarValue str_e("5.12");
	VarValue str_f("d");

		// INT > INT
	cout << "INT > INT" << endl;
	cout << (int_a > int_b) << endl;
	cout << (int_a > int_c) << endl;
		// INT > DOUBLE
	cout << "INT > DOUBLE" << endl;
	cout << (int_c > double_a) << endl;
	cout << (int_d > double_d) << endl;
		// INT > STRING
	cout << "INT > STRING" << endl;
	cout << (int_a > str_a) << endl;		
	cout << (int_a > str_c) << endl;
	cout << (int_d > str_d) << endl;
		// DOUBLE > DOUBLE
	cout << "DOUBLE > DOUBLE" << endl;
	cout << (double_a > double_b) << endl;
	cout << (double_d > double_a) << endl;
		// DOUBLE > STRING
	cout << "DOUBLE > STRING" << endl;
	cout << (double_a > str_d) << endl;
	cout << (double_a > str_e) << endl;
		// STRING > STRING
	cout << "STRING > STRING" << endl;
	cout << (str_a > str_b) << endl;
	cout << (str_a > str_c) << endl;
	cout << (str_c > str_d) << endl;
	cout << (str_a > str_f) << endl;
*/


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


	// // getExpResult("  testvar + (\' \' + testvar2) + \' \' + (1/2*6%2 + testvar3)  ").print();
	// // getExpResult("  testvar  ").print();
	// getExpResult("  testvar = testvar2  ").print();
	// getExpResult("  testvar = testvar + (\' \' + testvar2) + \' \' + (1/2*6%2 + testvar3)  ").print();
	// getExpResult("  testvar  ").print();

	// getExpResult(" 0.0 ").print();
	// getExpResult(" 1 > 0 ;").print();


	// fix local scope variable bug
	// VarValue testvv1(5);
	// VarValue testvv2(2.5);	
	// VarValue testvv3("hello");
	// VarValue testvv4("world");
	// VarValue receivevv;

	// ActRec testAR1;
	// ActRec testAR2;
	// ActRec testAR3;

	// ActRecManager testARM;

	// testAR1.addVar("testvar", testvv1);
	// testAR1.addVar("testvar2", testvv2);
	// testAR1.addVar("testvar3", testvv3);
	// testAR2.addVar("testvar", testvv1);
	// testAR2.addVar("testvar2", testvv2);

	// testARM.insertAR(testAR1);
	// testARM.insertAR(testAR2);

/*
	// test add a variable in the top Activity Record
	cout << "top size = " << testARM.top().getSize() << endl;
	testARM.addVar("testvar3", testvv3);
	cout << "top size = " << testARM.top().getSize() << endl;

	receivevv = testARM.acquireValue("testvar3");
	cout << "TEST ADD VARIABLE IN THE TOP AR" << endl;
	receivevv.print();
	cout << endl;
*/                                                        

	// cout << "top size = " << testARM.top().getSize() << endl;
	// testARM.setVar("testvar3", testvv4);
	// cout << "top size = " << testARM.top().getSize() << endl;

	// receivevv = testARM.acquireValue("testvar3");
	// cout << "TEST ADD VARIABLE IN THE TOP AR" << endl;
	// receivevv.print();
	// cout << endl;	

	// getExpResult("  1+ 1 ").print();
	// getExpResult("n = 1");
	return 0;
}