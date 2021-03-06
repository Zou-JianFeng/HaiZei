#include <stdio.h>
#include <stdlib.h>
int* two_sum(int *nums, int length, int target) {
    int *ans = malloc(2 * sizeof(int));
    int i = 0, j = length - 1;
    while (i < j) {
        if (nums[i] + nums[j] == target) 
            break;
        if (nums[i] + nums[j] < target) 
            ++i;
    	else
            --j;
    }
    if (i != j) {
        ans[0] = i;
        ans[1] = j;
    }
    return ans;
}
int main() {
    int n, target;
    scanf("%d %d", &n, &target);
    int* num = (int*)malloc(n * sizeof(int));
    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", num + i);
        a[i] = num[i];
    }
    int *x = two_sum(num, n, target);
    int *p = two_sum(num, n, target);
    if (p[0] == p[1]) {
        printf("一个数只能用一次!\n");
    } else {
        printf("%d\n", a[p[0]] + a[p[1]]);
    }
    free(p);
    free(num);
    free(a);
    return 0;
}