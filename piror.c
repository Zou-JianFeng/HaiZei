#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
    struct Node *prior;
}Node;

Node *init(int data) {
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->next = NULL;
    return p;
}

Node *insert(Node *head, int data, int index){
    if (index < 0) return head;
    if (head == NULL) {
        if (index != 0) return head;
        else {
            head = init(data);
        	return head;
        }
    }
    Node *p = head;
	Node *node = init(data);
    while (p->next != NULL && index--) {
        p = p->next;
    }
    node->next = p->next;
    p->next = node;
	return head;
}

Node *round(Node *head) {
    Node *p = head;
    while(p->next) {
        p->next->prior = p;
        p = p->next;
    }
    head->prior = p;
    return head;
}

void output(Node *head, int data, int n) {
    Node *p = head;
    if (p == NULL) return ;
    while(p->data != data) {
        p = p->next;
    }
	printf("%d", p->data);
    if (n-- != 0) printf(" ");
    p = p->prior;
    while(n--) {
        printf("%d", p->data);
        if (n != 0) printf(" ");
        p = p->prior;
    }
    return ;
}

void clear(Node *head) {
    Node *p;
    while(head) {
        p = head->next;
        free(head);
        head = p;
    }
    return ;
}

int main() {
    Node *head = NULL;
    int n, m, k;
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d ", &m);
        head = insert(head, m, i);
    }
    head = round(head);
    scanf("%d", &k);
    output(head, k, n);
    clear(head);
    return 0;
}