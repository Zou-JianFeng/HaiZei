#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild, *father;
}Node;

Node* init(int data, Node *p) {
    p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->lchild = p->rchild = NULL;
    p->father = p;
    return p;
}

Node* insert(Node *p, int data) {
    if (!p) p = init(data, NULL);
    else if (data > p->data) {
        p->rchild = insert(p->rchild, data);
    }
    else if (data < p->data) {
        p->lchild = insert(p->lchild, data);
    }
    return p;
}

Node* search(Node *p, int data) {
    if (p == NULL || p->data == data) return p;
    else {
        if (data > p->data) {
            return search(p->rchild, data);
        } else {
            return search(p->lchild, data);
        }
    }
}
void output(Node *p) {
    if (p == NULL) return ;
    output(p->lchild);
    printf("%d ", p->data);
    output(p->rchild);
    return ;
}
void clear(Node *node) {
    if (node != NULL) {
        if (node->lchild != NULL) {
            clear(node->lchild);
        }
        if (node->rchild != NULL) {
            clear(node->rchild);
        }
        free(node);
    }
}

int main() {
    Node *binarytree = NULL;
    init(100, binarytree);
    int n, data;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &data);
        binarytree = insert(binarytree, data);
    }
    scanf("%d", &n);
    printf("search %s!\n", search(binarytree, n) ? "success" : "failed");
    output(binarytree);
    clear(binarytree);
    return 0;
}