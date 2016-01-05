var intA = 2;
var intB = 5;
var intC = 5;

print("TEST INT == != < <= > >=");
print("---------------------------");
print(intA + " == " + intB + " : " + (intA==intB));
print(intB + " == " + intC + " : " + (intB==intC));
print(intA + " != " + intB + " : " + (intA!=intB));
print(intB + " != " + intC + " : " + (intB!=intC));
print(intA + " < " + intB + " : " + (intA<intB));
print(intB + " < " + intC + " : " + (intB<intC));
print(intA + " <= " + intB + " : " + (intA<=intB));
print(intB + " <= " + intC + " : " + (intB<=intC));
print(intA + " > " + intB + " : " + (intA>intB));
print(intB + " > " + intC + " : " + (intB>intC));
print(intA + " >= " + intB + " : " + (intA>=intB));
print(intB + " >= " + intC + " : " + (intB>=intC));

print("+++++++++++++++++++++++++");

var doubleA = 5.0;
var doubleB = 5.000;

print("TEST == between int and double");
print(intB + " == " + doubleA + " : " + (intB==doubleA));
print(intB + " == " + doubleB + " : " + (intB==doubleB));