// Terms04: 确定对象被使用前已先被初始化
// 为内置型对象进行手工初始化 C++不保证初始化它们
// 构造函数最好使用成员初值列 而不是在构造函数本体使用赋值操作 
// 初值列的成员变量排序顺序应该和它们在class声明的次序一致
// 为了避免"跨编译单元之初始化"问题 以local static对象替换non-local static对象
// reference-returning 函数是一种解决方案
#include <iostream>
#include <string>
#include <list>

class PhoneNumber {};
class ABEntry {
public:
    // ABEntry(const std::string& name, const std::string& address, 
    //         const std::list<PhoneNumber>& phones) {
    //     theName = name;         // 这里并不是初始化 而是赋值 
    //     theAddress = address;
    //     thePhones = phones;
    //     numTimesConsulted = 0;
    // }

    // 使用成员初始化列表替代赋值动作
    // 成员变量是const或者references 一定需要初值 必须在成员初值列中初始化
    // 基类比派生类更早被初始化 
    // 类的初始化顺序是按照声明的次序 而非初始化列表的顺序
    ABEntry(const std::string& name, const std::string& address, 
            const std::list<PhoneNumber>& phones)
        :theName(name),
        theAddress(address),
        thePhones(phones),
        numTimesConsulted(0)
    {} 
    
private:
    // 成员变量的初始化动作发生在进入构造函数本体之前
    std::string theName;
    std::string theAddress;
    std::list<PhoneNumber> thePhones;
    int numTimesConsulted;
};

// 假设FileSystem和Directory来自不同的编译单元(不同的源文件)
// class FileSystem {
// public:
//     size_t numDisks() const;
//     // ...
// };
// extern FileSystem tfs; 

// class Directory {
// public:
//     Directory();
// };

// Directory::Directory()
// {
//     size_t disks = tfs.numDisks();
// }

// Directory tempDir();

// 由于C++对"定义于不同编译单元内的non-local static对象"的初始化次序没有明确确定
// tfs和tempDir的初始化次序无法被确定 如果tfs初始化在tempDir之后 会得到惨重的灾情
// 解决方法: 将每个non-local static对象搬到自己的专属函数内 函数返回静态对象
// 函数内的local static对象会在函数被调用期间首次遇到对象定义式的时候被初始化
// 不调用non-local static对象的"仿真函数" 绝不会引发构造和析构成本

class FileSystem {
public:
    size_t numDisks() const;
};

// 用此函数替换tfs对象
FileSystem& tfs()
{
    static FileSystem fs;   // 定义并初始化local static对象
    return fs;              // 返回reference指向该对象
}

class Directory {
public:
    Directory();
};

Directory::Directory() {
    size_t disks = tfs().numDisks();
}

Directory& tempDir()
{
    static Directory td;
    return td;
}

int main() 
{
    return 0;
}