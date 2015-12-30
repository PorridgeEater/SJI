#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct varValue {
	int valuetype;			// -1 for undefined, 0 for null, 1 for int, 2 for double, 3 for string
	double num_value;
	string str_value;
};

class ActRec {
public:
	ActRec() {}
	
	void addVar(string varName, varValue val) {
		varMap[varName] = val;
	}
	
	varValue getValue(string varName) {
		varValue tmp;
		tmp.valuetype = -1;
		if (mapVar.count(varName))
			tmp = varMap[varName];
		return tmp;
	}

private:
	map<string, varValue> mapVar;	
};

class ActRecManager {
public:
	void insert(ActRec ar) {
		vecActRec.push_back(ar);
	}

	varValue acquireValue(string varName) {
		int size = vecActRec.size();
		varValue resValue;
		while (size--) {
			varValue = vecActRec[size].getValue(varName);
			if (varValue.valuetype != -1)
				return varValue;
		}
	}

	bool delete() {
		bool res = false;
		if ( vecActRec.size() != 0 ) {
			vecActRec.pop_back();	
			res = true;
		}
		return res;
	}

	ActRec top() {
		return vecActRec[vecActRec.end()];
	}

private:
	vector<ActRec> vecActRec;
};


int main()
{
	// only main..
	return 0;
}