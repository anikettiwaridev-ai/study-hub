#include <iostream>
#include <stack>
#include <string>
using namespace std;

// #region evaluatePostfix
int evaluatePostfix(string e) {
    stack<int> st;
    for (char c : e) {
        if (isdigit(c)) { st.push(c - '0'); continue; }   // '5' - '0' is 5, not 53
        int b = st.top(); st.pop();                       // 1st pop = RIGHT operand
        int a = st.top(); st.pop();                       // 2nd pop = LEFT operand
        if (c == '+') st.push(a + b);
        else if (c == '-') st.push(a - b);
        else if (c == '*') st.push(a * b);
        else st.push(a / b);
        cout << "  after " << c << ": top = " << st.top() << ", size = " << st.size() << endl;
    }
    return st.top();
}
// #endregion evaluatePostfix

int main() {
    for (string e : {"53+82-*", "231*+9-"}) {
        cout << e << endl;
        int r = evaluatePostfix(e);
        cout << "result = " << r << endl;
    }
    return 0;
}
