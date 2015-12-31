Interface for SJI
===

## VARIABLE PART
### varValue
```cpp
struct varValue {
	int valuetype;
	// -1:undefined, 0:null, 1:int, 2:double, 3:string
	double num_value;
	string str_value;
};
```

### Activity Record
- class ActRec
	- addVar(string, varValue)
		- void
		- add a variable
			- string is its name
			- varValue is its value
	- getValue(string)
		- return type: varValue
		- get a variable value
			- if none exists, varValue.valuetype = -1

### Activity Record Manager
- class ActRecManager
	- insert(ActRec ar)
	- acquireValue(string varName)
		- return type: varValue
		- get a variable value from activity record pool
			- if none exists, varValue.valuetype = -1
	- delete()
		- return type: bool
		- pop out the last element
			- if empty return false
	- top()
		- return type: ActRec()


Edited by PorridgeEater 2015.12.30

- - - -

## FUNCTION PART(to be continued...)

```cpp
class Function{
	string name,content;
	vector<string> arg;
};
```

```cpp
bool interpreter(string content,ActRecord ar);
```
