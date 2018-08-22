#include <stdio.h>
#include <stdlib.h>
void quick_sort(int *nums, int left, int right) {
    if (right - left < 1) return ;
	int x = left, y = right, z = nums[left];
	while (x < y) {
		while (x < y && nums[y] >= z) --y;
		if (x < y) nums[x++] = nums[y];
		while (x < y && nums[x] <= z) ++x;
		if (x < y) nums[y--] = nums[x];
	}
	nums[x] = z;
	quick_sort(nums, left, x - 1);
	quick_sort(nums, x + 1, right);
}
int three_sum_smaller(int *nums, int length, int target) {
    #define sum(a,b,c) (nums[a] + nums[b] + nums[c])
    quick_sort(nums, 0, length - 1);
    int ans = 0;
    int a, k = 0;
    for (int k = 0; k < length - 2; k++) {
        for (int i = k + 1; i < length - 1; i++) {
            for (int j = i + 1; j < length; j++) {
                if(sum(i, k, j) < target) ans++;
                else break;
            }
        }
    }
    return ans;
}
int main() {
    int n, target;
    scanf("%d %d", &n, &target);
    int* num = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", num + i);
    }
    printf("%d\n", three_sum_smaller(num, n, target));
    free(num);
    return 0;
}