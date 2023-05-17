// Terms20: 宁以pass-by-reference-to-const替换pass-by-value
// 尽量以pass-by-reference-to-const替换pass-by-value
// 前者通常比较高效 并可避免切割问题
// 但以上规则不使用与内置类型以及STL迭代器好而函数对象
#include <iostream>
#include <string>

class Person {
public:
    Person();
    virtual ~Person();
private:
    std::string name;
    std::string address;
};

class Student: public Person {
public:
    Student();
    ~Student();
private:
    std::string schoolName;
    std::string schoolAddress;
};


// int main() 
// {
//     // bool validateStudent(Student s);            // pass-by-value
//     // Student plato;
//     // bool platoIsOK = validateStudent(plato);
//     // 上诉函数被调用会发生什么事？
//     // Student的拷贝构造会被调用 当函数退出 Student析构函数被调用
//     // Student对象内有2个string对象 调用两次string构造函数和两次string析构函数
//     // Student继承与Person 构造Student必须构造Person对象 必须调用一次Person构造函数和析构函数
//     // Person对象内有2个string对象 调用两次string构造函数和析构函数
//     // by-value的方式传递一个Student对象 成本是六次构造函数和六次析构函数

//     bool validateStudent(const Student& s);     // pass by reference-to-const
//     Student plato;
//     bool platoIsOK = validateStudent(plato); 
//     // 传const reference的方式效率高得多 没有任何构造函数和析构函数被调用

    
//     return 0;
// }

class Window {
public:
    std::string name() const;         // 返回窗口名称
    virtual void display() const;     // 显示窗口及内容
};

class WindowWithScrollBars: public Window {
public:
    virtual void display() const;
};

// 打印窗口名称
void printNameAndDisplay(Window w)
{
    std::cout << w.name();
    w.display();
}

int main() 
{
    WindowWithScrollBars wwsb;
    printNameAndDisplay(wwsb);
    // 上述代码是不正确的 wwsb对象会被切割 会被构造成一个Window对象
    // 有关于WindowWithScrollBars对象的特化信息都会被切除
    // 所以调用printNameAndDisplay时 只会调用window::display()

    // 解决切割问题的方法 -- 使用by reference-to-const
    // void printNameAndDisplay(const Window& w)
    // {
    //     std::cout << w.name();
    //     w.display();
    // }

    return 0;
}