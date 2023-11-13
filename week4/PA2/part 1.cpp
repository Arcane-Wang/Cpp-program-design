#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 在此处补充你的代码
    Complex& operator=(const char * s){
        char * p = new char[strlen(s) + 1];
        strcpy(p, s);
        char * p1 = strtok(p, "+");
        char * p2 = strtok(NULL, "i");
        r = atof(p1);
        i = atof(p2);
        delete [] p;
        return *this;
    }
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}