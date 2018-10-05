#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Test{
public:
	Test(int v1, int v2) : a(v1), b(v2) {
		cout << "Test(int v1, int v2)" << endl;
	}
	friend bool setValue(Test &obj1, int v1, int v2);
	bool getA(int &v) {
		bool ret = (v = a);
		return ret;
	}

	bool getB(int &v) {
		bool ret = (v = b);
		return ret;
	}

private:
	int a, b;
};

bool setValue(Test &obj1, int v1, int v2) {
	bool ret = (obj1.a = v1)&&(obj1.b = v2);
	return ret;
}

int main() {
	Test t(1, 3);
	int a = 0;
	int b = 0;
	t.getA(a);
	t.getA(b);
	cout << a << " " << b << endl;
	setValue(t, 2, 4);
	t.getA(a);
	t.getB(b);
	cout << a << " " << b << endl;

	return 0;
}
