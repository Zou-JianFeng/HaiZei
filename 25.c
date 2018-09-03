#include <stdio.h>
#define MAX 1000

int f[3][MAX +5] = {0};

int main() {
    f[1][0] = f[1][1] = 1;
    f[2][0] = f[2][1] = 1;
    int n = 2;
    while (f[n % 3][0] < MAX) {
        ++n;
        for (int i = 1; i <= f[(n + 2) % 3][0]; ++i) {
            f[n % 3][i] = f[(n + 1) % 3][i] + f[(n + 2) % 3][i];
        }
        f[n % 3][0] = f[(n + 2) % 3][0];
        for (int i = 1; i <= f[n % 3][0]; ++i) {
            if (f[n % 3][i] < 10) continue;
            f[n % 3][i + 1] += f[n % 3][i] / 10;
            f[n % 3][i] %= 10;
            f[n % 3][0] += (i == f[n % 3][0]);
        }
    }
    printf("%d\n", n);
    return 0;
}
