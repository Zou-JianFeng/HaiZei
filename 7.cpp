#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class Father {
	public :
		int f;
		Father(int v) : f(v){
			cout << &f << endl;
		}
		void print() {
			cout << "fatehr" << endl;
		}
		int add(int v) {
			f += v;
			return f;
		}
		int add() {
			return f;
		}
};

class Child : public Father {
	public :
		int f;
		Child(int v) : Father(v), f(v) {
			cout << &f << endl;
		}
		void print() {
			cout << "child" << endl;
		}
		int add(int v1, int v2) {
			f += (v1 + v2);
			return f;
		}
		int add(int v1, int v2, int v3) {
			f += (v1 + v2 + v3);
			return f;
		}
};

int main() {
	Child c(5);
	c.f = 100;
	cout << c.f << " " << c.Father::f << endl;
	c.Father::f = 1000;
	// cout << &c.f << endl;
	// cout << sizeof(c.f) << endl;
	// cout << &c.Father::f << endl;
	// cout << sizeof(c.Father::f) << endl;
	c.print();
	//c.add(1);
	c.Father::add();
	//c.add


	return 0;
}