#include "interpreter.h"

static string getContent(string s, int &p, char left, char right)
{
    while (p < s.length() && (s[p] == ' ' || s[p] == '\n' || s[p] == 9)) {
        p++;
    }
    if (p > s.length()) {
        cout << "Can't find " << left << endl;
        return "";
    }
    if (s[p] != left) {
        cout << "s[p]: " << s[p] << endl;
        
        printf("Error: Not find %c!\n", left);
        return "";
    }
    int count = 1;
    string condition = "";
    while (count && p < s.length()) {
        p++;
        if (s[p] == right) {
            count--;
            if (count > 0) {
                condition += s[p];
            }
        }
        else if (s[p] == left) {
            count++;
            condition += s[p];
        }
        else {
            condition += s[p];
        }
    }
    if (p++ >= s.length()) {
        printf("Error: Brackets mismatched!");
        return "";
    }
    return condition;
}

static string getKey(string code, int &p)
{
    if (p >= code.length()) {
        return "";
    }
    string key = "";
    while (p < code.length() && ((code[p] == ' ') || (code[p] == '\n') || (code[p] == 9))) {
        p++;
    }
    if (p >= code.length()) {
        return "";
    }
    key += code[p++];
    if (code[p] == '{' || code[p] == '}') {
        return key;
    }
    while (p < code.length() &&
           ( (code[p] >= 'a' && code[p] <= 'z') ||
             (code[p] >= 'A' && code[p] <= 'Z') ||
             (code[p] >= '0' && code[p] <= '9') ||
             code[p] == '_'))
    {
        key += code[p++];
    }
    if (p >= code.length()) {
        cout << "Syntax Error!2" << endl;
        return "";
    }
    return key;
}

static void ifStatement(string condition, string content, string others) {
    // cout << condition << " " << content << endl;
    actRecManager.insertAR(ActRec());
    VarValue result = getExpResult(condition);
    if (result.toBool()) {
        interpreter(content);
    }
    else {
        interpreter(others);
    }
    actRecManager.deleteAR();
}

static void whileStatement(string condition, string content) {
    actRecManager.insertAR(ActRec());
    VarValue result = getExpResult(condition);
    while (result.toBool()) {
        actRecManager.insertAR(ActRec());
        interpreter(content);
        actRecManager.deleteAR();
        result = getExpResult(condition);
    }
    actRecManager.deleteAR();
}

static void forStatement(string condition, string content) {
    actRecManager.insertAR(ActRec());
    int p = 0, newVar = 0;
    string key = getKey(condition, p);
    if (key == "var") {
        key = getKey(condition, p);
        newVar = 1;
    }
    while (p < condition.length() && condition[p++] != ';') {}
    string init = condition.substr(0, p);
    
    if (p >= condition.length()) {
        cout << "Syntax Error in for statement!" << endl;
        return;
    }
    
    int q = p;
    while (p < condition.length() && condition[p++] != ';') {}
    string cond = condition.substr(q, p-q-2);
    
    if (p >= condition.length()) {
        cout << "Syntax Error in for statement!" << endl;
        return;
    }
    
    int t = p;
    string iter = condition.substr(t, condition.length()-t) + ";";
    
    
    cout << "init:" << init << endl;
    cout << "cond:" << cond << endl;
    cout << "iter:" << iter << endl;
    
    interpreter(init);
    cout << condition << endl;
    VarValue result = getExpResult(cond);
    while (result.toBool()) {
        actRecManager.insertAR(ActRec());
        interpreter(content);
        interpreter(iter);
        actRecManager.deleteAR();
        result = getExpResult(cond);
    }
    
    actRecManager.deleteAR();
}

VarValue interpreter(string code)
{
    //cout << content << endl;
    int pos = 0;
    while (pos < code.length()) {
        // cout << pos << " " << code.length() << endl;
        string e = getKey(code, pos);
        if (e == "") {
            break;
        }
        cout << "Key: " << e  << "  Pos: " << pos << endl;
        //cout << code.substr(pos, code.length() - pos);
        if (e == "{") { }
        else if (e == "}") { }
        if (e == "if") {
            string condition = getContent(code, pos, '(', ')');
            string content = getContent(code, pos, '{', '}');
            
            cout << "condition: " << condition << endl;
            cout << "content: " << content << endl;
            
            int old = pos;
            string others = getKey(code, pos);
            if (others == "else") {
                cout << "Key: else" << endl;
                string otherContent = "";
                while (pos < code.length() && code[pos] != '{') {
                    otherContent += code[pos++];
                }
                otherContent += '{';
                otherContent += getContent(code, pos, '{', '}');
                otherContent += '}';
                ifStatement(condition, content, otherContent);
            }
            else {
                pos = old;
                ifStatement(condition, content, "");
            }
        }
        else if (e == "while") {
            string condition = getContent(code, pos, '(', ')');
            string content = getContent(code, pos, '{', '}');
            cout << "condition: " << condition << endl;
            cout << "content: " << content << endl;
            whileStatement(condition, content);
        }
        else if (e == "for") {
            string condition = getContent(code, pos, '(', ')');
            string content = getContent(code, pos, '{', '}');
            cout << "condition: " << condition << endl;
            cout << "content: " << content << endl;
            forStatement(condition, content);
        }
        else if (e == "var") {
            string name = getKey(code, pos);
            while (pos < code.length() && code[pos++] != '=') {}
            string exp = "";
            while (pos < code.length() && code[pos] != ';') {
                exp += code[pos++];
            }
            if (pos >= code.length()) {
                cout << "Syntax Error after 'var'" << endl;
                break;
            }
            pos++;
            cout << "Name: " << name << endl;
            cout << "Expression: " << exp << endl;
            actRecManager.addVar(name, getExpResult(exp));
        }
        else if (e == "function") {
            string name = getKey(code, pos);
            string condition = getContent(code, pos, '(', ')');
            string content = getContent(code, pos, '{', '}');
            cout << "name: " << name << endl;
            cout << "condition: " << condition << endl;
            cout << "content: " << content << endl;
            defineFunction(name, condition, content);
        }
        else if (e == "print") {
            string exp = "";
            while (pos < code.length() && code[pos] != ';') {
                exp += code[pos++];
            }
            pos++;
            cout << "exp: " << exp << endl;
            VarValue result = getExpResult(exp);
            cout << result.toString();
        }
        else if (e == "return") {
            string exp = "";
            while (pos < code.length() && code[pos] != ';') {
                exp += code[pos++];
            }
            pos++;
            return getExpResult(exp);
        }
        else {
            while (pos < code.length() && (code[pos] == ' ' || code[pos] == '\n' || code[pos] == 9)) {pos++;}
            if (pos >= code.length()) {
                cout << "Syntax Error!3" << endl;
                break;
            }
            if (code[pos] == '(') {
                string content = getContent(code, pos, '(', ')');
                pos++;
                cout << "Content: " << content << endl;
                callFunction(e, content);
            }
            else if (code[pos] == '=') {
                string exp = "";
                pos++;
                while (pos < code.length() && code[pos] != ';') {
                    exp += code[pos++];
                }
                if (pos >= code.length()) {
                    cout << exp << endl;
                    cout << "Syntax Error!" << endl;
                    break;
                }
                pos++;
                //cout << e << " " << endl;
                //cout << actRecManager.acquireValue(e).toString() << endl;
                cout << "Expression: " << exp << endl;
                cout << "Result:" << getExpResult(exp).toString() << endl;
                actRecManager.addVar(e, getExpResult(exp));
                //cout << actRecManager.acquireValue(e).toString() << endl;
                //cout << getExpResult(exp).toString() << endl;
            }
            else {
                cout << "Syntax Error!4" << endl;
            }
        }
        cout << endl;
    }
    return VarValue();
}
