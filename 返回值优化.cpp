/*************************************************************************
	> File Name: main.cpp
	> Author: 从今启智
	> Mail: weirufeng@haizeix.com
	> Created Time: 四  9/20 19:21:34 2018
    > Description: 
    >              
 ************************************************************************/

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;
class Test {
    private:
        int a;
    public:
        Test(int a);
        Test();
        Test(const Test &obj);
        void show();
        ~Test();
};

Test::Test(int a): a(a) {
    cout << "Test(int a)" << endl;
}

Test::Test() {
    cout << "Test()" << endl;
   // Test(100); // 直接调用构造函数，产生临时对象
}
Test::Test(const Test &obj) {
    cout << "Test(const Test &obj)" << endl;
}
void Test::show() {
    cout << "a = " << a << endl;
}
Test::~Test() {
    cout << "~Test()" << endl;
}

Test f() {
    Test temp;
    return temp;
}

void set(Test t) {
    
}


int main() {
    cout << "cpp begin" << endl;
    cout << "直接调用构造函数" << endl;
    Test t = Test(100); 
    // Test t = 100;
                        // 分析：
                        // 1、生成一个Test(100)的临时对象，调用带参数构造函数；
                        //2、t生成对象调用无参数构造函数，
                        //3、用临时对象去初始化t，调用拷贝构造函数
                        //t = 临时对象 =等价于 =》 t = 100； 编译器给做了
    t.show();
    cout << "返回值调用：" << endl;
    Test tt = f();  // 分析
                    // 1、生成一个临时对象,调用有参数构造
                    // 2、返回值生成一个临时对象。
                    // 3、tt调用无参数构造
                    // 4、临时对象初始化tt，调用拷贝构造函数
    Test a(10);
    cout << "传参数调用：" << endl;
    set(a); // 直接调用拷贝构造函数
    cout << "cpp end " << endl;
    return 0;
}

