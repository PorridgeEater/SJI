var strA = "abc";
var strB = "def";
var strC = "5.5";
var strD = "a4c";
var strE = "10";
var strF = ".5";
var strG = "5.";

console.log("TEST STRING + - * / %");
console.log("---------------------------");
console.log(strA + " + " + strB + " = " + (strA+strB));
console.log(strA + " - " + strB + " = " + (strA-strB));
console.log(strA + " * " + strB + " = " + (strA*strB));
console.log(strA + " / " + strB + " = " + (strA/strB));
console.log(strA + " % " + strB + " = " + (strA%strB));

console.log("+++++++++++++++++++++++++");

console.log("TEST NUM STRING with STRING + - * / %");
console.log("---------------------------");
console.log(strC + " + " + strD + " = " + (strC+strD));
console.log(strC + " - " + strD + " = " + (strC-strD));
console.log(strC + " * " + strD + " = " + (strC*strD));
console.log(strC + " / " + strD + " = " + (strC/strD));
console.log(strC + " % " + strD + " = " + (strC%strD));

console.log("+++++++++++++++++++++++++");


console.log("TEST NUM STRING with NUM STRING + - * / %");
console.log("---------------------------");
console.log(strC + " + " + strE + " = " + (strC+strE));
console.log(strC + " - " + strE + " = " + (strC-strE));
console.log(strC + " * " + strE + " = " + (strC*strE));
console.log(strC + " / " + strE + " = " + (strC/strE));
console.log(strC + " % " + strE + " = " + (strC%strE));

console.log("+++++++++++++++++++++++++");

console.log(strE + " - " + strF + " = " + (strE-strF));
console.log(strG + " - " + strF + " = " + (strG-strF));

