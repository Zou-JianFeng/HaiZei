void swap(char *a, char *b) {
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
char* reverseString(char* s) {
    int j = strlen(s) - 1, i = 0;
    while (i < j) {
        swap(&s[i++], &s[j--]);
    }
    return s;
}
/*
请编写一个函数，其功能是将输入的字符串反转过来。
*/