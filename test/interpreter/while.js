/*
	test for for-statement
*/
var n = 5;

while (n > 0) {
	for (var i = n; i > 0; i = i - 1) {
		print "i: " + i;
		if (i == 1) {
			break;
		}
	}
	n = n - 1;
}