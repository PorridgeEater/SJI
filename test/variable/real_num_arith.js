var intA = 2;
var intB = 5;

console.log("TEST INT + - * / % << >>");
console.log("---------------------------");
console.log(intA + " + " + intB + " = " + (intA+intB));
console.log(intA + " - " + intB + " = " + (intA-intB));
console.log(intA + " * " + intB + " = " + (intA*intB));
console.log(intA + " / " + intB + " = " + (intA/intB));
console.log(intA + " % " + intB + " = " + (intA%intB));
console.log(intA + " << " + intB + " = " + (intA<<intB));
console.log(intA + " >> " + intB + " = " + (intA>>intB));

console.log("+++++++++++++++++++++++++");

var doubleA = 5.3;
var doubleB = 1.3;

console.log("TEST DOUBLE + - * / % << >>");
console.log("---------------------------");
console.log(doubleA + " + " + doubleB + " = " + (doubleA+doubleB));
console.log(doubleA + " - " + doubleB + " = " + (doubleA-doubleB));
console.log(doubleA + " * " + doubleB + " = " + (doubleA*doubleB));
console.log(doubleA + " / " + doubleB + " = " + (doubleA/doubleB));
console.log(doubleA + " % " + doubleB + " = " + (doubleA%doubleB));
console.log(doubleA + " << " + doubleB + " = " + (doubleA<<doubleB));
console.log(doubleA + " >> " + doubleB + " = " + (doubleA>>doubleB));

console.log("+++++++++++++++++++++++++");

var zero = 0;

console.log("TEST divided by 0");
console.log("---------------------------");
console.log(intA + " / " + zero + " = " + (intA/zero));
console.log(zero + " / " + zero + " = " + (zero/zero));
