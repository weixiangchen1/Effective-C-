// Terms24: 若所有参数皆需类型转换，请为此采用non-member函数
#include <iostream>

class Rational {
public:
    Rational(int numerator = 0, int denominator = 1);   // 不声明为explicit 允许隐式类型转换
    int numerator() const;
    int denominator() const;

    // const Rational operator*(const Rational& rhs) const;  // pass-by-value
};

const Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.numerator() * rhs.numerator(), 
                    lhs.denominator() * rhs.denominator());
}

int main()
{
    Rational oneEighth(1, 8);
    Rational oneHalf(1, 2);
    Rational result = oneEighth * oneHalf;
    result = result * oneEighth;

    // member函数尝试混合运算符
    result = oneHalf * 2;   // right  result = oneHalf.operator*(2)  隐式类型转换
    result = 2 * oneHalf;   // error  result = 2.operator(oneHalf)

    // non-member函数尝试混合运算符
    result = oneHalf * 2;   
    result = 2 * oneHalf;   // 可以通过编译

    return 0;
}