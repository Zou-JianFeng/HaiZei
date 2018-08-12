#include <stdio.h>
#define MAX 1000000

int prime[MAX + 5] = {0};
int dnum[MAX + 5] = {0};
int mnum[MAX + 5] = {0};

void init() {
	for (int i = 2; i <= MAX; i++) {
		if (!prime[i]) {
			prime[++prime[0]] = i;
			dnum[i] = 2;
			mnum[i] = 1;
		}
		for (int j = 1; j <= prime[0]; j++) {
			if (i * prime[j] > MAX) break;
			prime[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				dnum[i * prime[j]] = dnum[i] / (mnum[i] + 1) * (mnum[i] + 2);
				mnum[i * prime[j]] = mnum[i] + 1;
				break;
			} else {
				dnum[i * prime[j]] = dnum[prime[j]] * dnum[i];
				mnum[i * prime[j]] = 1;
			}
		}
	}
}

int main() {
	init();
	int n = 2;
	while (1) {
		int digis = 0;
		if (n % 2 == 0) {
			digis = dnum[n / 2] * dnum[(n + 1)];
		} else {
			digis = dnum[n] * dnum[(n + 1) / 2];
		}
		if (digis >= 500) {
			
			break;
		}
		n++;
	}
	printf("%d\n", n * (n + 1) / 2);
	return 0;
}