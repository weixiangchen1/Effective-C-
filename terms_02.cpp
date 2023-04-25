
// Terms02: 尽量以const, enum, inline替换#define
// 对于单纯常量 最好以const对象或enum替换#define
// 对于形如函数的宏 最好改用inline函数替换#define
#include <iostream>

class GamePlayer {
private:
    // 如果编译器不允许"static整型class常量"完成"in class初值设定"可使用"the enum hack"
    // enum 和 #define 取地址不合法
    // const对象有可能会设定另外的存储空间 取决于编译器 
    // enum 和 #define 绝不会导致非必要的内存
    enum { NumTurns = 5 };  

    // class专属常量 static修饰保证常量至多有一份
    // static const int NumTurns = 5;  // 如果不取地址 只需此声明无需提供定义式
    // static const double NumTurns;
    int score[NumTurns];
public:
    static int GetStaticVal() {
        // const int* p = &NumTurns;
        // std::cout << "NumTurns: " << *p << std::endl;
        return NumTurns;
    }
};

// const int GamePlayer::NumTurns;   // 如果对NumTurns进行取地址操作 需提供该定义式

#define CALL_WITH_MAX(a, b) ((a) > (b) ? (a) : (b))

template<typename T>
inline int callWithMax(const T& a, const T& b) {
    return a > b ? a : b;
}

int main() {
    // GamePlayer gp;
    // std::cout << gp.GetStaticVal() << std::endl;

    int a = 5, b = 0;
    int max1 = CALL_WITH_MAX(a, b);
    int max2 = callWithMax(a, b);
    std::cout << "max1: " << max1 << std::endl;
    std::cout << "max2: " << max2 << std::endl;

    return 0;
}