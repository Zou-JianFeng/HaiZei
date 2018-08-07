char str[1000];
char* longestCommonPrefix(char** strs, int strsSize) { 
    for (int i = 0; i < 1000; ++i) {
        str[i] = strs[0][i];
        for (int j = 1; j < strsSize; ++j) {
            if (str[i] != strs[j][i]) {
                str[i] = '\0';
                break;
                break;
            }
        }
    }
    return str;
}
/*
编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串 ""。
*/