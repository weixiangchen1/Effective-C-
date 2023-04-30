// Terms06: 若不想使用编译器自动生成的函数 应该明确拒绝
#include <iostream>

// class HomeForSale {
// public:
//     // ...
// private:
//     // 只声明不定义 并将函数设为私有 
//     HomeForSale(const HomeForSale&);
//     HomeForSale& operator=(const HomeForSale&);
// };

// 设计专门阻止copying动作的base class
class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable (const Uncopyable&);
    Uncopyable& operator=(const Uncopyable);
};

// 要阻止HomeForSale对象被拷贝 需要继承Uncopyable
// 但这种方法可能导致多重继承
class HomeForSale: private Uncopyable {
    // ...
};

int main()
{
    HomeForSale hfs;
    // HomeForSale copy(hfs);  通过继承Uncopyable类防拷贝

    return 0;
}