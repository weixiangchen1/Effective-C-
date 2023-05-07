// Terms10: 令operator=返回一个reference to *this
#include <iostream>

// 为了实现连续赋值 赋值运算符需要返回一个reference指向操作符左侧实参
class Widget {
public:
    Widget& operator=(const Widget& rhs)
    {
        return *this;
    }

    // 这个协议适用于+=、-=、*=等
    Widget& operator+=(const Widget& rhs)
    {
        return *this;
    }
    // 这个协议不限制操作符的参数类型
    Widget& operator=(int rhs)
    {
        return *this;
    }
};


int main()
{
    int x, y, z;
    x = y = z = 15; // 连续赋值
    // 连续赋值采用右结合律
    // x = y = z = 15; => x = (y = (z = 15));

    return 0;
}