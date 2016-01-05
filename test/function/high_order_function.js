function g(){
	function double(x){
		return x*2;
	}
	return double;
}

x = g();
print x(5);
print x(7);

print "----------------";

function g(f){
	print "Inside of g() :";
	f();
}

function func(){
	print "I'm func() from outside.";
}

g(func);