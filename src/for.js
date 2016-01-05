/*
	test for for-statement
*/
var n = 10;

for (var a = 1; a < n; a = a + 1) {
	print "a: " + a;
	for (var i = 0; i < a; i = i + 1) {
		print "i: " + i;
	}
	if (a >= 6) {
		break;
	}
}