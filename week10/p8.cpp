// 输入整数 n ( 0 <=n<= 2^30) , 以及整数i,j(0 <= i,j <31,i < j-1), 输出整数k(按十六进制输出结果 )，k的第i位和n相同，第j位和n不同，i,j之间的位是1, 其他位都是0。这里提到的所有的位，指的都是二进制位，最右边算第0位。

// 输入
// 第一行是整数 t，表示数据组数。

// 每组输入数据是一行，三个整数 n,i和j。

// 输出
// 对每组输入数据，按十六进制输出结果。

#include <iostream>
// #include <bit>
using namespace std;

int main(int argc, char* argv[]) {
    int t;
    cin >> t;
    while (t--) {
        unsigned int n, i, j;
        cin >> n >> i >> j;
        unsigned int k = 0;
        k |= n & (1 << i);
        k |= (n & (1 << j)) ^ (1 << j);
        int temp = (((1 << j) - 1) ^ ((1 << (1 + i)) - 1)) % (1 << j);
        k |= temp;
        cout << hex << k << endl;
    }
    return 0;
}