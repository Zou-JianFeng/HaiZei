#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int *data;
    int top, size;
} Stack;

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->top = -1;
    s->size = n;
    return s;
}

int push(Stack *s, int n) {
    if (s->top + 1 == s->size) return 0;
    s->top++;
    s->data[s->top] = n;
    return 1;
}

void output(Stack *s) {
    int top = s->top;
    for (int i = 0; i <= top; i++) {
        printf("%d", s->data[i]);
    }
}

int top(Stack *s) {
    return s->data[s->top];
}

void pop(Stack *s) {
    s->top--;
}

void clear(Stack *s) {
    free(s->data);
    free(s);
}

int main() {
    int n, m;
    scanf("%d\n", &n);
    int num[n];
    for (int i = 0; i < n; i++) {
        scanf("%d ", &m);
        num[i] = m;
    }
    
    Stack *s = init(n);
    int index = 1;
    for (int i = 0; i < n; i++) {
        while (num[i] >= index) {
            push(s, index);
            index++;
        }
        if (num[i] < top(s)) {
            index = 0;
            break;
        }
        pop(s);
    }
    if (index == n + 1) printf("YES");
    else printf("NO");
    clear(s);
    
    return 0;
}