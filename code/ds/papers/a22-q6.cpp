#include <cstdio>

struct node {
    int data;
    struct node* next;
};

void solve(struct node* start) {
    if (start == NULL)
        return;
    printf("%d ", start->data);
    if (start->next != NULL)
        solve(start->next->next);
    printf("%d ", start->data);
}

int main() {
    struct node* head = NULL;
    for (int x = 6; x >= 1; x--) {           // builds 1->2->3->4->5->6
        struct node* n = new node;
        n->data = x;
        n->next = head;
        head = n;
    }
    solve(head);
    printf("\n");
    return 0;
}
