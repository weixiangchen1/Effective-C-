// Terms18: 让接口容易被正确使用，不易被误用
#include <iostream>

class Date {
public:
    Date(int month, int day, int year) {}
};

// 用户有可能输入错误的参数次序
// Date d1(30, 3, 1995);
// Date d2(2, 30, 1995);

// 导入简单的外覆类型区别天数 月份和年份
struct Day {
    explicit Day(int d)
        :val(d)
    {}

    int val;
};

// struct Month {
//     explicit Month(int m)
//         :val(m)
//     {}

//     int val; 
// };

class Month {
public:
    static Month Jan() { return Month(1); }
    static Month Feb() { return Month(2); }
    // ...
    static Month Dec() { return Month(12); }
private:
    explicit Month(int m);
};

struct Year {
    explicit Year(int y)
        :val(y)
    {}

    int val;
};

class Date {
public:
    Date(const Month& m, const Day& d, const Year& y);
};
// Date d1(30, 3, 1995);                    // error 
// Date d2(Day(30), Month(3), Year(1995));  // error
// Date d3(Month(3), Day(30), Year(1995));
Date d(Month::Feb(), Day(30), Year(1995));

