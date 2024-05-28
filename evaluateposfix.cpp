#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


bool isOperator(char ch) {
    vector<char> op = {'+','-','*','/','%'};
    return find(op.begin(), op.end(), ch) != op.end();
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

void printInfix(const vector<string>& infix) {
    for (size_t i = 0; i < infix.size(); ++i) {
        cout << infix[i] << " ";
    }
    cout << endl;
}

int main() {
    string str;
    getline(cin, str);

    vector<string> infix = stringToInfix(str);

    printInfix(infix);

    return 0;
}
