// Terms17: 以独立语句将newd对象置入智能指针
#include <iostream>
#include <memory>

class Widget {};

// 获取程序优先级的函数
int priority();

// Widget的优先级的相关处理
void processWidget(std::shared_ptr<Widget> pw, int priority);

int main() 
{
    // 调用processWidget函数
    processWidget(std::shared_ptr<Widget>(new Widget), priority());
    // 以上代码会做三件事
    // 1. 调用priority 2. 执行new Widget 3. 调用shared_ptr构造函数
    // 但是在C++中这三件事的执行次序是不一定的
    // 如果是按照一下次序执行：
    // 1. 执行new Widget
    // 2. 调用priority
    // 3. 调用shared_ptr构造函数
    // 如果调用priority导致异常 new Widget返回的指针就会遗失
    // 这会导致内存泄露 解决方法：
    std::shared_ptr<Widget> pw(new Widget); // 用单独语句内以智能指针存储newed所得对象
    processWidget(pw, priority());

    return 0;
}