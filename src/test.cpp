#include "variable.h"
#include "calculator.h"

/*  //variable test
int main()
{
	string queryName;
	ActRec testAR1;
	ActRec testAR2;
	ActRec testAR3;

	varValue testvv1;
	varValue testvv2;
	varValue testvv3;
	varValue receivevv;

	ActRecManager testARM;

	testvv1.valuetype = 1;
	testvv1.num_value = 5;
	testvv2.valuetype = 3;
	testvv2.str_value = "hello";
	testvv3.valuetype = 2;
	testvv3.num_value = 2.15;

	// test addVar func, success!
	testAR1.addVar("testvar", testvv1);
	testAR1.addVar("testvar2", testvv2);
	testAR2.addVar("testvar", testvv1);
	testAR2.addVar("testvar2", testvv2);
	cout << "TEST ADDVAR" << endl;
	cout << "AR1's size = " << testAR1.getSize() << endl;
	cout << "AR2's size = " << testAR2.getSize() << endl;
	cout << endl;

	// test getValue with exist varName, success!	
	cout << "TEST GETVALUE" << endl;
	queryName = "testvar";
	receivevv = testAR1.getValue(queryName);
	cout << "query for AR1's " << queryName << endl;
	cout << "valuetype = " << receivevv.valuetype << endl;
	cout << "value = " << receivevv.num_value << endl;
	queryName = "testvar2";
	receivevv = testAR1.getValue(queryName);
	cout << "query for AR1's " << queryName << endl;
	cout << "valuetype = " << receivevv.valuetype << endl;
	cout << "value = " << receivevv.str_value << endl;
	cout << endl;

	// test add the same name var, will update the value, success!
	queryName = "testvar";
	testAR1.addVar(queryName, testvv3);
	receivevv = testAR1.getValue(queryName);
	cout << "TEST UPDATE VALUE" << endl;
	cout << "update for AR1's " << queryName << endl;
	cout << "valuetype = " << receivevv.valuetype << endl;
	cout << "value = " << receivevv.num_value << endl;
	cout << endl;

	// test getValue with non-exist varName, success!
	// non-exist var will return valuetype -1
	receivevv = testAR1.getValue("undefine");
	cout << "TEST GET NON-EXIST VALUE" << endl;
	cout << "valuetype = " << receivevv.valuetype << endl;
	cout << endl;

	cout << "----------------------------" << endl << endl;

	// test inserting an activity record, success!
	// testAR1(double 2.15 | string hello)
	// testAR2(int 5 | string hello)
	testARM.insertAR(testAR1);
	testARM.insertAR(testAR2);
	cout << "TEST INSERT AN ACTIVITY RECORD" << endl;
	cout << "stack size = " << testARM.getSize() << endl;
	cout << endl;

	// test acquire the value through name in ARManager, success!
	// we can find that it get the value from the stack top AR
	receivevv = testARM.acquireValue("testvar");
	cout << "TEST GET VALUE IN ActRecManager" << endl;
	cout << "valuetype = " << receivevv.valuetype << endl;
	cout << "value = " << receivevv.num_value << endl;
	cout << endl;

	// test add a variable in the top Activity Record
	cout << "top size = " << testARM.top().getSize() << endl;
	testARM.addVar("testvar3", testvv3);
	cout << "top size = " << testARM.top().getSize() << endl;

	// now the testAR2 will have values (testvar int 5 | testvar2 string hello | testvar3 double 2.15)
	receivevv = testARM.acquireValue("testvar3");
	cout << "TEST ADD VARIABLE IN THE TOP AR" << endl;
	
	cout << "valuetype = " << receivevv.valuetype << endl;
	cout << "value = " << receivevv.num_value << endl;
	cout << endl;

	// test delete the top activity record, success!
	testARM.deleteAR();
	cout << "TEST POP THE ACTIVITY RECORD STACK" << endl;
	cout << "stack size = " << testARM.getSize() << endl;
	
	return 0;
}
*/


int main() {
}