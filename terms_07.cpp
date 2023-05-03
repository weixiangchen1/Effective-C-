// Term07: 为多态基类声明virtual析构函数
// 带有多态性质的基类(带有任何virtual函数)应该声明一个virtual析构函数
// 如果类的设计不是为了作为基类亦或者不具有多态性 就不该声明virtual析构函数
#include <iostream>

class TimeKeeper {
public:
    virtual ~TimeKeeper();
};

// 如果不对TimeKeeper的析构函数用virtual修饰
// 在AtomicClock类getTimeKeeper方法调用返回一个指向heap上的
// 指针被父类TimeKeeper的指针ptk接收后 释放ptk
// 只会调用父类的析构函数 而子类的析构函数没有被调用
// 这就会导致AtomicClock的一部分资源没有被释放 造成资源泄露
TimeKeeper::~TimeKeeper()
{
    std::cout << "~TimeKeeper()" << std::endl;
}

class AtomicClock: public TimeKeeper {
public:
    static AtomicClock* getTimeKeeper()
    {
        return new AtomicClock();
    }

    ~AtomicClock()
    {
        std::cout << "~AtomicClock()" << std::endl;
    }
};
class WaterClock: public TimeKeeper {};
class WristWatch: public TimeKeeper {};


// 如果一个对象包含virtual函数 在对象里会多一个vptr(虚函数表指针)
// vptr指针指向一个由函数指针构成的数组 称为vtbl(虚函数表)
// vptr和vtbl的出现势必会占用一些内存空间
// 如果无端的讲析构函数设为virtual 对象的体积就会增加
// 且这会失去移植性 不再可能将对象传递给其他语言所写的函数
class Point {
public:
    Point(int xCoord, int yCoord);
    virtual ~Point();

private:
    int x, y;
};

// string不含任何virtual函数 如果当成base class会造成资源泄露
// STL容器都是non-virtual析构函数
class SpecialString: public std::string {
public:
    SpecialString(const char* str)
        :std::string(str)
    {}
};

// SpecialString* pss = new SpecialString("Impending Doom");
// std::string* ps = pss;
// delete ps;    // err 只会调用string析构 不会调用SpecialString析构

// 带有纯虚函数的抽象类
class AWOV {
public:
    virtual ~AWOV() = 0;  // 纯虚函数
};

AWOV::~AWOV() {}

int main()
{
    TimeKeeper* ptk = AtomicClock::getTimeKeeper();
    delete ptk;    

    // 未加virtual的size: 8
    // 加了virtual的size: 16
    std::cout << sizeof(Point) << std::endl;

    return 0;
}