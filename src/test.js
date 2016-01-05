var n = 10 ;
var c = 0; /* hhh */
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

switch (n) {
	case 1:
		print "Enter case 1";
		break;
	case 5:
		print "Enter case 5";
	case 10:
		print "Enter case 10";
	default:
		print "Enter default";
		break;
}

for ( var i = 0 ; i < n ; i = i+1 )
{
	print i;
	if (i > 5) {
		break;
	}
}
var i = 0;
while (1) {
	print i;
	if (i > 5) {
		break;
	}
	i = i + 1;
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
