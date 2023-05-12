// Terms13: 以对象管理资源
// 为了防止资源泄露 使用RAII对象 在构造函数获取资源 构造函数释放资源
// 两个常用的RAII分别是share_ptr和auto_ptr auto_ptr复制动作会是它指向null
#include <iostream>
#include <memory>

class Investment{
    // ...
};

// 工厂函数供应Investment对象
Investment* createInvestment()
{
    return new Investment();
}

void f()
{
    Investment* pInv = createInvestment();
    // ...   如果...中存在return语句 抛异常等情况 delete将不被执行 这就会造成资源泄露
    delete pInv;
}

// 使用智能指针管理资源
void f()
{
    std::auto_ptr<Investment> pInv1(createInvestment());
    // auto_ptr会自动调用析构函数删除pInv1
    // 受auto_ptr管理的资源必须绝对没有一个以上的auto_ptr同时指向它

    std::auto_ptr<Investment> pInv2(pInv1);  // pInv2指向对象 pInv1指向null
    pInv1 = pInv2;                           // pInv1指向对象 pInv2指向null
}

// 使用引用计数型智能指针share_ptr
void f()
{
    std::shared_ptr<Investment> pInv1(createInvestment());
    std::shared_ptr<Investment> pInv2(pInv1);
    // pInv1和pInv2指向同一对象
}