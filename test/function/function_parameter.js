function f(x){
	x="hello";
}

var a = "abc";
print a;
f(a);
print a;

print "--------------------";

function f(x){
	x["name"]="hello";
}

var a = {
   name:"abc",
   age:28
};

print a;
f(a);
print a;

print "--------------------";

function f(x,y){
	print "x = "+x;
	print "y = "+y;
}

f(233);

print "--------------------";

function f(x){
	print "x = "+x;
	print "arguments[0] = "+arguments[0];
	print "arguments[1] = "+arguments[1];
}

f(233,"hello");
