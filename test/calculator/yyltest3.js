

b = function() {
	print "haha";
	return 1;
};
a = function() {
	b();
	return b;
};
// print a();
// print a+1;

