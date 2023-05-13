// Terms14: 在资源管理类中小心copying行为
#include <iostream>
#include <memory>
using namespace std;

class Mutex {
    // ...
};

void lock(Mutex* pm);   // 锁定pm所指的互斥器
void unlock(Mutex* pm); // 将互斥器解除锁定

class Lock {
public:
    explicit Lock(Mutex* pm)
        :mutexPtr(pm)
    {
        lock(mutexPtr);    // 获取资源
    }

    ~Lock()
    {
        unlock(mutexPtr);  // 释放资源
    }
private:
    Mutex* mutexPtr;
};


// Lock ml1(&m)
// Lock ml2(ml1)
// 如何解决copying问题
// 1. 禁止复制
class Uncopyable {
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class Lock: private Uncopyable {
public:
    // ...
};

// 2. 使用引用计数法
class Lock {
public:
    explicit Lock(Mutex* pm)
        :mutexPtr(pm, unlock)
    {
        lock(mutexPtr.get());
    }
private:
    shared_ptr<Mutex> mutexPtr;
};


int main()
{
    // 用户使用
    Mutex m;
    // ...
    // 建立区块来定义临界区
    {
        Lock m1(&m);   // 锁定互斥器
        // ...            执行操作
    }
    // m1生命周期结束 自动解除互斥器锁定

}

