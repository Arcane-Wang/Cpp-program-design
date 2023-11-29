// 输入
// 第一行是正整数T，表示测试数据的组数

// 每组测试数据输入共两行，

// 第一行是正整数N，表示字符串个数

// 第二行是N个字符串, 字符串间用空格分离

// 输出
// 对于每组测试数据，先输出一行：

// Case: n

// 如对第一组数据就输出Case: 1

// 第二行按照字符串长度从小到大排序之后输出N个字符串，字符串之间以空格间隔（不会出现字符串长度相同的情况）

// 第三行按照字符串首字符ASCII码序从小到大排序之后输出N个字符串，字符串之间以空格间隔（不会出现字符串首字母相同的情况）

#include <iostream>
#include <string>
#include <list>
using namespace std;

class A{
private:
        string name;
public:
        A(string n) :name(n){}
        friend bool operator < (const class A& a1, const class A &a2);
        friend bool operator == (const class A &a1, const class A &a2){
                if (a1.name.size() == a2.name.size())
                        return true;
                else
                        return false;
        }
        friend ostream & operator << (ostream &o, const A &a){
                o << a.name;
                return o;
        }
        string get_name() const{
                return name;
        }
        int get_size() const{
                return name.size();
        }
};
// 在此处补充你的代码
bool operator < (const class A& a1, const class A &a2) {
        return a1.get_size() < a2.get_size();
}

template <class T>
class MyLarge {
public:
        bool operator()(const T &a1, const T &a2) {
                return a1.get_name() < a2.get_name();
        }
};


class Print {
public:
        void operator()(const A &a) {
                cout << a << " ";
        }
};

template <class T>
void Show(T begin, T end, Print p) {
        for (T it = begin; it != end; it++) {
                p(*it);
        }
}

int main(int argc, char* argv[])
{
        list<A> lst;
        int ncase, n, i = 1;
        string s;
        cin >> ncase;
        while (ncase--){
                cout << "Case: "<<i++ << endl;
                cin >> n;
                for (int i = 0; i < n; i++){
                         cin >> s;
                         lst.push_back(A(s));
                }
                lst.sort();
                Show(lst.begin(), lst.end(), Print());

                cout << endl;
                lst.sort(MyLarge<A>());
                Show(lst.begin(), lst.end(), Print());
                cout << endl;
                lst.clear();
        }
        return 0;
}