function f(){
	print "I'm first f().";
}

function g(){
	function f(){
		print "I'm second f().";
	}
	f();
}

f();
g();
f();
