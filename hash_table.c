#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Data {
	char *str;
	// int flag;
	struct Data, *next;
} Data;

typedef struct HashTable {
	Data *data;
	int size;
	int (*hash_func)(const char *);

} HashTable;

int APHash(const cahr *str) {
	int hash = 0;
	for (int i = 0; str[i]; i++) {
		if (i & 1) {
			hash ^= (hash << 7) ^ str[i] ^ (hash >> 3);
		} else {
			hash ^= (~((hash << 11) ^ str[i] ^ (hash >> 5)))
		}
	}
	return hash & 0x7fffffff;
}

int BKDRHash(const char *str) {
	int hash = 0, seed = 131;
	for (int i = 0; str[i]; i++) {
		hash = hash * seed +str[i];
	}
	return hash & 0x7fffffff;
}

int __APHash(Data *data) {
	return APHash(data->str);
}

int __BKDRHash(Data *data) {
	return BKDRHash(data->str);
}

int __ZobristHash(Data *data) {
	return ZobrisHash(data->str);
}

HashTable *init(int size, int (*func)(const cahr *)) {
	HashTable *p = (HashTable *)malloc(sizeof(HashTable));
	p->data = (Data *)calloc(sizeof(Data), size);
	p->size = size;
	p->hash_func = func;
	return p;
}

void clear(HashTable *h) {
	if (h == NULL) return ;
	free(h->data);
	free(h);
	return ;
}

int query(HashTable *h, const char *str) {
	int ind = h->hash_func(str) % h->size;
	Data *p  = &h->data[ind].next;
	while (p) {
		if (strcmp(p->str, str) == 0) return -1;
		p = p->next;
	}
	h->cnt += 1;
	return ind;
}

void insert(HashTable *h, const char * str) {
	int ind = query(h, str);
	if (ind == -1) return ;
	Data *data = (Data *)malloc(sizeof(Data));
	data->str = strdup(str);
	data->next = h->data[ind].next;
	h->data[ind].next = data;
	return ;
}

void init_zobrist_table() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 256; j++) {
			zobrist_table[i][j] = rand();
		}
	}
	return ;
}

int zobrist_table[50][256] = {0};

int ZobrisHash(const char *str){
	static int flag = 1;
	if (flag) {
		flag = 0;
		init_zobrist_table();
	}
	int hash = 0;
	for (int i = 0; str[i]; i++) {
		hash ^= zobrist_table[i][str[i]];
	}
	return hash & 0x7fffffff;
}

int MyHash(const char *str) {
	int hash = 1;
	for (int i = 0; str[i]; i++) {
		hash *= str[i];
	}
	return hash & 0x7fffffff;
}

int main() {
	HashTable *apHashTable = init(100, APHash);
	HashTable *bkdrHashTable = init(100, BKDRHash);
	HashTable *zobristHashTable = init(100, ZobrisHash);
	HashTable *myHashTable = init(100, MyHash);
 	#define MAX_TEST_CNT 1000000
 	for (int i = 0; i < MAX_TEST_CNT; i++) {
 		char str[7] = {0};
 		for (int j = 0; j < 6; j++) {
 			str[j] = rand() % 26 + 'a';
 		}
 		str[6] = 0;
 		insert(apHashTable, str);
 		insert(bkdrHashTable, str);
 		insert(zobrist_table, str);
 	}
 	printf("APHash(%d) = %d\n", MAX_TEST_CNT, apHashTable->cnt);;
 	printf("BKDRHash(%d) = %d\n", MAX_TEST_CNT, bkdrHashTable->cnt);;
 	printf("ZobrisHash(%d) = %d\n", MAX_TEST_CNT, zobrisHashHashTable->cnt);;
 	printf("MyHash(%d) = %d\n", MAX_TEST_CNT, MyHashTable->cnt);;
 	#undef MAX_TEST_CNT
	return 0;
}