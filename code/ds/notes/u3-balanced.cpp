#include <iostream>
#include <stack>
#include <string>
using namespace std;

// #region balanced
bool isBalanced(string e) {
    stack<char> st;
    for (char c : e) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (st.empty()) return false;                 // closer with nothing open
            char o = st.top(); st.pop();
            if ((c == ')' && o != '(') || (c == ']' && o != '[') || (c == '}' && o != '{'))
                return false;                             // wrong type
        }
    }
    return st.empty();                                    // leftover openers?
}
// #endregion balanced

int main() {
    string tests[] = {"{[a+(b*c)]-1}", "{[a+(b*c)]-1)}", "a+b)", "((a)", "([)]", ""};
    for (string t : tests)
        cout << "\"" << t << "\" -> " << (isBalanced(t) ? "balanced" : "not balanced") << endl;
    return 0;
}
