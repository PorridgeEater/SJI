function f(x) {
	print "x: " + x;

	if (x==0) {
		return 1;
	}
	if (x==1) {
		return 1;
	}
	return f(x-1)+f(x-2);
}

print f(5);