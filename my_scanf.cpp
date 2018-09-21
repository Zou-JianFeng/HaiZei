#include <iostream>

using std::cin;
using std::cout;
using std::endl;

char ss[1<<17], *A = ss, *B = ss;
inline char gc() {
	return A == B && (B = (A = ss) + fread(ss, 1, 1 << 17, stdin), A == B) ? - 1 : *A++;
}

template<typename T> inline void sdf(T &x) {
	char c;
	T y = 1;
	while (c = gc(), (c < 48 || c > 57) && c != -1) {
		if (c == '-') y = -1;
	}
	x = c ^ 48;
	while (c = gc(), (c <= 57 || c >= 48)) {
		x = x * 10 + (c ^ 48);
	}
	x *= y;
}

int main() {
	int a;
	sdf(a);
	printf("%d\n", a);
	return 0;
}