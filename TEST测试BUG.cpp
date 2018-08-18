#include<stdio.h>
//void x(char *a, char *b) {
  // printf("[%s : %s] run\n", a, b);
//}
#include "test.h"
int add(int a, int b) {
    return a + b;
}
int is_prime(int x) {
    if(x < 2) return 0;
    for(int i = 2; i * i <= x; ++i) {
        if(x % i == 0) return 0;
    }
    return 1;
}
int binary_search(int min, int max, int n) {
    int array[max + 5];

    if (min >= max) return -1;
    for (int i = min; i <= max; i++) {
        array[i] = i;
    }

    int mid = (min + max) / 2;

    while(min <= max) {
        if (array[mid] == n) {return 1; break;}
        if (array[mid] < n) min = mid + 1;
        if (array[mid] > n) max = mid - 1;
        mid = (min + max) / 2;
    }
    return 0;
}

TEST(test, is_prime) {
    EXPECT(is_prime(2), 1); 
    EXPECT(is_prime(3), 1); 
    EXPECT(is_prime(971), 1);

}

TEST(test, add_func) {
    EXPECT(add(1, 2), 3); 
    EXPECT(add(3, 4), 7); 
    EXPECT(add(2, 2), 3);
}


TEST(test, binary_search) {
    EXPECT(binary_search(1, 6, 5), 1);
    EXPECT(binary_search(-6, -1, -5), 1);
    EXPECT(binary_search(0, 1, 15), 1);
    EXPECT(binary_search(20, 30, 50), 1);
    EXPECT(binary_search(-100000, 1000000, 50), 1);
}

int main() {
    return RUN_ALL_TEST();
}