// 描述
// 现有一整数集（允许有重复元素），初始为空。我们定义如下操作：

// add x 把x加入集合

// del x 把集合中所有与x相等的元素删除

// ask x 对集合中元素x的情况询问

// 对每种操作，我们要求进行如下输出。

// add 输出操作后集合中x的个数

// del 输出操作前集合中x的个数

// ask 先输出0或1表示x是否曾被加入集合（0表示不曾加入），再输出当前集合中x的个数，中间用空格格开。

// 输入
// 第一行是一个整数n，表示命令数。0<=n<=100000。

// 后面n行命令，如Description中所述。

// 输出
// 共n行，每行按要求输出。

#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;
    multiset<int> s;
    set<int> ever_added;
    while (n--)
    {
        string cmd;
        int x;
        cin >> cmd >> x;
        if (cmd == "add")
        {
            s.insert(x);
            ever_added.insert(x);
            cout << s.count(x) << endl;
        }
        else if (cmd == "del")
        {
            cout << s.count(x) << endl;
            s.erase(x);
        }
        else if (cmd == "ask")
        {
            cout << (ever_added.count(x) ? 1 : 0) << " " << s.count(x) << endl;
        }
    }
    return 0;
}