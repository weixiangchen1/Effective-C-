// Terms27: 尽量少做转型动作
#include <iostream>
#include <vector>
#include <memory>

// 旧式转型:
// C风格的转型动作:     (T)expression
// 函数风格的转型动作:   T(expression)

// C++的新式转型:
// const_cast<T>( expression ): 去除对象的常量性
// static_cast<T>( expression ): 强迫隐式转换
// dynamic_cast<T>( expression ): 安全向下转型
// reinterpret_cast<T>( expression ): 执行低级转型
// 旧式转型虽然合法 但是新式转型更受欢迎：
// 1. 更容易在代码中被辨识出来
// 2. 各转型动作的目标愈窄化 编译器愈可能诊断出错误的运用
// 比如如果想要把常量性去掉 除非使用新式转型的const_cast否则无法通过编译

class Base {};
class Derived: public Base {};

class Window {
public:
    virtual void blink() {}
    virtual void onResize() {}
};
class SpecialWindow: public Window {
public:
    virtual void blink() {}
    virtual void OnResize() {
        static_cast<Window>(*this).onResize();   // 将*this转型为Window调用其onResize
        // 但是并不会如你所愿 调用的是"*this对象之base class成分"的暂时副本的onResize
    }
    // 正确写法：
    virtual void OnResize() {
        Window::onResize();
    }
};


int main() 
{
    Derived d;
    Base* pb = &d;
    // 单一对象可能拥有一个以上的地址 
    // 对象在C++中如何布局 是随编译器的 不应该作出任何转型动作

    typedef std::vector<std::shared_ptr<Window>> VPW;
    VPW winPtrs;
    for (VPW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
        (*iter)->blink();     // 减少使用dynamic_cast  dynamic_cast的许多实现版本执行速度相当慢

    // 避免使用连串的dynamic_cast 代码又大又慢
    for (VPW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
    {
        if (SpecialWindow* psw1 = dynamic_cast<SpecialWindow*>(iter->get())) {}
        else if (SpecialWindow* psw2 = dynamic_cast<SpecialWindow*>(iter->get())) {}
        else if (SpecialWindow* psw3 = dynamic_cast<SpecialWindow*>(iter->get())) {}
    }


    return 0;
}