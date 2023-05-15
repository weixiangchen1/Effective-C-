// Terms16: 成对使用new和delete时要采取相同形式
#include <iostream>
#include <string>

// 对象数组在创建出来时 大部分编译器会在内存中包括数组大小的记录
// 单一对象的内存没有这个记录

int main()
{
    std::string* stringPtr1 = new std::string;
    std::string* stringPtr2 = new std::string[100];

    // ...

    delete stringPtr1;      // 删除一个对象
    delete []stringPtr2;    // 删除对象数组

    typedef std::string AddressLines[4];
    std::string* pal = new AddressLines;
    delete pal;      // error
    delete []pal;
    // 尽量不要对数组形式做typedef动作
    // 可定义成vector<string> 

    return 0;
}