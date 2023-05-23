// Terms26: 尽可能延后变量定义式的出现时间
#include <iostream>

// 计算通行密码的加密版本后返回的函数
// 密码不够长 返回logic_error异常
const int MinimumPasswordLength = 10;
std::string encryptPassword(const std::string& password)
{
    using namespace std;
    string encrypted;
    if (password.length() < MinimumPasswordLength) {
        throw logic_error("Password is to short");
    }   
    // 将加密后的密码放入变量encrypted中
    return encrypted;
}
// 上述代码的encrypted并未完全被使用
// 如果异常抛出 encrypted就完全不会被使用 但是需要付出构造和析构成本
// 延后encrypted的定义式
std::string encryptPassword(const std::string& password)
{
    using namespace std;
    if (password.length() < MinimumPasswordLength) {
        throw logic_error("Password is to short");
    }   
    string encrypted;
    // 将加密后的密码放入变量encrypted中
    return encrypted;
}
// 上述代码仍然不够纤秾合度 encrypted虽然定义却无任何实参作为初值
void encrypt(std::string& s);   // 对s进行加密
std::string encryptPassword(const std::string& password)
{
    using namespace std;
    if (password.length() < MinimumPasswordLength) {
        throw logic_error("Password is to short");
    }   
    std::string encrypted(password);
    encrypt(encrypted);
    return encrypted;
}

int main()
{
    class Widget {};
    const int n = 100;
    // 变量定义在循环内or循环外的选择
    // 方法A: 定义在循环外
    Widget w;
    for (int i = 0; i < n; ++i) {
        // w = 取决于i的某个值
    }
    // 代价: 1次构造函数 + 1次析构函数 + n次赋值操作

    // 方法B: 定义在循环内
    for (int i = 0; i < n; ++i) {
        // Widget w = 取决于i的某个值
    }
    // 代价: n次构造函数 + n次析构函数
    // 如果一个赋值成本低于一组构造+析构成本 A好
    // 否则A做法会使w的作用域更大 对程序的可理解性和易维护性造成冲突

    return 0;
}