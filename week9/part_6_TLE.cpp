// 描述
// 我们定义一个正整数a比正整数b优先的含义是：

// *a的质因数数目（不包括自身）比b的质因数数目多；

// *当两者质因数数目相等时，数值较大者优先级高。

// 现在给定一个容器，初始元素数目为0，之后每次往里面添加10个元素，每次添加之后，要求输出优先级最高与最低的元素，并把该两元素从容器中删除。

// 输入
// 第一行: num (添加元素次数，num <= 30)

// 下面10*num行，每行一个正整数n（n < 10000000).

// 输出
// 每次输入10个整数后，输出容器中优先级最高与最低的元素，两者用空格间隔。

// 样例输入
// 1
// 10 7 66 4 5 30 91 100 8 9

// 样例输出
// 66 5

// 虽然下面的代码超时了,但为了用priority_queue完成，自己写了一个custom_priority_queue类，继承自priority_queue，重写了remove方法，可以作为继承系统模板类的例子

#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm>

#define USE_INPUT_FILE 1

using namespace std;

class cmp
{
    int aa, bb;

public:
    cmp(int a, int b) : aa(a), bb(b) {}
    bool operator()(const int a1, const int b1) const
    {   int a = a1, b = b1;
        int cnt_a = 0, cnt_b = 0;
        int i = 2;
        while (i < a1 && i <= a)
        {
            if (a % i == 0)
            {
                cnt_a++;
                while (a % i == 0)
                    a /= i;
            }
            
            i++;
        }
        i = 2;
        while (i < b1 && i <= b)
        {
            if (b % i == 0)
            {
                cnt_b++;
                while (b % i == 0)
                    b /= i;
            }
            
            i++;
        }
        if (cnt_a != cnt_b)
            return cnt_a < cnt_b;
        else
            return a1 < b1;
    }
};

class cmp1
{
    int a, b;
    
    public:
    cmp1(int a, int b) : a(a), b(b) {}
        bool operator()(const int a1, const int b1) const
    {   int a = a1, b = b1;
        int cnt_a = 0, cnt_b = 0;
        int i = 2;
        while (i < a1 && i <= a)
        {
            if (a % i == 0)
            {
                cnt_a++;
                while (a % i == 0)
                    a /= i;
            }
            
            i++;
        }
        i = 2;
        while (i < b1 && i <= b)
        {
            if (b % i == 0)
            {
                cnt_b++;
                while (b % i == 0)
                    b /= i;
            }
            
            i++;
        }
        if (cnt_a != cnt_b)
            return cnt_a > cnt_b;
        else
            return a1 > b1;
    }
};

template<class T, class OP>
class custom_priority_queue : public std::priority_queue<T, std::vector<T>, OP>
{
  public:
      custom_priority_queue(const OP& op) : std::priority_queue<T, std::vector<T>, OP>(op) {}

      bool remove(const T& value) {
          typename std::vector<T>::iterator it = std::find(this->c.begin(), this->c.end(), value);
       
          if (it == this->c.end()) {
              return false;
          }
          if (it == this->c.begin()) {
              // pop the top element
              this->pop();
          }    
          else {
              // remove element and re-heap
              this->c.erase(it);
              std::make_heap(this->c.begin(), this->c.end(), this->comp);
         }
         return true;
     }
};

int main()
{
    #if USE_INPUT_FILE
    ifstream inputFile("in.txt");
    int num;
    inputFile >> num;
    // cmp c(1,1); // 1,1是随便给的, 只是为了验证用非默认构造函数时priority_queue的用法
    // priority_queue<int, vector<int>, cmp> pq(c);
    // cmp1 c1(1,1);
    // priority_queue<int, vector<int>, cmp1> pq1(c1);

    // 以下是用自定义的priority_queue的用法，因为priority_queue没有remove方法，所以自己写了一个
    cmp c(1,1); // 1,1是随便给的, 只是为了验证用非默认构造函数时priority_queue的用法
    custom_priority_queue<int, cmp> pq(c);
    cmp1 c1(1,1);
    custom_priority_queue<int, cmp1> pq1(c1);
    while (num--)
    {
        for (int i = 0; i < 10; i++)
        {
            int n;
            inputFile >> n;
            pq.push(n);
            pq1.push(n);
        }
        int temp1 = pq.top();
        int temp2 = pq1.top();
        cout << temp1 << " ";
        cout << temp2 << endl;
        
        pq.pop();
        pq1.pop();
        pq.remove(temp2);
        pq1.remove(temp1);
    }
    return 0;

    #else
    int num;
    cin >> num;

    cmp c(1,1); // 1,1是随便给的, 只是为了验证用非默认构造函数时priority_queue的用法
    custom_priority_queue<int, cmp> pq(c);
    cmp1 c1(1,1);
    custom_priority_queue<int, cmp1> pq1(c1);
    while (num--)
    {
        for (int i = 0; i < 10; i++)
        {
            int n;
            cin >> n;
            pq.push(n);
            pq1.push(n);
        }
        int temp1 = pq.top();
        int temp2 = pq1.top();
        cout << temp1 << " ";        
        cout << temp2 << endl;
        
        pq.pop();
        pq1.pop();
        pq.remove(temp2);
        pq1.remove(temp1);
    }
    return 0;
    #endif
}