#include <stdio.h>
#define MAX 105

int main() {
  int n;
  int num[MAX][MAX];
  int f[MAX][MAX];
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      scanf("%d", &num[i][j]);
    }
  }

  for (int i = 1; i < n; ++i) {
    f[n - 1][i] = num[n - 1][i];  
  }
  for (int i = n - 2; i >= 0; --i) {
    for (int j = 0; j <= i; ++j) {
      f[i][j] = num[i][j];
      if (f[i + 1][j] >f[i + 1][j + 1]) {
        f[i][j] += f[i + 1][j];
      }
      else f[i][j] += f[i + 1][j + 1];
    }
  }
  printf("%d", f[0][0]);


  return 0;
}
