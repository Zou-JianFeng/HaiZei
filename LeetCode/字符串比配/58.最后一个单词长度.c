int lengthOfLastWord(char* s) {
    int ans = 0, n = strlen(s); 

    for (int i = n - 1; s[i]; --i) {
        if (s[i] != ' ') {
            for (int j = i; s[j]; --j, --i) {
                if (s[j] != ' ') ans += 1;
                else return ans;
            }
        }
    }
    return ans;
}
/*
给定一个仅包含大小写字母和空格 ' ' 的字符串，返回其最后一个单词的长度。

如果不存在最后一个单词，请返回 0 。
*/