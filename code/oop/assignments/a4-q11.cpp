#include <iostream>
using namespace std;

class Candidate {
public:
    int id, written, interview;
    Candidate(int i, int w, int iv) { id = i; written = w; interview = iv; }
    int total() const { return written + interview; }   // const: safe to call on a const object
};

// const reference: no copy is made, and the function cannot change either candidate.
const Candidate &better(const Candidate &a, const Candidate &b) {
    if (a.total() != b.total()) return a.total() > b.total() ? a : b;
    return a.written >= b.written ? a : b;              // tie-breaker: written marks
}

int main() {
    Candidate c1(1, 70, 20), c2(2, 60, 30), c3(3, 75, 10);
    cout << "c1 vs c2 (both 90): candidate " << better(c1, c2).id << " wins on written marks" << endl;
    cout << "c2 vs c3: candidate " << better(c2, c3).id << endl;
    return 0;
}
