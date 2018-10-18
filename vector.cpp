#include <iostream>

using namespace std;

class Data {
public :
	Data() {
		cout << "data constructor" << endl;
		this->x = 6;
		this->data = new int(0);
	}
	Data(const Data &obj) {
		cout << "data copy constructor" << endl;
		this->x = 7;
		this->data = new int(0);
		*(this->data) = *(obj.data);
	}
	friend ostream &operator<<(ostream &, const Data &);
	~Data() {
		delete this->data;
	}
private :
	int x;
	int *data;
};

ostream &operator<<(ostream &out, const Data &obj) {
	cout << "(" << obj.x << ", " << obj.data << ")"<<endl;
	return out;
}

template<typename T> 
class Array{
public :
	Array() : Array(10) {}
	Array(int n) {
		this->n = n;
		this->data = new T[this->n];
	}
	Array(const Array &arr) : n(0){
		this->operator=(arr);
	}
	Array(Array &&arr) : n(0){
		this->operator=(move(arr));
	}
	T &operator[](int ind) {
		if (ind < 0 || ind >= this->n) return this->NIL;
		return this->data[ind];
	}
	Array<T> operator+(const Array &arr) {  // 返回一个右值
		Array<T> parr(this->n + arr.n); 
		// parr->n = this->n + arr.n;
		// parr->data = new T[parr->n];
		for (int i = 0; i < this->n; i++) {
			new(parr.data + i) T(this->data[i]);
		}
		for (int i = 0; i < arr.n; i++) {
			new(parr.data + i + this->n) T(arr.data[i]);
		}
		return move(parr);  // 改成move
	}

	Array<T> &operator=(const Array &arr) {   // 改成右值
		this->~destory();
		this->n = arr.n;
		this->data = new T[this->n];
		for (int i; i < this->n; i++) {
			new(this->data + i) T(arr.data[i]);
		}
		return *this;
	}
	Array<T> &operator=(Array &&arr) {   // 改成右值
		this->~destory();
		this->n = arr.n;
		this->data = arr.data;
		arr.data = nullptr;
		arr.n = 0;
		return *this;
	}
	void output() {
		printf("[");
		for (int i = 0; i < this->n; i++) {
			cout << this->data[i] << " ";
		}
		printf("]\n");
	}
	int size() { return this->n; }
	void destory() {
		if (this->n <= 0) return ;
		this->n = 0;
		delete[] this->data;
		return ;
	}
	~Array() {
		this->destory();
	}
private :
	T NIL;
	T *data;
	int n;
};

int main() {
	Array<Data> arr_a(5);
	Array<Data> arr_b(5);
	Array<Data> arr_c(arr_a + arr_b);
 	// arr_c = arr_a + arr_b;
 	arr_c.output();
	return 0;
}
