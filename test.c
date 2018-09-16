#include <stdio.h>
//#include <stdlib.h>

int main() {
	int a[10] = {0};
	printf("%lu %lu\n", sizeof(a), sizeof(*a));
	return 0;
}