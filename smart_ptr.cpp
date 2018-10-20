#include <iostream>
using namespace std;

class A {
public :
	A() { cout << "A constructor" << endl; }
	~A() { cout << "A destructor" << endl; }
};

class B : public A {

};

namespace haizei {
	template<typename T> 
	class shared_ptr {
	public :
		// 初始化（3种）
		//  shared_ptr<A> p
		shared_ptr() {
			this->data = nullptr;
		}
		//  shared_ptr<A> p(new A())  
		shared_ptr(T *obj) {
			// this->data = new pair<T *, int>(obj, 1);
			this->data = obj;
			this->cnt = new int {1};
		} 
		// shared_ptr<A> p_(p) 
		shared_ptr(const shared_ptr<T> &p) {
			this->data = p.data;
			// this->data->second += 1;
			this->cnt = p.cnt;
			*(this->cnt) += 1;
		} 
		// q(p)
		template<typename Y> 
		shared_ptr(const shared_ptr<Y> &p) {
			p.set_ptr(this->data, this->cnt);
			*(this->cnt) += 1;
			// this->data = p.getData();
			// this->data = reinterpret_cast<T *>(&(*p));
			// this->cnt
			// this->data->second += 1;
		}


		// 重载运算符->
		T *operator->() {
			return this->data;
		}
		// 重载赋值运算符=    相同类型
		shared_ptr<T> &operator=(shared_ptr<T> &p) {
			if (p.data) *(p.cnt) += 1;
			if (this->data) {
				this->destory_ptr();
			}
			p.set_ptr(this->data, this->cnt);
			return *this;
		}
		// 重载赋值运算符= nullptr_t 空指针类型
		shared_ptr<T> &operator=(nullptr_t x) {
			if (this->data) this->destory_ptr();
			this->data = nullptr;
			return *this;
		}
		//重载赋值运算符= 子类赋给基类
		template<typename Y>  // 没有自己等于自己 可以先减
		shared_ptr<T> &operator=(shared_ptr<Y> &p) {
			if (this->data) this->destory_ptr();
			p.set_ptr(this->data, this->cnt);
			*(this->cnt)+= 1;
			return *this;
		}
		// 重载取解析*
		T operator*() {
			return *(this->data);
		}

		int use_count() {
			if (this->data == nullptr) return 0;
			return *(this->cnt);
		}

		template<typename Y>
		void set_ptr(Y *&obj, int *&cnt) const {
			obj = this->data;
			cnt = this->cnt;
			return ;
		}

		void destory_ptr() {
			if (!(*(this->cnt) -= 1)) {
				delete this->data;
				delete this->cnt;
				this->data = nullptr;
				this->cnt = nullptr;
			}
			return ;
		}
		~shared_ptr() {
			if (this->data == nullptr) return ;
			this->destory_ptr();
			return ;
		}

	private :
		// mutable pair<T *, int> *data;
		T *data;
		int *cnt;
	};
}

int main() {
	B *obj = new B();
	haizei::shared_ptr<B> p(obj);
	haizei::shared_ptr<A> q(p), p1;
	p1 = p;
	cout << p.use_count() << " " << q.use_count() << endl;
	p = nullptr;
	cout << "---------------" << endl;
	return 0;
}
