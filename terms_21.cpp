// Terms21: 必须返回对象时 别妄想返回其reference
// 绝不要以pointer或reference返回local stack对象 
// 或返回reference返回一个heap-allocated对象
// 或返回pointer或reference最小一个local static对象
#include <iostream>

// 表现有理数的class
class Rational {
public:
    Rational(int numerator = 0, int denominator = 1);
private:
    int n, d;

    // 实现返回reference的三个版本 达到避免构造函数和析构函数的目标
    // 1. on-the-stack
    // friend const Rational& operator*(const Rational& lhs, 
    //     const Rational& rhs)
    // {
    //     Rational result(lhs.n * rhs.n, lhs.d * rhs.n);
    //     return result;
    // }
    // warning！！
    // 目标是为了避免构造函数和析构函数 result却需要对象一下被构造出来
    // result是local对象 函数退出就销毁了
    // 返回的reference指向的是不明确的Rational 将会造成"无定义行为"

    // 2. on-the-heap
    // friend const Rational& operator*(const Rational& lhs, 
    //     const Rational& rhs)
    // {
    //     Rational* result = new Rational(lhs.n * rhs.n, lhs.d * rhs.n);
    //     return *result;
    // }
    // warning！！
    // new对象同样付出了析构函数的代价
    // 对于new出来的对象 谁来delete是不明确的 容易造成内存泄漏

    // 3. 返回函数内部的static对象
    // friend const Rational& operator*(const Rational& lhs, 
    //     const Rational& rhs)
    // {
    //     static Rational result;
    //     // ...
    //     return result;
    // }
    // warning！！
    // 如果用户写出如下代码:
    // bool operator==(const Rational& lhs, const Rational& rhs);
    // Rantinoal a, b, c, d;
    // if ((a * b) == (c * d)) {}
    // else {}
    // (a * b) == (c * d)总是被核算为true 因为对象是static的
    
    // 正确做法 -- 使用pass-by-value方式
    friend const Rational operator*(const Rational& lhs, 
        const Rational& rhs)
    {
        return Rational(lhs.n * rhs.n, lhs.d * rhs.n);
    }
};
