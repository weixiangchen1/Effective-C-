// Trems15: 在资源管理类中提供对原始资源的访问
// APIs往往要求访问原始资源 所以RAII class必须提供取得原始资源的方法
// 对原始资源的访问可以经由显式转换或隐式转换 一般显式转换较安全 隐式转换较方便
#include <iostream>
#include <memory>

class Investment {
public:
    bool isTaxFree() const;
};

// 创建Investment对象
Investment* createInvestment();

// 返回投资天数
int daysHeld(const Investment* pi);

class FontHandle {};                    // 字体资源
FontHandle getFont();                   // 获取字体资源
void releaseFont(FontHandle fh);        // 释放字体资源
void changeFontSize(FontHandle f, int newSize);  // 更改字体大小


// 如果有大量的关于FontHandle的api 则需要大量重复将Font转换为FontHandle
// 可以提供一个显式转换函数get
class Font {       // RAII class
public:
    explicit Font(FontHandle fh)
        :f(fh)
    {}

    // 显式转换函数
    FontHandle get() const { return f; }

    // 隐式转换函数
    operator FontHandle() const { return f; }

    ~Font() { releaseFont(f); }
private:
    FontHandle f;
};


int main() 
{
    std::shared_ptr<Investment> pInv(createInvestment());
    // daysHeld函数参数为原生的Investment* 指针
    // 所以不能直接传递shared_ptr 
    // auto_ptr和shared_ptr提供一个get成员函数返回智能指针的原始指针
    int days = daysHeld(pInv.get());

    // 所有智能指针都重载了operator->和operator* 允许隐式转换至底部原始指针
    bool taxable1 = !(pInv->isTaxFree());
    bool taxable2 = !((*pInv).isTaxFree());

    Font f(getFont());

    int newFontSize;
    // 显式转换，这样设计增加了泄露字体的可能性
    changeFontSize(f.get(), newFontSize);
    // 隐式转换，但这会增加错误的发生机会
    changeFontSize(f, newFontSize);

    return 0;
}