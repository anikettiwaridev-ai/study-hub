#include <iostream>
#include <stack>
#include <string>
using namespace std;

int prec(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// #region infixToPostfix
string infixToPostfix(string e) {
    stack<char> st;
    string out;
    for (char c : e) {
        if (isalnum(c)) out += c;                               // operand: straight out
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (st.top() != '(') { out += st.top(); st.pop(); }
            st.pop();                                           // drop the (
        } else {                                                // operator
            while (!st.empty() && st.top() != '(' &&
                   (prec(st.top()) > prec(c) || (prec(st.top()) == prec(c) && c != '^'))) {
                out += st.top(); st.pop();                      // higher or equal pops, except ^
            }
            st.push(c);
        }
    }
    while (!st.empty()) { out += st.top(); st.pop(); }
    return out;
}
// #endregion infixToPostfix

int main() {
    for (string e : {"a+b*c-d", "(a+b)*(c-d)", "a+b*c^d^e", "a-(b+c*d/(e/f*g+h)-i)"})
        cout << e << "  ->  " << infixToPostfix(e) << endl;
    return 0;
}
