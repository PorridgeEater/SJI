var intA = 2;
var intB = 5;

print("TEST INT + - * / % << >>");
print("---------------------------");
print(intA + " + " + intB + " = " + (intA+intB));
print(intA + " - " + intB + " = " + (intA-intB));
print(intA + " * " + intB + " = " + (intA*intB));
print(intA + " / " + intB + " = " + (intA/intB));
print(intA + " % " + intB + " = " + (intA%intB));
print(intA + " << " + intB + " = " + (intA<<intB));
print(intA + " >> " + intB + " = " + (intA>>intB));

print("+++++++++++++++++++++++++");

var doubleA = 5.3;
var doubleB = 1.3;

print("TEST DOUBLE + - * / % << >>");
print("---------------------------");
print(doubleA + " + " + doubleB + " = " + (doubleA+doubleB));
print(doubleA + " - " + doubleB + " = " + (doubleA-doubleB));
print(doubleA + " * " + doubleB + " = " + (doubleA*doubleB));
print(doubleA + " / " + doubleB + " = " + (doubleA/doubleB));
print(doubleA + " % " + doubleB + " = " + (doubleA%doubleB));
print(doubleA + " << " + doubleB + " = " + (doubleA<<doubleB));
print(doubleA + " >> " + doubleB + " = " + (doubleA>>doubleB));

print("+++++++++++++++++++++++++");

var zero = 0;

print("TEST divided by 0");
print("---------------------------");
print(intA + " / " + zero + " = " + (intA/zero));
print(zero + " / " + zero + " = " + (zero/zero));