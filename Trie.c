#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 100010;
const int SIZE = 26;
const char BASE = 'a';

typedef struct TrieNode {
    int index;
    struct TrieNode **childs;
} TrieNode, *Trie;



TrieNode* new_node() {
    TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode));
    p->childs = (TrieNode **)malloc(sizeof(TrieNode *) * SIZE);
    p->index = 0;
    for (int i = 0; i < SIZE; ++i) {
        p->childs[i] = NULL;
    }
    return p;
}

void clear(TrieNode *p) {
    if (p == NULL) return ;
    for (int i = 0; i < SIZE; ++i) {
        if (p->childs[i] != NULL) clear(p->childs[i]);
    }
    free(p->childs);
    free(p);
    return ;
}

void insert(TrieNode *trie, char *str) {
    TrieNode *p = trie;
    for (int i = 0; str[i]; ++i) {
        if (p->childs[str[i] - BASE] == NULL) {
            p->childs[str[i] - BASE] = new_node();
        }
        p = p->childs[str[i] - BASE];
    }
    p->index = 1;
    return ;
}

int find(TrieNode *p) {
    if (!p) return 0;
    int n = 1;
    for (int i = 0; i < SIZE; ++i) {
        if (p->childs[i] != NULL) n += find(p->childs[i]);
    }
    return n;
}

int main() {
    char str[N];
    scanf("%s", str);
    Trie root = new_node();
	for (int i = 0; str[i]; ++i) {
    	insert(root, str + i);
    }
    printf("%d", find(root) - 1);
    return 0;
}