// 对人群按照输入的信息进行排序和分类。

#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class A
{
public:
    int age;
    char id;
    A(int k) : age(k), id('A'){};
};

class B : public A
{
public:
    B(int k) : A(k) { id = 'B'; }
};

class Comp
{
public:
    bool operator()(const A *a, const A *b) const
    {
        return a->age < b->age;
    }
};

// bool Comp(const A* a, const A* b){
//     return a->age < b->age;
// }

void Print(A *a)
{
    cout << a->id << " " << a->age << endl;
}

int main()
{
    int t;
    cin >> t;
    set<A *, Comp> ct;
    // set<A*, bool(*)(const A*, const A*)> ct(Comp);
    while (t--)
    {
        int n;
        cin >> n;
        ct.clear();
        for (int i = 0; i < n; ++i)
        {
            char c;
            int k;
            cin >> c >> k;

            if (c == 'A')
                ct.insert(new A(k));
            else
                ct.insert(new B(k));
        }
        for_each(ct.begin(), ct.end(), Print);
        cout << "****" << endl;
    }
}