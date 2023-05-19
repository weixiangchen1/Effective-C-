// Terms22: 将成员变量声明为private
#include <iostream>

// 可细微划分访问控制
class AccessLevels {
public:
    int getReadOnly() const { return readOnly; }
    void setReadWrite(int value) { readWrite = value; }
    int getReadWrite() const { return readWrite; }
    void setWriteOnly(int value) { writeOnly = value; }
private:
    int noAccess;    // 无任何访问动作
    int readOnly;    // 只读访问
    int readWrite;   // 读写访问
    int writeOnly;   // 惟写访问
};

class SpeedDateCollection {
public:
    void addValue(int speed);      // 添加新数据
    double averageSoFar() const;   // 返回平均速度
};
// averageSoFar函数有两种做法: 
// 1. 随时保持平均值 为平均值、累积总量、数据点数分配空间 比较高效
// 2. 被询问时才计算平均值 
// 两种方式各有合适的场景 但是重点是通过成员变量访问平均值可以替换不同的实现方式

// public和protected都不具有封装性
// 如果不封装成员变量 用户可以随意改变 改变就是从class移除它 
// 如果成员变量是public 所有使用它的用户码会被破坏
// 如果成员变量是protected 所有derived classes都会被破坏