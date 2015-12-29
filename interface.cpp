//变量部分

class Value{
	int type;
	//** something about value
};

class Function{
	string name,content;
	vector<string> arg;
};

class ActRecord{
private:
	varHashTable<VarName,Value>;
	funcHashTable<FuncName,Function>;
public:
	Value getValue(string name);
	void addVar(string name,Value val);
};

class ActManager{
private:
	stack<ActRecord>;
public:
	void push(ActRecord);
	bool pop(ActRecord);
	ActRecord top();
};

bool interpreter(string content,ActRecord ar);