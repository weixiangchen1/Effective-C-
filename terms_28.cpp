// Terms28: 避免返回handles指向对象内部成分
#include <iostream>
#include <memory>

// 表示点的类
class Point {
public:
    Point(int x, int y) {}
    void setX(int newVal) {}
    void setY(int newVal) {}
};

// 用点来表示一个矩形
class RectData {
    Point ulhc;    // upper left-hand comer 左上角
    Point lrhc;    // lower right-hand comer 右上角
};

class Rectangle {
public:
    Rectangle(Point p1, Point p2) {}

    // 加上const可以让用户读取Point而修改是被禁止的
    const Point& upperLeft() const { return pData->ulhc; }
    const Point& lowerLeft() const { return pData->lrhc; }

private:
    std::shared_ptr<RectData> pData;    // 智能指针管理资源
};

class GUIObject {};
const Rectangle boundingBox(const GUIObject& obj);

int main()
{
    Point coord1(0, 0);
    Point coord2(100, 100);
    const Rectangle rec(coord1, coord2);
    // rec.upperLeft().setX(50);      // upperLeft的调用者能够使用被返回的引用改变成员 但实际上rec是const的

    // 返回handle可能导致dangling handles handle所指的对象不复存在
    GUIObject* pgo;
    const Point* pUpperLeft = &(boundingBox(*pgo).upperLeft());
    // 上述代码调用会产生一个Rectangle的临时对象 upperLeft作用在临时对象上
    // pUpperLeft指向临时对象内的Point对象
    // 当前语句结束 临时对象就会被销毁 临时对象内的Point就会被析构
    // 最终导致pUpperLeft指向一个不再存在的对象

    return 0;
}