#include <cstdio>

int Q[20], front = -1, rear = -1;

void enqueue(int x) {
    if (front == -1) front = 0;
    Q[++rear] = x;
}
int dequeue() { return Q[front++]; }

void show() {
    printf("  front = %d, rear = %d, queue:", front, rear);
    for (int i = front; i <= rear; i++) printf(" %d", Q[i]);
    printf("\n");
}

int main() {
    enqueue(3);
    enqueue(5);
    enqueue(9);
    printf("%d", dequeue());     // d1
    enqueue(2);
    enqueue(4);
    printf("%d", dequeue());     // d2
    printf("%d", dequeue());     // d3
    enqueue(1);
    enqueue(8);
    printf("\n");
    show();
    return 0;
}
