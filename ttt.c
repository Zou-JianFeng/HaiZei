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

Node *insert(Trie root, unsigned char *str) {
    if (!root) root = get_new_node();
    Node *p = root;
    for (int i = 0; str[i]; ++i) {
        int ind = str[i];
        if (!p->next[ind]) p->next[ind] = get_new_node();
        p = p->next[ind];
    }
    p->flag = 1;
    return root;
}

int search_cnt = 0;
int search(Trie root, unsigned char *str) {
    Node *p = root;
    int n = strlen((char *)str);
    int i = 0;
    while (p && i < n) {
        search_cnt += 1;
        int ind = str[i++];
        p = p->next[ind];
    }
    return (p && p->flag);
}

int main() {
    Trie root = NULL;

    int word_cnt = 0;
    int search_word_cnt = 0;
    unsigned char buffer[10000];

    FILE *fpp = NULL;
    fpp = fopen("/Users/zou-jianfeng/HZ/ZY/2.txt", "r"); //读取60M中文文本
    while (~fscanf(fpp, "%s", buffer)) {
        //printf("%s\n", buffer);
        int n = strlen((char *)buffer);
        word_cnt += n;
        root = insert(root, buffer);
    }
    fclose(fpp);

    FILE *fp = NULL;
    fp = fopen("/Users/zou-jianfeng/HZ/ZY/2.txt", "r"); //读取60M中文文本
    while (~fscanf(fp, "%s", buffer)) {
        int n = strlen((char *)buffer);
        search_word_cnt += n;
        if (search(root, buffer)) {
            printf("1");
        } else {
            printf("0");
            search_cnt += 1;
        }
    }
    fclose(fpp);
    printf("\n");

    printf("word_cnt = %d node_cnt = %d search_word_cnt = %d search_cnt = %d\n", word_cnt, node_cnt, search_word_cnt, search_cnt);
    printf("searchrate : %lf\n", 1.0 * search_word_cnt / (1.0 * search_cnt));
    printf("rate : %lf\n", 1.0 * word_cnt / (1.0 * node_cnt * sizeof(Node)));
    clear(root);
    return 0;
}














