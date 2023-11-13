// 描述
// 给出两个正整数以及四则运算操作符（+ - * /），求运算结果。

// 输入
// 第一行：正整数a，长度不超过100
// 第二行：四则运算符o，o是“+”，“-”，“*”，“/”中的某一个
// 第三行：正整数b，长度不超过100

// 保证输入不含多余的空格或其它字符
// 输出
// 一行：表达式“a o b”的值。

// 补充说明：
// 1. 减法结果有可能为负数
// 2. 除法结果向下取整
// 3. 输出符合日常书写习惯，不能有多余的0、空格或其它字符

#include <iostream>
#include <cstring>
using namespace std;

class BigInt
{
private:
    int *num;
    int size;
    bool isPositive;

public:
    BigInt(const char *s)
    {
        int len = strlen(s);
        num = new int[len];
        isPositive = true;
        for (int i = 0; i < len; i++)
        {
            num[i] = s[len - i - 1] - '0';
        }
        size = len;
    }

    ~BigInt()
    {
        delete[] num;
    }

    BigInt &calculate(BigInt &b, char o)
    {
        switch (o)
        {
        case '+':
            *this = *this + b;
            break;
        case '-':
            *this = (*this - b);
            break;
        case '*':
            *this = *this * b;
            break;
        case '/':
            *this = *this / b;
            break;
        }
        return *this;
    }

    BigInt &operator+(const BigInt &b)
    {
        int len = size > b.size ? size : b.size;
        int *res = new int[len + 1];
        for (int i = 0; i < len + 1; i++)
        {
            res[i] = 0;
        }
        for (int i = 0; i < len; i++)
        {
            if (i < size)
            {
                res[i] += num[i];
            }
            if (i < b.size)
            {
                res[i] += b.num[i];
            }
            if (res[i] >= 10)
            {
                res[i + 1] += res[i] / 10;
                res[i] %= 10;
            }
        }
        if (res[len] == 0)
        {
            len--;
        }
        delete[] num;
        num = res;
        size = len + 1;
        return *this;
    }

    BigInt &operator-(BigInt &b)
    {
        if (b > *this)
        {
            isPositive = false;
            *this = b - *this;
            return *this;
        }
        int len = size > b.size ? size : b.size;
        int *res = new int[len];
        for (int i = 0; i < len; i++)
        {
            res[i] = 0;
        }
        for (int i = 0; i < len; i++)
        {
            if (i < size)
            {
                res[i] += num[i];
            }
            if (i < b.size)
            {
                res[i] -= b.num[i];
            }
            if (res[i] < 0)
            {
                res[i + 1] -= 1;
                res[i] += 10;
            }
        }
        while (res[len - 1] == 0 && len > 1)
        {
            len--;
        }
        delete[] num;
        num = res;
        size = len;
        return *this;
    }

    BigInt &operator*(const BigInt &b)
    {
        int len = size + b.size;
        int *res = new int[len];
        for (int i = 0; i < len; i++)
        {
            res[i] = 0;
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < b.size; j++)
            {
                res[i + j] += num[i] * b.num[j];
                if (res[i + j] >= 10)
                {
                    res[i + j + 1] += res[i + j] / 10;
                    res[i + j] %= 10;
                }
            }
        }
        while (res[len - 1] == 0 && len > 1)
        {
            len--;
        }
        delete[] num;
        num = res;
        size = len;
        return *this;
    }

    BigInt &operator/(BigInt &b)
    {
        int len = std::max(1, size - b.size + 1);
        int *res = new int[len];
        for (int i = 0; i < len; i++)
        {
            res[i] = 0;
        }
        BigInt tmp("0");
        for (int i = size - 1; i >= 0; i--)
        {
            tmp = tmp * BigInt("10");
            tmp.num[0] = num[i];
            while (tmp >= b)
            {
                tmp = tmp - b;
                res[i]++;
            }
        }
        while (res[len - 1] == 0 && len > 1)
        {
            len--;
        }

        delete[] num;
        num = res;
        size = len;
        return *this;
    }

    bool operator>=(const BigInt &b)
    {
        if (size > b.size)
        {
            return true;
        }
        if (size < b.size)
        {
            return false;
        }
        for (int i = size - 1; i >= 0; i--)
        {
            if (num[i] > b.num[i])
            {
                return true;
            }
            if (num[i] < b.num[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator>(const BigInt &b)
    {
        if (size > b.size)
        {
            return true;
        }
        if (size < b.size)
        {
            return false;
        }
        for (int i = size - 1; i >= 0; i--)
        {
            if (num[i] > b.num[i])
            {
                return true;
            }
            if (num[i] < b.num[i])
            {
                return false;
            }
        }
        return false;
    }

    BigInt &operator=(const BigInt &b)
    {
        if (this == &b)
        {
            return *this;
        }
        if (num != NULL)
        {
            delete[] num;
        }
        size = b.size;
        num = new int[size];
        for (int i = 0; i < size; i++)
        {
            num[i] = b.num[i];
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const BigInt &obj);
};

ostream &operator<<(ostream &os, const BigInt &obj)
{
    if (!obj.isPositive)
    {
        os << '-';
    }
    for (int i = obj.size - 1; i >= 0; i--)
    {
        os << obj.num[i];
    }
    return os;
}

int main()
{
    char *a, *b, o;
    a = new char[101];
    b = new char[101];
    cin >> a >> o >> b;
    BigInt A(a), B(b);
    delete[] a;
    delete[] b;
    cout << A.calculate(B, o);

    return 0;
}