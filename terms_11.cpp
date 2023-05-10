// Terms11: 在operator=中处理"自我复制"
#include <iostream>

class Bitmap {
public:
    Bitmap();
    Bitmap(const Bitmap&);
};
class Widget {
public:
    Widget()
        :pb(new Bitmap())
    {}

    void swap(const Widget& rhs);

    Widget& operator=(const Widget& rhs);
    Widget& operator=(Widget rhs);
private:    
    Bitmap* pb;
};

// Widget& Widget::operator=(const Widget& rhs)
// {
//     delete pb;
//     pb = new Bitmap(*rhs.pb);   // *this和rhs有可能是同一个对象
//     return *this;
// }

// 添加一个"证同测试"
// new Bitmap仍然存在异常安全问题
// 如果new抛异常 pb就会指向一块已经被删除的空间 存在异常安全问题
Widget& Widget::operator=(const Widget& rhs)
{
    if (this == &rhs) return *this;

    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}

// 需注意在复制pb所指东西之前别删除pb
Widget& Widget::operator=(const Widget& rhs)
{
    Bitmap* pOrig = pb;    // 先保存原来的pb
    pb = new Bitmap(*rhs.pb);
    delete pOrig;
    return *this;
}

// copy and swap
Widget& Widget::operator=(const Widget& rhs)
{
    Widget temp(rhs);       // 创建一个局部变量
    swap(temp);             // 交换*this和temp的数据
    return *this;
}   // 函数退出临时变量的生命周期结束 temp将自动销毁

// 另一种写法 利用函数值传递
Widget& Widget::operator=(Widget rhs)
{
    swap(rhs);
    return *this;
}