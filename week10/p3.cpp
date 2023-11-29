// 请写出sum函数，使其可以计算输入数列的平方和。

#include <iostream>
using namespace std;
// 在此处补充你的代码
int(*fp)(int);
int sum(int a[], int n, int(*fp)(int)){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += fp(a[i]);
    }
    return sum;
}


int sqr(int n)
{
    return n * n;
}
int main()
{
    int t, n, a[0x100];
    cin >> t;
    for (int c = 0; c < t; ++c)
    {
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        cout << sum(a, n, sqr) << endl;
    }
    return 0;
}