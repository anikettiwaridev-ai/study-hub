#include <iostream>
using namespace std;

// Practice sheet 3, Q8: keeps the last K values; when full, a new value overwrites the oldest.
class RingBuffer {
    static const int K = 4;
    int buf[K];
    int front = 0, rear = -1, count = 0;
    long long sum = 0;
public:
    // #region add
    void add(int x) {
        if (count == K) {                    // full: the oldest leaves the window
            sum -= buf[front];
            front = (front + 1) % K;
        } else count++;
        rear = (rear + 1) % K;
        buf[rear] = x;
        sum += x;
    }
    // #endregion add
    bool isFull() const { return count == K; }
    int size() const { return count; }
    double average() const { return count ? (double) sum / count : 0; }   // cast BEFORE dividing
    void printOldestToNewest() const {
        for (int i = 0; i < count; i++) cout << buf[(front + i) % K] << " ";
    }
};

int main() {
    RingBuffer r;
    for (int x : {5, 9, 2, 8, 6, 3}) {
        r.add(x);
        cout << "add " << x << ": ";
        r.printOldestToNewest();
        cout << "| size " << r.size() << ", average " << r.average() << endl;
    }
    return 0;
}
