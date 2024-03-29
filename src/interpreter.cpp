#include "interpreter.h"
#include <vector>
using namespace std;

static string getContent(string s, int &p, char left, char right)
{
    while (p < s.length() && (s[p] == ' ' || s[p] == '\n' || s[p] == 9)) {
        p++;
    }
    if (p > s.length() || s[p] != left) {
        string err= "Can't find ";
        err += left;
        err += '\n';
        throw Exception(err);
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
        throw Exception("Error: Brackets mismatched!\n");
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
    key += code[p];
    if (code[p] == '{' || code[p] == '}' || code[p] == '/') {
        p++;
        return key;
    }
    p++;
    while (p < code.length() &&
           ( (code[p] >= 'a' && code[p] <= 'z') ||
             (code[p] >= 'A' && code[p] <= 'Z') ||
             (code[p] >= '0' && code[p] <= '9') ||
             code[p] == '_'))
    {
        key += code[p++];
    }
    if (p >= code.length()) {
        throw Exception("Syntax Error in getKey!\n");
    }
    return key;
}

static void ifStatement(string condition, string content, string others) {
    actRecManager.insertAR(ActRec());
    VarValue result = getExpResult(condition);
    // cout << "Result " << result.toString() << endl;
    if (result.toBool()) {
        try {
            interpreter(content);
        } catch (VarValue e) {
            actRecManager.deleteAR();
            throw e;
        } catch (interrupt e) {
            //cout << "break" << endl;
            actRecManager.deleteAR();
            throw e;
        } catch (Exception e) {
            actRecManager.deleteAR();
            throw e;
        }
    }
    else {
        try {
            interpreter(others);
        } catch (VarValue e) {
            actRecManager.deleteAR();
            throw e;
        } catch (interrupt e) {
            //cout << "break" << endl;
            actRecManager.deleteAR();
            throw e;
        } catch (Exception e) {
            actRecManager.deleteAR();
            throw e;
        }
    }
    actRecManager.deleteAR();
}

static void whileStatement(string condition, string content) {
    actRecManager.insertAR(ActRec());
    VarValue result = getExpResult(condition);
    while (result.toBool()) {
        actRecManager.insertAR(ActRec());
        try {
            interpreter(content);
        } catch (interrupt e) {
            //cout << "break" << endl;
            actRecManager.deleteAR();
            break;
        } catch (Exception e) {
            actRecManager.deleteAR();
            actRecManager.deleteAR();
            throw e;
        } catch (VarValue e) {
            actRecManager.deleteAR();
            actRecManager.deleteAR();
            throw e;
        }
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
        actRecManager.deleteAR();
        throw Exception("Syntax Error in for statement!\n");
    }
    
    int q = p;
    while (p < condition.length() && condition[p++] != ';') {}
    string cond = condition.substr(q, p-q-1);
    
    if (p >= condition.length()) {
        actRecManager.deleteAR();
        throw Exception("Syntax Error in for statement!\n");
    }
    
    int t = p;
    string iter = condition.substr(t, condition.length()-t) + ";";
    
    
    //cout << "init:" << init << endl;
    //cout << "cond:" << cond << endl;
    //cout << "iter:" << iter << endl;
    
    interpreter(init);
    //cout << condition << endl;
    VarValue result = getExpResult(cond);
    while (result.toBool()) {
        actRecManager.insertAR(ActRec());
        try {
            interpreter(content);
        } catch (interrupt e) {
            //cout << "break" << endl;
            actRecManager.deleteAR();
            break;
        } catch (Exception e) {
            actRecManager.deleteAR();
            actRecManager.deleteAR();
            throw e;
        } catch (VarValue e) {
            actRecManager.deleteAR();
            actRecManager.deleteAR();
            throw e;
        }
        interpreter(iter);
        actRecManager.deleteAR();
        result = getExpResult(cond);
        //cout << "cond: " << cond << " Result!: " << result.toString() << endl;
    }
    
    actRecManager.deleteAR();
}

void switchStatement(string condition, string content) {
    VarValue result = getExpResult(condition);
    //cout << "Condition Result: " << result.toString() << endl;
    int p = 0;
    vector<VarValue> labels;
    vector<string> contents;
    string defaultContent = "";
    labels.clear();
    contents.clear();
    while (p < content.length()) {
        string caseStatement = getKey(content, p);
        if (caseStatement == "default") {
            while (p < content.length() && content[p++] != ':') {}
            defaultContent = content.substr(p, content.length() - p);
            //cout << "default: " << defaultContent << endl;
            break;
        }
        if (caseStatement != "case") {
            throw Exception("Error in switch(" +condition + ") statement\n");
        }
        string exp = "";
        while (p < content.length() && (content[p] == ' ' || content[p] == '\n' || content[p] == 9 )) {p++;}
        while (p < content.length() && content[p] != ':') {
            exp += content[p++];
        }
        p++;
        if (p >= content.length()) {
            throw Exception("Error in switch(" +condition + ") statement\n"); 
        }
        VarValue label = getExpResult(exp);
        labels.push_back(label);
        string cont = "";
        while (p < content.length()) {
            int old = p;
            string key = getKey(content, p);
            if (key == "case" || key == "default") {
                p = old;
                break;
            }
            else {
                cont += key;
                while (p < content.length() && content[p] != ';') {
                    cont += content[p++];
                }
                cont += content[p++];
            }
        }
        contents.push_back(cont);

        //cout << "Label: " << label.toString() << " Content: " << cont << endl;
    }

    actRecManager.insertAR(ActRec());
    try {
        bool match = false;
        for (int i = 0; i < labels.size(); ++i) {
            if (result == labels[i]) {
                match = true;
            }
            if (match) {
                interpreter(contents[i]);
            }
        }
        interpreter(defaultContent);
    } catch (interrupt e) {
        //cout << "break" << endl;
    } catch (Exception e) {
        actRecManager.deleteAR();
        throw e;
    } catch (VarValue e) {
        actRecManager.deleteAR();
        throw e;
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
        // cout << "Key: " << e  << "  Pos: " << pos << endl;
        //cout << code.substr(pos, code.length() - pos);
        if (e == "{") { }
        else if (e == "}") { }
        if (e == "if") {
            string condition = getContent(code, pos, '(', ')');
            string content = getContent(code, pos, '{', '}');
            
            // cout << "condition: " << condition << endl;
            // cout << "content: " << content << endl;
            
            int old = pos;
            string others = getKey(code, pos);
            if (others == "else") {
                // cout << "Key: else" << endl;
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
            //cout << "condition: " << condition << endl;
            //cout << "content: " << content << endl;
            whileStatement(condition, content);
        }
        else if (e == "for") {
            string condition = getContent(code, pos, '(', ')');
            string content = getContent(code, pos, '{', '}');
            //cout << "condition: " << condition << endl;
            //cout << "content: " << content << endl;
            forStatement(condition, content);
        }
        else if (e == "switch") {
            string condition = getContent(code, pos, '(', ')');
            string content = getContent(code, pos, '{', '}');
            //cout << "condition: " << condition << endl;
            //cout << "content: " << content << endl;
            switchStatement(condition, content);
        }
        else if (e == "continue") {
            return VarValue();
        }
        else if (e == "break") {
            throw interrupt();
        }
        else if (e == "var") {
            string name = getKey(code, pos);
            while (pos < code.length() && code[pos] == ' ') {
                pos++;
            }
            if (code[pos] == ';') {
                actRecManager.addVar(name);
                pos++;
            }
            else {
                while (pos < code.length() && code[pos++] != '=') {}
                string exp = "";
                while (pos < code.length() && code[pos] != ';') {
                    exp += code[pos++];
                }
                if (pos >= code.length()) {
                    throw Exception("Syntax Error after 'var'\n");
                }
                pos++;
                //cout << "Name: " << name << endl;
                //cout << "Expression: " << exp << endl;
                //cout << "Expression Result: " << getExpResult(exp).toString() << endl;
                actRecManager.addVar(name, getExpResult(exp));
            }
        }
        else if (e == "function") {
            string name = getKey(code, pos);
            string condition = getContent(code, pos, '(', ')');
            string content = getContent(code, pos, '{', '}');
            // cout << "name: " << name << endl;
            // cout << "condition: " << condition << endl;
            // cout << "content: " << content << endl;
            defineFunction(name, condition, content);
        }
        else if (e == "print") {
            string exp = "";
            while (pos < code.length() && code[pos] != ';') {
                exp += code[pos++];
            }
            pos++;
            //cout << "exp: " << exp << endl;
            VarValue result = getExpResult(exp);
            cout << result.toString() << endl;
        }
        else if (e == "return") {
            string exp = "";
            while (pos < code.length() && code[pos] != ';') {
                exp += code[pos++];
            }
            pos++;
            // cout << "return: " << exp << endl;
            // cout << "Result: " << getExpResult(exp).toString() << endl;
            throw getExpResult(exp);
        }
        else if (e == "/") {
            //cout << "Comment" << endl;
            //cout << pos << " " << code[pos] << endl;
            if (code[pos] == '*') {
                bool right = false;
                while (pos < code.length()-2 && !right) {
                    if (code[++pos] == '*'){
                        if (code[++pos] == '/') {
                            right = true;
                        }
                    }
                }
            }
            else if (code[pos] == '/') {
                while (pos < code.length()-1 && code[++pos] != '\n') {}
            }
            else {
                throw Exception("Syntax Error after '/'\n");
            }
            pos++;
        }
        else {
            string exp = e;
            int count = 0;
            while (pos < code.length() && (count > 0 || code[pos] != ';')) {
                if (code[pos] == '{') {
                    count++;
                }
                if (code[pos] == '}') {
                    count--;
                }
                exp += code[pos];
                pos++;
            }
            if (pos >= code.length()) {
                throw Exception("Missing ';'\n");
            }
            pos++;
            //cout << "Expression: " << exp << endl;
            //cout << "Result: " << getExpResult(exp).toString() << endl;
            getExpResult(exp);
            /*
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
                actRecManager.setVar(e, getExpResult(exp));
                //cout << actRecManager.acquireValue(e).toString() << endl;
                //cout << getExpResult(exp).toString() << endl;
            }
            else {
                cout << "Syntax Error!4" << endl;
            }
            */
        }
        // cout << endl;
    }
    return VarValue();
}
