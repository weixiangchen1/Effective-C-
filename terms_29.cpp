// Terms29: 为异常安全而努力是值得的
#include <iostream>
#include <memory>

class Mutex {};   // 互斥锁
void lock(Mutex* mtx) {}
void unlock(Mutex* mtx) {}


class Image {   // 表示图片的类
public:
    Image(std::istream& imgSrc) {}
};   

// 用来表示夹带背景图案的GUI菜单类
// class PrettyMenu {
// public:
//     void changeBackground(std::istream& imgSrc); // 改变背景图像
// private:
//     Mutex mutex;       // 互斥器
//     Image* bgImage;    // 目前的背景图像
//     int imageChanges;  // 背景图像被改变的次数
// };

// void PrettyMenu::changeBackground(std::istream& imgSrc)
// {
//     lock(&mutex);                    // 取得互斥器
//     delete bgImage;                  // 删除旧的背景图
//     ++imageChanges;                  // 修改图像变更次数
//     bgImage = new Image(imgSrc);     // 安装新的背景图
//     unlock(&mutex);                  // 释放互斥器
// }
// 异常安全的函数：1. 不泄露任何资源 2. 不允许数据败坏
// 上诉代码不是异常安全的 一旦"new Image"抛异常 unlock就永远不会执行 导致资源泄露
// 一旦"new Image"抛异常 bgImage指向的就是已经被删除的对象 imageChanges也已经被累加

// Lock class 确保互斥器被及时释放
class Lock {
public:
    Lock(Mutex* mtx): mutex(mtx) { lock(mutex); }
    ~Lock() { unlock(mutex); }
private:
    Mutex* mutex;
};

// 解决了资源泄露的问题
// void PrettyMenu::changeBackground(std::istream& imgSrc)
// {
//     Lock m1(&mutex);
//     delete bgImage;
//     ++imageChanges;
//     bgImage = new Image(imgSrc);
// }

// 异常安全函数需要提供一下三个保证之一:
// 基本承诺: 假如异常被抛出 没有任何对象或数据结构会因此被破坏
// 强烈保证: 假如异常被抛出 程序状态不改变 如果函数调用成功 就是完全成功 如果函数调用失败 程序要恢复到调用函数前的状态
// 不抛掷保证: 承诺绝不抛出异常

// changeBackground可以提供强烈保证
// 1. 使用智能指针管理Image对象
// 2. 重新排序函数内的语句次序 更换图像后才累加imageChanges
// class PrettyMenu {
// public:
//     void changeBackground(std::istream& imgSrc); // 改变背景图像
// private:
//     Mutex mutex;       // 互斥器
//     std::shared_ptr<Image> bgImage;    // 目前的背景图像
//     int imageChanges;  // 背景图像被改变的次数
// };

// void PrettyMenu::changeBackground(std::istream& imgSrc)
// {
//     Lock m1(&mutex);
//     bgImage.reset(new Image(imgSrc));
//     // 无需再手动delete旧指针 这个动作在智能指针内部处理了
//     ++imageChanges;
// }

// 上述代码的改变已经几乎让函数提供强烈的异常安全
// 但是Image构造函数抛出异常 有可能输入流的读取记号已被移走
// 可以使用pimpl idiom + copy and swap 
struct PMImpl {
    std::shared_ptr<Image> bgImage;
    int imageChanges;
};

class PrettyMenu {
public:
    void changeBackground(std::istream& imgSrc);
private:
    Mutex mutex;
    std::shared_ptr<PMImpl> pImpl;
};

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    using std::swap;
    Lock m1(&mutex);
    std::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));
    pNew->bgImage.reset(new Image(imgSrc));
    ++pNew->imageChanges;

    swap(pImpl, pNew);
}