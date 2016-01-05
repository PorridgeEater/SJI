var strA = "abc";
var strB = "def";
var strC = "5.5";
var strD = "a4c";
var strE = "10";
var strF = ".5";
var strG = "5.";

print("TEST STRING + - * / %");
print("---------------------------");
print(strA + " + " + strB + " = " + (strA+strB));
print(strA + " - " + strB + " = " + (strA-strB));
print(strA + " * " + strB + " = " + (strA*strB));
print(strA + " / " + strB + " = " + (strA/strB));
print(strA + " % " + strB + " = " + (strA%strB));

print("+++++++++++++++++++++++++");

print("TEST NUM STRING + - * / %");
print("---------------------------");
print(strC + " + " + strD + " = " + (strC+strD));
print(strC + " - " + strD + " = " + (strC-strD));
print(strC + " * " + strD + " = " + (strC*strD));
print(strC + " / " + strD + " = " + (strC/strD));
print(strC + " % " + strD + " = " + (strC%strD));

print("+++++++++++++++++++++++++");

print("TEST NUM STRING with NUM STRING + - * / %");
print("---------------------------");
print(strC + " + " + strE + " = " + (strC+strE));
print(strC + " - " + strE + " = " + (strC-strE));
print(strC + " * " + strE + " = " + (strC*strE));
print(strC + " / " + strE + " = " + (strC/strE));
print(strC + " % " + strE + " = " + (strC%strE));

print("+++++++++++++++++++++++++");

print(strE + " - " + strF + " = " + (strE-strF));
print(strG + " - " + strF + " = " + (strG-strF));

