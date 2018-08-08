#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define BASE 256
#define MAX_LEN 100000
#define swap(a, b) { \
	__typeof(a) temp; \
	temp = a; \
	a = b; \
	b = temp; \
}

typedef struct HFNode {
	int data, freq;
	struct HFNode *lchild, *rchild;
} HFNode;

HFNode *get_Node() {
	HFNode *p = (HFNode *)malloc(sizeof(HFNode));
	p->freq = p->data = 0;
	p->lchild = p->rchild = NULL;
	return p;
}

void build(int n, HFNode *arr[n]) {
	for (int times = 0; times < n - 1; times++) {
		HFNode *minNode = arr[0];
		int ind = 0;
		for (int i = 1; i < n - times; i++) {
			if (arr[i]->freq >= minNode->freq) continue;
			minNode = arr[i];
			ind = i;
		}
		swap(arr[ind], arr[n - times - 1]);
		minNode = arr[0];
		ind = 0;

		for (int i = 1; i < n - times; i++) {
			if (arr[i]->freq >= minNode->freq) continue;
			minNode = arr[i];
			ind = i;
		}
		swap(arr[ind], arr[n - times - 2]);
		HFNode *new_node = get_Node();
		new_node->lchild = arr[n - times - 1];
		new_node->rchild = arr[n - times - 2];
		new_node->freq = arr[n - times - 1]->freq + arr[n - times - 2]->freq;
		arr[n - times - 2] = new_node;
	}
	return ;
}

void get_cn(char *str, int *CN) {
	for(int i = 0; str[i]; ++i) {
		CN[str[i] * (-1)]++;
	}
}

void output(HFNode *root, int *num, int n) {
	if (!root) return ;
	if (root->lchild == NULL && root->rchild == NULL) {
		if (root->freq) {
			printf("%d %d : ", root->data, root->freq);
			for (int i = 0; i < n; ++i) printf("%d", num[i]);
			printf("\n");
		}
	}
	num[n] = 0;
	output(root->rchild, num, n + 1);
	num[n] = 1;
	output(root->lchild, num, n + 1);
	return ;
}

int main() {
	HFNode *arr[BASE] = {0};
	char buffer[MAX_LEN];
	int freq;
	scanf("%s", buffer);
	int CN[256] = {0};
	get_cn(buffer, CN);
	for (int i = 0; i < BASE; i++) {
		HFNode *new_node = get_Node();
		new_node->data = i;
		new_node->freq = CN[i];
		arr[i] = new_node; 
	}
	build(BASE, arr);
	int ans;
	int num[100];
	scanf("%d", &ans);
	output(arr[0], num, 0);

	return 0;
}








