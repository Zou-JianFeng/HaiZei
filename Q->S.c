#include <stdlib.h>
typedef struct {
    int *data;
    int top, size, count;
} MyQueue;

/** Initialize your data structure here. */
MyQueue* myQueueCreate(int maxSize) {
    MyQueue *obj = (MyQueue *)malloc(sizeof(MyQueue));
    obj->data = (int *)malloc(sizeof(int) * maxSize);
    obj->top = -1;
    obj->size = maxSize;
    obj->count = 0;
    return obj;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    obj->top++;
    obj->count++;
    obj->data[obj->top] = x;
}

MyQueue *f(MyQueue *q, int n) {
    //printf("%d %d %d\n", q->count, q->top,q->data[q->top]);
    MyQueue *m = myQueueCreate(n + 1);
    int count = q->count;
    int top = q->top;
    while (count--) {
        //printf("%d ", q->data[top--]);
        myQueuePush(m, q->data[top--]);
    }
    // for (int i = n; i >= q->count - 2; i--) {
    //     myQueuePush(m, q->data[i]);
    // }
    return m;
}
 
/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    int n = obj->data[obj->top];
    MyQueue *q = f(obj, n);
    int m = q->data[q->top];
    obj->count--;
    myQueueFree(q);

    return m;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
    int n = obj->data[obj->top];
    MyQueue *q = f(obj, n);
    
    int m = q->data[q->top];
    myQueueFree(q);

    return m;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    if (obj->count == 0) return true;
    return false;
}

void myQueueFree(MyQueue* obj) {
    free(obj->data);
    free(obj);
}
