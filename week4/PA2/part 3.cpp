#include <iostream>
#include <cstring>
using namespace std;
// 在此处补充你的代码
class Array2 {
    private:
        int ** p;
        int row, col;
    
    public:
        Array2(int r = 0, int c = 0): row(r), col(c) {
            if (r == 0 || c == 0) {
                p = NULL;
                return;
            }
            p = new int * [r];
            for (int i = 0; i < r; i++) {
                p[i] = new int [c];
            }
        }
        Array2(Array2 & a) {
            row = a.row;
            col = a.col;
            if (row == 0 || col == 0) {
                p = NULL;
                return;
            }
            p = new int * [row];
            for (int i = 0; i < row; i++) {
                p[i] = new int [col];
            }
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col;j++) {
                    p[i][j] = a.p[i][j];
                }
            }
        }
        ~Array2() {
            if (p == NULL) {
                return;
            }
            for (int i = 0; i < row; i++) {
                delete [] p[i];
            }
            delete [] p;
        }
        int * & operator[](int i) {
            return p[i];
        }
        int & operator()(int i, int j) {
            return p[i][j];
        }
        Array2 & operator=(Array2 & a) {
            if (p == a.p) {
                return *this;
            }
            if (p != NULL) {
                for (int i = 0; i < row; i++) {
                    delete [] p[i];
                }
                delete [] p;
            }
            row = a.row;
            col = a.col;
            if (row == 0 || col == 0) {
                p = NULL;
                return *this;
            }
            p = new int * [row];
            for (int i = 0; i < row; i++) {
                p[i] = new int [col];
            }
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col;j++) {
                    p[i][j] = a.p[i][j];
                }
            }
            return *this;
        }
};


int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}