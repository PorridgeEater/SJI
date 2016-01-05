var n = 10 ;
var c = 0; /* hhh
var a = c<n;
print c<n;
print a; // 23333333
/*
	hahahsdfasdfasdfasdfsdf
*/
// hhhhh
//d = 1;
var e;

print n;
var str="---------I'm a string--------------";
print str;
print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

function f(){
	print "first f()";
}

function g(){
	function f(){
		print "second f()";
	}
	f();
}
f();
g();
f();

function f(x){
	print x;
}
f(12345);

b=1;
if ((b == 1)) {
	print b;
}
function add(a, b)
{
	return a + b;
}

if ( add(a,b)) {
	c = 1;	
}
else {
	a = 1;
}

var n = 10 ;

for ( var i = 0 ; i < n ; i = i+1 )
{
	c = c + 1;
}

while (n) {
	print n;
	n = n - 1;
}

a = b;
e = add(b, c);

print a;
print b;
print c;
print n;
print e;
print add(a,b);
