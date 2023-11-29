// 使以下代码输出结果为200.

#include<iostream>
using namespace std;
class Number {
public:
    int num;
    Number(int n=0): num(n) {}
// 在此处补充你的代码
    Number operator*(const Number & n) {
        return Number(num * n.num);
    }
    operator int() {
        return num;
    }
    Number & operator=(const Number & n) {
        num = n.num;
        return *this;
    }
};

int main() {
    Number n1(10), n2(20);
    Number n3;n3 = n1*n2;
    cout << int(n3) << endl;
    return 0;
}