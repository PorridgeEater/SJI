function f(a) {
	return 2;
}

a = [1, "1", f(1), {a:1, b:"1", c:f(1)}];
b = [a, 1];
a = [a, b];
// b = [b, a];
// a = [a, b];
print a;




