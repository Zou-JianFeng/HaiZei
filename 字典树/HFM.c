#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define HBASE 256
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

void get_cn(unsigned char *str, int *CN) {
	for(int i = 0; str[i]; ++i) {
		CN[str[i]]++;
	}
}

void extract(HFNode *root, char *buff, char (*huffman_code)[100], int n) {
	buff[n] = '\0';
	if (root->lchild == NULL && root->rchild == NULL) {
		strcpy(huffman_code[root->data], buff);
		printf("%d %d : %s\n",root->data, root->freq, buff);
		return ; 
	}
	buff[n] = '0';
	extract(root->lchild, buff, huffman_code, n + 1);
	buff[n] = '1';
	extract(root->rchild, buff, huffman_code, n + 1);
	return ;
}

int main() {
	HFNode *arr[HBASE] = {0};
	unsigned char buffer[MAX_LEN];
	int freq;
	scanf("%s", buffer);
	int CN[HBASE] = {0};
	get_cn(buffer, CN);
	int n = 0;
	for (int i = 0; i < BASE; ++i) {
		if(!CN[i]) continue;
		HFNode *new_node = get_Node();
		new_node->data = i;
		new_node->freq = CN[i];
		arr[n++] = new_node; 
	}

	build(n, arr);
	char buff[100];
	char huffman_code[256][100] = {0};
	extract(arr[0], buff, huffman_code, 0);

	return 0;
}








