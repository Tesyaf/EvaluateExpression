#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

bool isOperator(char ch) {
    vector<char> op = {'+','-','*','/','%'};
    return find(op.begin(), op.end(), ch) != op.end();
}

int precedence(string op){
    if(op == "+" || op == "-") return 1;
    else if(op == "*" || op == "/" || op == "%") return 2;
    else return 0;
}

vector<string> stringToInfix(string str) {
    vector<string> infix;
    string angka;

    for (size_t i = 0; i < str.size(); ++i) {
        char ch = str[i];

        if (isspace(ch)) {
            continue;
        }
        else if (isdigit(ch) ) {
            angka += ch;
        } 
        else if (ch == '-' && (i == 0 || isOperator(str[i - 1]) || str[i-1] == '(' )) {
            if((str[i-1] == '(' && str[i+2] ==')')){
                angka += ch;
            }
            else if(isOperator(str[i-1]) || str[i+1] == ')' || str[i+1] == '(' || str[i-1] == '('){
                infix.push_back("-1");
                infix.push_back("*");
            }
            else if((isdigit(str[i+1] && str[i-1] == '(') || i == 0)){
                angka += ch;
            }
            else{
                infix.push_back("-");
            }
        }
        else {
            if (!angka.empty()) {
                infix.push_back(angka);
                angka.clear();
            }
            infix.push_back(string(1, ch));
        }
    }

    if (!angka.empty()) {
        infix.push_back(angka);
    }
    return infix;
}

vector<string> InfixToPostfix(vector<string> infix){
    stack<string> operand;
    vector<string> postfix;

    for(auto itr = infix.begin(); itr != infix.end(); itr++){
        string str = *itr;
        if( isdigit(str[0]) || ( str[0] == '-' && str.size() > 1 && isdigit(str[1]) ) ){
            postfix.push_back(str);
        }else if(str == "("){
            operand.push(str);
        }else if(str == ")"){
            while (!operand.empty() && operand.top() != "("){
                postfix.push_back(operand.top());
                operand.pop();
            }
            if(!operand.empty()){
                operand.pop();
            }

        }else{
            while(!operand.empty() && operand.top() != "(" && ( precedence(str) <= precedence(operand.top()))){
                postfix.push_back(operand.top());
                operand.pop();
            }
            operand.push(str);
        }
    }
    while(!operand.empty() && ( operand.top() != "(" || operand.top() != ")" )){
        postfix.push_back(operand.top());
        operand.pop();
    }
    return postfix;
}

void printPostfix(vector<string> postfix) {
    for (size_t i = 0; i < postfix.size(); ++i) {
        cout << postfix[i] << " ";
    }
    cout << endl;
}

int main() {
    string str;
    getline(cin, str);

    vector<string> infix = stringToInfix(str);
    vector<string> postfix = InfixToPostfix(infix);
    printPostfix(postfix);

    return 0;
}
