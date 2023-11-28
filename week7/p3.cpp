#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    int a;
    cin >> a;
    // 16进制
    cout << hex << a << endl;
    // 10 个字符宽度，右对齐，多余的用 0 填充
    cout << setw(10) << setfill('0') << dec << a << endl;

    return 0;
}