#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR 0
#define OK 1

typedef struct Stack {
    int *elements;
    int max_size, top_index;
} Stack;

void init(Stack *s, int n) {
    s->elements = (int *)malloc(sizeof(int) * n);
    s->top_index = -1;
    s->max_size = n;
}

int push(Stack *s, int element) {
    if (s->top_index >= s->max_size - 1) return ERROR;
    s->top_index++;
    s->elements[s->top_index] = element;
    return OK;
}

int pop(Stack *s) {
    if (s->top_index < 0) return ERROR;
    s->top_index--;
    return OK;
}

int top(Stack *s) {
    return s->elements[s->top_index];
}

int empty(Stack *s) {
    if (s->top_index < 0) return 1;
    else return 0;
}

int precede(char a, char b) {
    if ((a == '*' || a == '/') && (b == '+' || b == '-')) {
        return 1;
    }
    else {
        return 0;
    }
}
int operate(char theta, int a, int b) {
    if (theta == '+') {
        return a + b;
    } 
    else if (theta == '-') {
        return a - b;
    }
    else if (theta == '/') {
        return a / b;
    }
    else if (theta == '*') {
        return a * b;
    }
}
void calc(Stack *numbers, Stack *operators) {
    int a = top(numbers);
    pop(numbers);
    int b = top(numbers);
    pop(numbers);
    push(numbers, operate(top(operators), b, a));
    pop(operators);
}

void clear(Stack *s) {
    free(s->elements);
    free(s);
}

int main() {
    Stack *numbers = (Stack *)malloc(sizeof(Stack));
    Stack *oper = (Stack *)malloc(sizeof(Stack));
    int n;
    scanf("%d\n", &n);
    init(numbers, n);
    init(oper, n);
    char *buffer = (char *)malloc(sizeof(char) * (n + 1));
    scanf("%s", buffer);
    int i = 0;
    while(i < n) {
       if (isdigit(buffer[i])) {
           push(numbers, buffer[i] - '0');
           //printf("%d\n", top(numbers));
           i++;
       } 
       else {
           if (empty(oper) || precede(buffer[i], top(oper))) {
               push(oper, buffer[i]);
               //printf("%c\n", top(oper));
               i++;
           } else {
               calc(numbers, oper);
               //printf("%d\n", top(numbers));
             }
       }
    }
    while (!empty(oper)) {
        calc(numbers, oper);
    }
    printf("%d\n", top(numbers));
    clear(numbers);
    clear(oper);
    free(buffer);
    
    return 0;
}