// Terms30: 透彻了解inlining的里里外外
#include <iostream>

// inline函数无需蒙受函数调用所招致的额外开销
// 但是inline函数会使目标代码增加 造成的代码膨胀会导致额外的换页行为 降低指令高速缓存装置的击中率
// 但是对于本体较小的inline函数 函数本体所产出的吗可能比函数调用的代码更小

// 隐喻的inline函数
class Person {
public:
    int age() const { return theAge; }     // 隐喻的inline
private:
    int theAge;
};

// 明确的inline函数
template<typename T>
inline const T& Max(const T& a, const T& b) 
{
    return a < b ? b : a;
}

// virtual函数一般来说不可以inline
// 因为virtual函数直到运行时才确定调用哪个函数
// inline是在执行前将调用动作替换成被调用函数本体 
// 看似inline的函数不一定真inlined 这取决于编译器

// 虽然编译器有可能inlining某个函数 但也有可能为函数生成一个函数本体
inline void f() {}
void (*pf)() = f;
// f();      该调用会被inline 因为是正常调用
// pf();     该调用不会被inline 因为是通过函数指针调用

// 构造函数和析构函数不是一个好的inline选择
class Base {
public:
    Base() {}
private:
    std::string bm1, bm2;
};

class Derived: public Base {
public:
    Derived() {}
private:
    std::string dm1, dm2, dm3;
};

// 空白构造函数的具象化
// Derived::Derived()
// {
//     Base::Base();
//     try { dm1.std::string::string(); }
//     catch (...) {
//         Base::~Base();
//         throw;
//     }
//     try { dm2.std::string::string(); }
//     catch (...) {
//         dm1.std::string::~string();
//         Base::~Base();
//         throw;
//     }
//     try { dm3.std::string::string(); }
//     catch (...) {
//         dm2.std::string::~string();
//         dm1.std::string::~string();
//         Base::~Base();
//         throw;
//     }
// }
// 编译器会使用更精细的代码处理异常 如果所有的构造函数都是inline的 
// Derived构造函数会展开多份构造函数的本体
