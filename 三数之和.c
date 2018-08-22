#include <stdio.h>
#include <stdlib.h>
int* three_sum(int *nums, int length, int target) {
    int *ans = malloc(sizeof(int) * 3);
    int i, j, a, k = 0;
    while (k < length - 2) {
        a = target - nums[k]; 
        i = k + 1, j = length - 1;
        while (i < j && nums[i] + nums[j] != a) {
        	if (nums[i] + nums[j] < a) {
                //a = a - nums[i] + nums[i + 1];
            	++i;
            } else {
                //a = a - nums[j] + nums[j - 1];
            	--j;
            }
    	}
    	if (i < j) {
    		ans[0] = k;
    		ans[1] = i;
    		ans[2] = j;
    		//printf("%d %d %d\n", k, i, j);
        	return ans;
    	}
        k++;
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
    int *x = three_sum(num, n, target);
    int *p = three_sum(num, n, target);
    if (p[0] == p[1] || p[0] == p[2] || p[1] == p[2] ) {
        printf("一个数只能用一次!\n");
    } else {
        printf("%d\n", a[p[0]] + a[p[1]] + a[p[2]]);
    }
    free(p);
    free(num);
    free(a);
    return 0;
}