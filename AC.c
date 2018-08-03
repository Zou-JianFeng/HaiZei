#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 26;
const char BASE = 'a';
const int MAX_SIZE = 1000000;
const int MAX_LEN = 100000;

typedef struct TrieNode {
    int count;
    struct TrieNode **childs, *fail;
} TrieNode, *Trie;

TrieNode* new_node() {
    Trie p = (Trie)malloc(sizeof(TrieNode));
    p->childs = (Trie *)malloc(sizeof(Trie) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        p->childs[i] = NULL;
    }
    p->fail = NULL;
    p->count = 0;
    return p;
}

void clear(Trie p) {
    if (!p) return ;
    for (int i = 0; i < SIZE; ++i) {
        if (p->childs[i] != NULL) clear(p->childs[i]);
    }
    free(p->childs);
    free(p);
    
    return ;
}

void insert(Trie t, char *str) {
    Trie p = t;
    for (int i = 0; str[i]; ++i) {
        if (p->childs[str[i] - BASE] == NULL) p->childs[str[i] - BASE] = new_node();
        p = p->childs[str[i] - BASE];
    }
    ++p->count;
    //printf("%d ", p->count);
}

void build_automaton(Trie root) {
	root->fail = root;
    Trie q[MAX_SIZE];
    int l = 0, r = 0;
    q[r++] = root;
    while (l < r) {
        Trie now = q[l++];
        for (int i = 0; i < SIZE; i++) {
        	if (now->childs[i] != NULL) {
                Trie child = now->childs[i];
                if (now == root) child->fail = root;
                else {
                	Trie trie = now;
                    while (trie != root && trie->fail->childs[i] == NULL) {
                        trie = trie->fail;
                    }
                    if (trie->fail->childs[i] != NULL) child->fail = trie->fail->childs[i];
                    else child->fail = root;
                }
            	q[r++] = child;
            }
    	}
    }	
}

int match_count(Trie root, const char *buffer) {
    TrieNode *p = root;
    int total_count = 0;
    for (int i = 0; buffer[i]; i++) {
        while (p != root && p->childs[buffer[i] - BASE] == NULL) {
            p = p->fail;
        }
        
        p = p->childs[buffer[i] - BASE];
        if (p == NULL) p = root;
        
        TrieNode *iter = p;
    	while (iter != root) {
        	total_count += iter->count;
            iter = iter->fail;
    	} 
    }
    return total_count;
}

int main() {
    Trie root = new_node();
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        char pattern[MAX_LEN];
        scanf("%s", pattern);
        insert(root, pattern);
    }
    build_automaton(root);
    char str_buffer[MAX_LEN];
    scanf("%s", str_buffer);
    printf("%d\n", match_count(root, str_buffer));
    clear(root);
    return 0;
}