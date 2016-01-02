#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

extern void pushAR();
extern void popAR();
extern void *getExpResult(string exp);

string getContent(string s, int &p, char left, char right);
int interpreter(string code);
string getKey(string code, int &p);

string getContent(string s, int &p, char left, char right)
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
        }
        else if (s[p] == left) {
            count++;
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

string getKey(string code, int &p)
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

void ifStatement(string condition, string content, string others) {
    //bool result = * ((bool *) getExpResult(condition));
    //pushAR();
    //if (result) {
        interpreter(content);
    //}
    //else {
        interpreter(others);
    //}
    //popAR();
}

void whileStatement(string condition, string content) {
    bool result;
    //while ((result = * ((bool *) getExpResult(condition))) ) {
        //pushAR();
        interpreter(content);
        //popAR();
    //}
}

void forStatement(string condition, string content) {
    //pushAR();
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
    string cond = condition.substr(q, p-q-1);
    
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
    bool result;
    //while ((result = * ((bool *) getExpResult(cond))) ) {
        //pushAR();
        interpreter(content);
        interpreter(iter);
        //popAR();
    //}
    
    // popAR();
}

int interpreter(string code)
{
    //cout << content << endl;
    int pos = 0;
    while (pos < code.length()) {
        //cout << pos << " " << code.length() << endl;
        string e = getKey(code, pos);
        if (e == "") {
            return 0;
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
                return -1;
            }
            exp += code[pos++];
            cout << "Name: " << name << endl;
            cout << "Expression: " << exp << endl;
            //setVarToCurrentAR(name, getExpResult(exp));
        }
        else if (e == "function") {
            string name = getKey(code, pos);
            string condition = getContent(code, pos, '(', ')');
            string content = getContent(code, pos, '{', '}');
            cout << "name: " << name << endl;
            cout << "condition: " << condition << endl;
            cout << "content: " << content << endl;
            //functionStatement(name, condition, content);
        }
        else if (e == "print") {
            string exp = "";
            while (pos < code.length() && code[pos] != ';') {
                exp += code[pos++];
            }
            exp += code[pos++];
            cout << "exp: " << exp << endl;
            // cout << getExpResult(exp);
        }
        else {
            // Check name e, var or func?
            while (pos < code.length() && (code[pos] == ' ' || code[pos] == '\n' || code[pos] == 9)) {pos++;}
            if (pos >= code.length()) {
                cout << "Syntax Error!3" << endl;
                return -1;
            }
            if (code[pos] == '(') {
                string content = getContent(code, pos, '(', ')');
                pos++;
                cout << "Content: " << content << endl;
                // callFunction(e, content);
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
                    return -1;
                }
                exp += code[pos++];
                cout << "Expression: " << exp << endl;
                //setVarToCurrentAR(e, getExpResult(exp));
            }
            else {
                cout << "Syntax Error!4" << endl;
                return -1;
            }
        }
        
        cout << endl;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream in("test.js");
    stringstream buffer;
    buffer << in.rdbuf();
    //pushAR();
    interpreter(buffer.str());
    //popAR();
    return 0;
}