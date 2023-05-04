// Terms08: 别让异常逃离析构函数
// 析构函数绝对不要抛出异常 如果抛出就应该捕捉任何异常 吐下异常或者结束程序
// 如果客户需要某个操作函数运行期间抛出异常 class应该提供一个普通函数执行该操作
// 而不是用析构函数执行该操作
#include <iostream>
#include <vector>

class Widget {
public:
    ~Widget() {}  // 假设析构函数会抛出一个异常
};

void doSomething()
{
    std::vector<Widget> v;
}                 // v在此处被自动销毁
// 假设v内含有十个Wigets 在析构第一个元素时抛出异常
// 其他九个元素还是应该被销毁 但是如果第二个元素析构又抛出异常
// 现有两个同时作用的异常 这会导致不明确行为

// DBConnection类负责数据库连接
class DBConnection {
public:
    static DBConnection create();  

    void close();          // 关闭数据库连接 失败则抛异常
};

// 为了确保用户不忘记调用close() 创建一个用来管理DBConnection的类
class DBConn {
public:
    DBConn(DBConnection& _db) 
        :db(_db)
    {}
    
    // 如果close()调用失败 DBConn析构函数会传播该异常
    // 也就是允许离开析构函数 这个问题可以用捕捉异常+abort()解决
    // ~DBConn()    // 确保数据库总是被关闭
    // {
    //     db.close();
    // }

    ~DBConn()
    {
        try {
            db.close();   // close抛出异常就结束程序
        }
        catch(...) {
            // 制作运转记录 几下close调用失败
            std::abort();
        }
    }
    // 如果遭遇析构时发出的错误 强迫结束程序是个合理选项
    // 此方法可以阻止异常从析构函数传播出去
    // 但是此方法无法对异常做出反应
private:
    DBConnection db;
};

    // 重新设计DBConn接口 使用户有机会对异常做出反应
    class DBConn {
    public:
        void close()    // 供客户使用的新函数
        {
            db.close();
            closed = true;
        }
        ~DBConn()
        {
            if (!closed) {
                try {
                    db.close();
                }
                catch(...) {
                    // 制作运转记录 记下对close调用失败
                }
            }
        }
    private:
        DBConnection db;
        bool closed;
    };
    // DBconn析构函数内含双保险调用 把调用close交于客户
    // 客户若忽略 DBConn可以调用close

int main()
{
    return 0;
}