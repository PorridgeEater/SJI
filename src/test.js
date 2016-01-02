var a = 0 ;
var b = 1 ;
var c = 2 ;
d = 1;

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

print a;
print b;
print c;
print n;
print i;
print d;
print add(a,b);
