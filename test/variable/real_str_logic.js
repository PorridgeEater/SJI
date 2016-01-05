var strA = "Bcdf";
var strB = "abc";
var strC = "abc";
var strD = "a4c";
var strE = "10";
var strF = "5";

console.log("TEST STRING == != < >");
console.log("---------------------------");
console.log(strA + " != " + strB + " : " + (strA!=strB));
console.log(strB + " == " + strC + " : " + (strB==strC));

console.log(strA + " < " + strB + " : " + (strA<strB));
console.log("");

console.log("COMPARE NUM STRING AND NUM STRING");
console.log("---------------------------");
console.log(strE + " < " + strF + " : " + (strE < strF));
console.log("");

var intA = 5;
console.log("COMPARE NUM STRING AND NUM");
console.log("---------------------------");
console.log(strE + " < " + intA + " : " + (strE < intA));
console.log("");

console.log("COMPARE STRING AND NUM");
console.log("---------------------------");
console.log(strB + " < " + intA + " : " + (strB < intA));
console.log(strB + " > " + intA + " : " + (strB > intA));
console.log(strB + " == " + intA + " : " + (strB == intA));



