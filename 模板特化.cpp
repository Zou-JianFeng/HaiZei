#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <typename T>
T add(T a, T b) {
	cout << "1" << endl;
	return a + b;
}

template < >
int add (int a, int b) {
	cout << "2" << endl;
	return a + b;
}

int add (int a, int b) {
	cout << "3" << endl;
	return a + b;
}

int main() {
	double a = 0.1, b = 0.2, c;
	c = add(a, b);
	int x = 1, y = 2, z;
	z = add(x, y);

	return 0;
}
