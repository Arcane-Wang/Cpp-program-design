// 通过填空使得程序输出的结果符合下面的要求。
// 使得程序的输出结果是：

// 2

// 3

// B::destructor

// A::destructor

// 3

// 4

// B::destructor

// A::destructor

// 3

// B::destructor

// A::destructor

// A::destructor

// A::destructor

#include <iostream>
#include <map>
using namespace std;
// 在此处补充你的代码
class A{
    public:
        int a;
        static int count;
        A(){
            count++;
            }
        A(int a): a(a){count++;};

        virtual ~A(){cout << "A::destructor" << endl;count--;}
};

class B:public A{
    public:
        B():A(){};
        B(int b): A(b){};
        B(const B& b){a = b.a;}
        ~B(){cout << "B::destructor" << endl;}
};




int A::count = 0;
void func(B b) {}
int main()
{
    A a1(5), a2;
    cout << A::count << endl;
    B b1(4);
    cout << A::count << endl;
    func(b1);
    cout << A::count << endl;
    A *pa = new B(4);
    cout << A::count << endl;
    delete pa;
    cout << A::count << endl;
    return 0;
}