// Terms23: 宁以non-member、non-friend替换member函数
// non-member、non-friend函数替换member函数可以增加封装性、包裹弹性和机能扩充性
#include <iostream>

// 表示网页浏览器的class
class WebBrowser {
public:
    void clearCache();      // 清除下载元素高速缓存区
    void clearHistory();    // 清除URL历史记录
    void removeCookie();    // 清除系统的所有cookie

    // 1. webBrowser提供一个类内函数
    void clearEveryThing() {
        clearCache();
        clearHistory();
        removeCookie();
    }
};

// 如果要执行所有动作 有两种方案
// 1. webBrowser提供一个类内函数
// 2. 提供一个non-member函数调用member函数
void clearBrowser(WebBrowser& wb)
{
    wb.clearCache();
    wb.clearHistory();
    wb.removeCookie();
}

// member函数会影响private的成员封装性
// non-member函数会增加类的封装性
// 在C++中比较自然的做法是吧non-member函数放在和类所在的同一个命名空间中
// namespace可以跨越多个源码文件使用
namespace WebBrowserStuff {
    class WebBrowser {};
    void clearBrowser(WebBrowser& wb);
}

// non-member函数可以扩展核心机能

// "webbrowser.h"
namespace WebBrowserStuff {
    class WebBrowser {};
    // ...                  核心机能 用户需要使用的non-member函数
}

// "webbrowserbookmarks.h"
namespace WebBrowserStuff {
    // ...                  与书签相关的non-member函数
}

// "webbrowsercookies.h"
namespace WebBrowserStuff {
    // ...                  与cookie相关的non-member函数
}
