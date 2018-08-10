#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BASE 256

typedef struct Node {
    int flag;
    struct Node *next[BASE];
} Node, *Trie;

int node_cnt = 0;
Node *get_new_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->flag = 0;
    node_cnt += 1;
    return p;
}

void clear(Trie root) {
    if (!root) return;
    for (int i = 0; i < BASE; ++i) clear(root->next[i]);
    free(root);
    return ;
}

Node *insert(Trie root, char *str) {
    if (!root) root = get_new_node();
    Node *p = root;
    for (int i = 0; str[i]; ++i) {
        int ind = str[i] * (-1);
        if (!p->next[ind]) p->next[ind] = get_new_node();
        p = p->next[ind];
    }
    p->flag = 1;
    return root;
}

int search(Trie root, char *str) {
    Node *p = root;
    int n = strlen(str);
    int i = 0;
    while (p && i < n) {
        int ind = str[i++] * (-1);
        p = p->next[ind];
    }
    return (p && p->flag);
}

int main() {
    Trie root = NULL;
    int n = 5;

    int word_cnt = 0;
    FILE *fpp = NULL;
    char buffer[1000];
    fpp = fopen("/Users/zou-jianfeng/HZ/ZY/1.txt", "r"); //读取60M中文文本
    while (~fscanf(fpp, "%s", buffer)) {
        printf("%s\n", buffer);
        word_cnt += strlen(buffer);
        root = insert(root, buffer);
    }
    fclose(fpp);
    printf("请输入查询次数\n");
    scanf("%d", &n);
    // while (n--) {
    //  char str1[100];
    //  scanf("%s", str1);
    //  word_cnt += strlen(str1);
    //  int *CN1 = str_to_num(str1);
    //  int n1 = strlen(str1) * 8;
    //  root = insert(root, CN1, n1);
    // }
    //n = 5;
    while (n--) {
        char str[100];
        scanf("%s", str);
        printf("%d\n", search(root, str));
    }
    // printf("%d %d\n", word_cnt, node_cnt);
    printf("rate : %lf\n", 1.0 * word_cnt / (1.0 * node_cnt * sizeof(Node)));
    clear(root);
    return 0;
}














