var intA = 2;
var intB = 5;
var intC = 5;

console.log("TEST INT == != < <= > >=");
console.log("---------------------------");
console.log(intA + " == " + intB + " : " + (intA==intB));
console.log(intB + " == " + intC + " : " + (intB==intC));
console.log(intA + " != " + intB + " : " + (intA!=intB));
console.log(intB + " != " + intC + " : " + (intB!=intC));
console.log(intA + " < " + intB + " : " + (intA<intB));
console.log(intB + " < " + intC + " : " + (intB<intC));
console.log(intA + " <= " + intB + " : " + (intA<=intB));
console.log(intB + " <= " + intC + " : " + (intB<=intC));
console.log(intA + " > " + intB + " : " + (intA>intB));
console.log(intB + " > " + intC + " : " + (intB>intC));
console.log(intA + " >= " + intB + " : " + (intA>=intB));
console.log(intB + " >= " + intC + " : " + (intB>=intC));

console.log("+++++++++++++++++++++++++");

var doubleA = 5.0;
var doubleB = 5.000;

console.log("TEST == between int and double");
console.log(intB + " == " + doubleA + " : " + (intB==doubleA));
console.log(intB + " == " + doubleB + " : " + (intB==doubleB));