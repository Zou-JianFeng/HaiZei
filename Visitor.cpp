#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class B;
class C;
// class D;

class A {
public :
	class IVisitor { // 访问者模式 减少bug
	public :
		virtual void Visit(B *) = 0;
		virtual void Visit(C *) = 0;
		// virtual void Visit(D *) = 0;
	};
	virtual void say() = 0;
	virtual void Accept(IVisitor *) = 0;
	virtual ~A() {
		cout << "A" << endl;
	}
};

class B : public A{
public :
	virtual void say() {
		cout << "B" << endl;
	}
	int getNum() {return this->num;}
	void setNum(int num) { this->num = num; }
	void Accept(A::IVisitor *vis) { vis->Visit(this); }
private :
	int num;
};

class C : public A{
public :
	virtual void say() {
		cout << "C" << endl;
	}
	double getN() {return this->n;}
	void setN(double n) { this->n = n;}
	void Accept(A::IVisitor *vis) { vis->Visit(this); }
private :
	double n;
};

class NumVisitor : public A ::IVisitor {
public :
	virtual void Visit(B *obj) {
		int num = obj->getNum();
		sprintf(buf, "%d", num);
		return ;
	}	
	virtual void Visit(C *obj) {
		double n = obj->getN();
		sprintf(buf, "%lf", n);
		return ;
	}
	char *getResult() { return this->buf; }
private :
	char buf[100];
};

class CountVisitor : public A ::IVisitor {
public :
	virtual void Visit(B *obj) {
		this->score = 1;
		return ;
	}	
	virtual void Visit(C *obj) {
		this->score = 2;
		return ;
	}
	int getscore() { return this->score; }
private :
	int score;
};

// 析构函数配合虚函数使用

int main() {
	srand(time(0));
	A *arr[10];
	for (int i = 0; i < 10; i++) {
		int op = rand() % 2; 
		switch (op) {
			case 0: 
				arr[i] = new B();
				dynamic_cast<B *>(arr[i])->setNum(rand() % 100);  // 没有虚函数表 不知道对象类型
				 break;
			case 1: 
				arr[i] = new C(); break;
				dynamic_cast<C *>(arr[i])->setN(rand() % 100 * 1.0 / 100); //
				 break;
		}
	}
	string str;
	NumVisitor n_vis;
	CountVisitor c_vis;
	int total = 0;
	int n;
	for (int i = 0; i < 10; i++) {

		arr[i]->Accept(&n_vis);
		arr[i]->Accept(&c_vis);
		str = str + " " + n_vis.getResult();
		total += c_vis.getscore();
	}
	cout << str << endl;
	cout << total << endl;
	return 0;
}
