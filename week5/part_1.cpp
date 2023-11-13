#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class MyString:public string{
public:
    MyString():string(){}

    MyString(const char * s):string(s){}

    MyString(const MyString & s):string(s){}

    MyString(const string & s):string(s){}

    MyString operator()(int start, int length){
        return MyString(this->substr(start, length));
    }

    MyString & operator=(const char * s){
        string::operator=(s);
        return *this;
    }

    MyString & operator=(const MyString & s){
        string::operator=(s);
        return *this;
    }

    MyString operator+(const MyString & s){
        MyString temp;
        temp = *this;
        temp.append(s);
        return temp;
    }

    MyString operator+(const char * s){
        MyString temp;
        temp = *this;
        temp.append(s);
        return temp;
    }

    friend MyString operator+(const char * s, const MyString & ms){
        MyString temp;
        temp = s;
        temp.append(ms);
        return temp;
    }

    MyString & operator+=(const char * s){
        this->append(s);
        return *this;
    }

    MyString & operator+=(const MyString & s){
        this->append(s);
        return *this;
    }

    // friend ostream & operator<<(ostream & os, const MyString & s){
    //     os << s.c_str();
    //     return os;
    // }
};


bool CompareString(const MyString & s1, const MyString & s2) {
    return s1 < s2;
}

int main() {
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
    MyString SArray[4] = {"big","me","about","take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3;    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;    s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;
    std::sort(SArray,SArray+4,CompareString);
    for( int i = 0;i < 4;++i )
        cout << SArray[i] << endl;
    //输出s1从下标0开始长度为4的子串
    cout << s1(0,4) << endl;
    //输出s1从下标为5开始长度为10的子串
    cout << s1(5,10) << endl;
    return 0;
}