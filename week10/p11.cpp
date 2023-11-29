// 程序填空，使得下面的程序,先输出

// (Tom,80),(Tom,70),(Jone,90),(Jack,70),(Alice,100),

// (Tom,78),(Tom,78),(Jone,90),(Jack,70),(Alice,100),

// (70,Jack),(70,Tom),(80,Tom),(90,Jone),(100,Alice),

// (70,Error),(70,Error),(80,Tom),(90,Jone),(100,Alice),

// ******

// 然后，再根据输入数据按要求产生输出数据

#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
#include <typeinfo>
template <class T1, class T2, typename OP = std::greater<T1> >
class MyMultimap : public std::multimap<T1, T2, OP>
{
public:
    MyMultimap() : std::multimap<T1, T2, OP>(){};

    template <class T3, class T4>
    void Set(T3 in1, T4 in2)
    {
        typedef typename std::multimap<T1, T2, OP>::iterator iterator;
        iterator it = this->begin();
        if (typeid(T3) == typeid(std::string))
        {
            for (it = this->begin(); it != this->end();)
            {
                if (it->first == in1)
                {
                    this->insert(std::make_pair(it->first, in2));
                    this->erase(it++);
                }
                else
                {
                    ++it;
                }
            }
        }
        else
        {
            std::multimap<T1, T2, OP> temp;
            for (it = this->begin(); it != this->end(); ++it)
            {
                if (it->first == in1)
                {
                    temp.insert(std::make_pair(in1, in2));
                }
                else
                {
                    temp.insert(*it);
                }
            }
            this->clear();
            this->insert(temp.begin(), temp.end());
        }
    }
};

ostream &operator<<(ostream &o, const std::pair<const string, int> &s)
{
    o << "(" << s.first << "," << s.second << ")";
    return o;
}

ostream &operator<<(ostream &o, const std::pair<const int, string> &s)
{
    o << "(" << s.first << "," << s.second << ")";
    return o;
}





struct Student
{
    string name;
    int score;
};

template <class T>
void Print(T first, T last)
{
    for (; first != last; ++first)
        cout << *first << ",";
    cout << endl;
}
int main()
{

    Student s[] = {{"Tom", 80}, {"Jack", 70}, {"Jone", 90}, {"Tom", 70}, {"Alice", 100}};
    MyMultimap<string, int> mp;
    for (int i = 0; i < 5; ++i)
        mp.insert(make_pair(s[i].name, s[i].score));
    Print(mp.begin(), mp.end()); // 按姓名从大到小输出

    mp.Set("Tom", 78); // 把所有名为"Tom"的学生的成绩都设置为78
    Print(mp.begin(), mp.end());

    MyMultimap<int, string, less<int> > mp2;
    for (int i = 0; i < 5; ++i)
        mp2.insert(make_pair(s[i].score, s[i].name));

    Print(mp2.begin(), mp2.end()); // 按成绩从小到大输出
    mp2.Set(70, "Error");          // 把所有成绩为70的学生，名字都改为"Error"
    Print(mp2.begin(), mp2.end());
    cout << "******" << endl;

    mp.clear();

    string name;
    string cmd;
    int score;
    while (cin >> cmd)
    {
        if (cmd == "A")
        {
            cin >> name >> score;
            if (mp.find(name) != mp.end())
            {
                cout << "erroe" << endl;
            }
            mp.insert(make_pair(name, score));
        }
        else if (cmd == "Q")
        {
            cin >> name;
            MyMultimap<string, int>::iterator p = mp.find(name);
            if (p != mp.end())
            {
                cout << p->second << endl;
            }
            else
            {
                cout << "Not Found" << endl;
            }
        }
    }
    return 0;
}