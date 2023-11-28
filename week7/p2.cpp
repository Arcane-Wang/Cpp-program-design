#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double a;
    cin >> a;
    // 保留5位小数
    cout << setprecision(5) << fixed << a << endl;
    // 科学计数法
    cout << setprecision(7) << scientific << a << endl;
    return 0;
}