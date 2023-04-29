// Terms05: 了解C++默认编写并调用了哪些函数
#include <iostream>

// class Empty {};
// C++编译器在处理完上面空类后 会为你写下下述函数:
class Empty {
public:
    Empty() {}                              // 默认构造函数
    Empty(const Empty& rhs) {}              // 拷贝构造函数
    ~Empty() {}                             // 析构函数 -- non-virtual
    Empty& operator=(const Empty& rhs) {}   // 拷贝赋值
};

// template<typename T>
// class NamedObject {
// public:
//     NamedObject(const char* name, const T& value) {
//         std::cout << "NamedObject(const char* name, const T& value): " << name << ": " << value << std::endl;
//     }
//     NamedObject(const std::string name, const T& value) {
//         std::cout << "NamedObject(const string name, const T& value): " << name << ": " << value << std::endl;
//     }
// private:
//     std::string nameValue;
//     T objectValue;
// }; 

template<class T>
class NamedObject {
public:
    NamedObject(std::string& name, const T& value);

private:
    std::string& nameValue;
    const T& objectValue;
};


int main()
{
    // nameValue的类型是string string拥有拷贝构造函数
    // no2.nameValue的初始化方式是调用string的拷贝构造函数以no1.nameValue为实参
    // no2.objectValue的类型是int 初始化以no1.objectValue的每一个bit完成初始化
    // NamedObject<int> no1("Smallest Prime Number", 2);
    // NamedObject<int> no2(no1);

    std::string newDog("Persephone");
    std::string oldDog("Satch");
    NamedObject<int> p(newDog, 2);
    NamedObject<int> s(oldDog, 36);
    // p = s;    C++拒绝生成默认赋值构造函数 
    // C++在面对内含reference成员的class时 不会生成默认赋值构造 必须自己定义
    // C++在面对内含const成员的class时 不会生成默认赋值构造 更改const的不合法的

    return 0;
}   