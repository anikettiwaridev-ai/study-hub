#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

int prec(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// #region infixToPrefix
string infixToPrefix(string e) {
    reverse(e.begin(), e.end());                         // 1. reverse
    for (char& c : e) {                                  // 2. swap ( and )
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }
    stack<char> st;                                      // 3. modified postfix pass
    string out;
    for (char c : e) {
        if (isalnum(c)) out += c;
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (st.top() != '(') { out += st.top(); st.pop(); }
            st.pop();
        } else {
            while (!st.empty() && st.top() != '(' &&
                   (prec(st.top()) > prec(c) || (prec(st.top()) == prec(c) && c == '^'))) {
                out += st.top(); st.pop();               // equal precedence pops ONLY for ^
            }
            st.push(c);
        }
    }
    while (!st.empty()) { out += st.top(); st.pop(); }
    reverse(out.begin(), out.end());                     // 4. reverse the result
    return out;
}
// #endregion infixToPrefix

int main() {
    for (string e : {"(a-b/c)*(a/k-l)", "a-b-c", "a^b^c", "((H*((((A+((B+C)*D))*F)*G)*E))+J)"})
        cout << e << "  ->  " << infixToPrefix(e) << endl;
    return 0;
}
