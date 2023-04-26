// Terms03 尽可能使用const
// const出现在星号左边 表示被指物是常量
// const出现在星号右边 表示指针是常量
// const出现在星号量表 表示被指物和指针都是常量
// const可被施加于任何作用域内的对象、函数参数、函数返回类型、成员函数本体
// 编译器强制实施bitwise constness 但编写程序可以使用概念上的常量性
// 通过mutable实施logical constness
// const和non-const成员函数有等价的实现的时候 令non-const版本调用const版本可避免代码重复
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

int main()
{
    // 1. const变量
    char greeting[] = "Hello";
    char* p = greeting;
    // const char* p = greeting;       // 被指物为常量
    // char* const p = greeting;       // 指针为常量
    // const char* const p = greeting; // 被指物和指针为常量

    std::vector<int> vec {1, 2, 3};
    // STL迭代器实现 T* const一样的功能
    const std::vector<int>::iterator iter = vec.begin();
    *iter = 10;
    // iter++;       // err 迭代器本身是const
    // STL迭代器实现 const T*一样的功能
    std::vector<int>::const_iterator cIter = vec.begin();
    // *cIter = 10;  // err 迭代器所指物是const
    cIter++; 

    // 2. const成员函数
    class TextBlock {
    public:
        TextBlock(const char* s): text(s) {}
        // 成员函数因为常量性不同 可以被重载
        const char& operator[](size_t position) const {
            return text[position];
        }
        char& operator[](size_t position) {
            return text[position];
        }
    private:
        std::string text;
    };

    TextBlock tb("Hello");
    std::cout << tb[0];
    tb[0] = 'x';

    const TextBlock ctb("World");
    std::cout << ctb[0];
    // ctb[0] = 'x';   
    // err: 企图对const版本的operator[]返回的const char& 进行赋值动作

    // bitwise constness: 成员函数只有不更改任何成员变量
    // 不更改对象内的每一个bit 才可以说是const的
    class CTextBlock {
    public:
        CTextBlock(char* str)
            :pText(str)
        {}

        char& operator[](size_t position) const {
            return pText[position];
        }

    private:
        char* pText;
    };

    const CTextBlock cctb("Hello");
    char* pc = &cctb[0];
    *pc = 'J';  // err 违背了bitwise const原则 但是编译器识别不出来

    // logical constness: const成员函数可以修改某些bit
    // 但是编译器坚持bitwise constness 需要利用mutable关键字
    // mutable关键字可以释放掉non-static成员变量 bitwise const约束
    class CTextBlock1 {
    public:
        size_t Length() const {
            if (!lengthIsVaild) {
                textLength = std::strlen(pText); // const成员函数不能修改成员变量
                lengthIsVaild = true;            // mutable修饰可以免除bitwise const约束
            }
            return textLength;
        }
    private:
        char* pText;
        mutable size_t textLength;
        mutable bool lengthIsVaild;
    };

    class TextBlock1 {
    public:
        const char& operator[](size_t position) const
        {
            // ......          边界检验
            // ......          数据访问
            // ......          检验数据完整性
            return text[position];
        }

        char& operator[](size_t position)
        {
            // ......          边界检验
            // ......          数据访问
            // ......          检验数据完整性
            return text[position];
        }
    private:
        std::string text;
    };

    // 上述代码代码重复 优化以上代码 进行常量性转除
    class TextBlock1 {
    public:
        // 只能non-const成员函数调用const成员函数 反之违背了const成员函数的规则
        const char& operator[](size_t position) const
        {
            // ......          边界检验
            // ......          数据访问
            // ......          检验数据完整性
            return text[position];
        }

        char& operator[](size_t position)
        {
            // static_cast将*this从原始类型转型为const类型 加上const属性
            // const_cast从const operator[]的返回值中移除const
            return 
                const_cast<char&>(
                    static_cast<const TextBlock1&>(*this)
                        [position]
                );
        }
    private:
        std::string text;
    };


    return 0;
}