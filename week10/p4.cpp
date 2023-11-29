// 下列程序每次读入一个整数N，若N为0则退出，否则输出N和N的平方

#include <iostream>
using namespace std;
// 在此处补充你的代码
class CType
{
    int n_;

public:
    void setvalue(int n) { n_ = n; };
    int operator++(int)
    {
        int tmp = n_;
        n_ *= n_;
        return tmp;
    }
    friend ostream &operator<<(ostream &os, const CType &c)
    {
        os << c.n_;
        return os;
    }
};

int main(int argc, char *argv[])
{
    CType obj;
    int n;
    cin >> n;
    while (n)
    {
        obj.setvalue(n);
        cout << obj++ << " " << obj << endl;
        cin >> n;
    }
    return 0;
}