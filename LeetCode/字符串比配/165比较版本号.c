int compareVersion(char* version1, char* version2) {
    int len1 = strlen(version1), len2 = strlen(version2);
    int i = 0, j = 0;
    while (1) {
        int a = 0, b = 0;
        while (i < len1 && version1[i] != '.') {
            a = a * 10 + (version1[i] - '0');
            ++i;
        }
        while (j < len2 && version2[j] != '.') {
            b = b * 10 + (version2[j] - '0');
            ++j;
        }
        if (a > b) return 1;
        else if (a < b) return -1;
        ++i;
        ++j;
        if (i >= len1 && j >= len2) break;
    }
    return 0;
}
/*
比较两个版本号 version1 和 version2。
如果 version1 > version2 返回 1，如果 version1 < version2 返回 -1， 除此之外返回 0。
*/