// Terms25: 考虑写出一个不抛异常的swap函数
#include <iostream>
#include <vector>

// std::swap的典型实现
// template<typename T>
// void swap(T& a, T& b)
// {
//     T temp(a);
//     a = b;
//     b = temp;
// }

// 通常情况下不允许对std命名空间的内容做出改变
// 但允许对模板函数提供特化版本
// namespace std {
//     // 针对Widget的swap版本
//     template<>
//     void swap<Wiget>(Widget& a, Widget& b) {
//         a.swap(b);  // 调用类内的swap 交换pImpl指针
//     }
// }

// 'pimpl'手法: pointer to implementation 以指针指向一个对象 内含真正的数据
// class WidgetImpl {
// private:
//     int a, b, c;
//     std::vector<double> v;
// };
// class Widget {
// public:
//     void swap(Widget& other)
//     {
//         using std::swap;
//         std::swap(pImpl, other.pImpl);
//     }

//     Widget(const Widget& rhs);
//     Widget& operator=(const Widget& rhs)
//     {
//         // ...
//         *pImpl = *(rhs.pImpl);
//         // ...
//     }
// private:
//     WidgetImpl* pImpl;    // 如要置换两个对象值 只需交换两个pImpl指针
// };


// 假设Widget是class templates
template<typename T>
class WidgetImpl {
private:
    int a, b, c;
    std::vector<int> vec;
};

template<typename T>
class Widget {
public:
    void swap(Widget<T>& other)
    {
        using std::swap;
        std::swap(pImpl, other.pImpl);
    }
private:
    WidgetImpl<T>* pImpl;
};

// namespace std {
//     // error 这属于模板的偏特化 C++只允许对类进行偏特化 不允许对函数进行偏特化
//     // template<typename T>
//     // void swap<Widget<T> >(Widget<T>& a, Widget<T>& b) {
//     //     a.swap(b);
//     // }

//     // 函数重载
//     // error std命名空间只允许添加模板的全特化版本 不允许函数重载
//     template<typename T>
//     void swap(Widget<T>& a, Widget<T>& b) {
//         a.swap(b);
//     }
// }

namespace WidgetStuff {
    template<typename T>
    class Widget {
    public:
        void swap(Widget<T>& other)
        {
            using std::swap;
            std::swap(pImpl, other.pImpl);
        }
    private:
        WidgetImpl<T>* pImpl;
    };

    template<typename T>
    void swap(Widget<T>& a, Widget<T>& b) {
        a.swap(b);
    }
}

template<typename T>
void dosomething(T& obj1, T& obj2)
{
    using std::swap;
    // ...
    swap(obj1, obj2);
    // 根据C++的名称查找法则 会找到T所在之命名空间内的任何T的专属swap
    // 如果T为Widget 就会到命名空间WidgetStuff中查找swap 如果没有专属swap 就会使用std::swap
}