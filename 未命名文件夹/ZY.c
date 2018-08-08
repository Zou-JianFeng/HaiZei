#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BASE 2

typedef struct Node {
	int flag;
	struct Node *next[BASE];
} Node, *Trie;

Node *get_new_node() {
	Node *p = (Node *)calloc(sizeof(Node), 1);
	p->flag = 0;
	return p;
}

void clear(Trie root) {
	if (!root) return;
	for (int i = 0; i < BASE; ++i) clear(root->next[i]);
	free(root);
	return ;
}

Node *insert(Trie root, const int *CN, int n) {
	if (!root) root = get_new_node();
	Node *p = root;
	for (int i = 0; i < n; ++i) {
		int ind = CN[i];
		if (!p->next[ind]) p->next[ind] = get_new_node();
		p = p->next[ind];
	}
	p->flag = 1;
	return root;
}

int search(Trie root, const int *CN, int n) {
	Node *p = root;
	int i = 0;
	while (p && i < n) {
		int ind = CN[i++];
		p = p->next[ind];
	}
	return (p && p->flag);
}

int *str_to_num(const char *str) {
	int n = strlen(str);
	int *num = (int *)calloc(sizeof(int), 8 * n);
	int j = 0;
	for (int i = 0; str[i]; ++i) {
		int n = str[i] * (-1),  ind = 8;
		while (ind--) {
			if (n) {
				num[j++] = n % 2;
				n /= 2;
			}
			else num[j++] = 0;
		}
	}
	return num;
}

int main() {
	Trie root = NULL;
	int n = 5;
	while (n--) {
		char str1[100];
		scanf("%s", str1);
		int *CN1 = str_to_num(str1);
		int n1 = strlen(str1) * 8;
		root = insert(root, CN1, n1);
	}
	n = 5;
	while (n--) {
		char str[100];
		scanf("%s", str);
		int *CN = str_to_num(str);
		int n = strlen(str) * 8; 
		printf("%d\n", search(root, CN, n));
	}
	clear(root);
	return 0;
}














