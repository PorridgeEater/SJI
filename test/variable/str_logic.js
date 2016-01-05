var strA = "Bcdf";
var strB = "abc";
var strC = "abc";
var strD = "a4c";
var strE = "10";
var strF = "5";

print("TEST STRING == != < >");
print("---------------------------");
print(strA + " != " + strB + " : " + (strA!=strB));
print(strB + " == " + strC + " : " + (strB==strC));

print(strA + " < " + strB + " : " + (strA<strB));
print("");

print("COMPARE NUM STRING AND NUM STRING");
print("---------------------------");
print(strE + " < " + strF + " : " + (strE < strF));
print("");

var intA = 5;
print("COMPARE NUM STRING AND NUM");
print("---------------------------");
print(strE + " < " + intA + " : " + (strE < intA));
print("");

print("COMPARE STRING AND NUM");
print("---------------------------");
print(strB + " < " + intA + " : " + (strB < intA));
print(strB + " > " + intA + " : " + (strB > intA));
print(strB + " == " + intA + " : " + (strB == intA));



