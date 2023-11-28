#include <iostream>
using namespace std;
// 在此处补充你的代码
template <class T>
class CArray3D
{
private:
    T ***p;
    int x, y, z;
public:
    CArray3D(int a, int b, int c): x(a), y(b), z(c)
    {
        p = new T**[x];
        for (int i = 0; i < x; i++)
        {
            p[i] = new T*[y];
            for (int j = 0; j < y; j++)
            {
                p[i][j] = new T[z];
            }
        }
    }
    ~CArray3D()
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++) delete[] p[i][j];
            delete[] p[i];
        }
        delete[] p;

    }
    T** operator[](int i)
    {
        return p[i];
    }
};



int main()
{
    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                cout << a[i][j][k] << ",";
    return 0;
}