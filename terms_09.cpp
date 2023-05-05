// Terms09: 绝不在构造和析构过程中调用virtual函数
// 在构造和析构期间不要调用virtual函数 这类调用不会下降至derived class
#include <iostream>

// 股市交易类 每一笔交易要进行审计日志
// class Transaction {    // base class
// public:
//     Transaction();
//     virtual void logTransaction() const = 0; // 因类型不同而改变的日志记录
// };

// Transaction::Transaction()
// {
//     logTransaction();
// }

// void Transaction::logTransaction() const
// {
//     std::cout << "Transaction::logTransaction()" << std::endl;  
// }

// class BuyTransaction: public Transaction {  // derived class
// public: 
//     virtual void logTransaction() const {
//         std::cout << "BuyTransaction::logTransaction()" << std::endl;
//     }
// };

// class SellTransaction: public Transaction {  // derived class
// public:
//     virtual void logTransaction() const {
//         std::cout << "SellTransaction::logTransaction()" << std::endl;
//     }
// };

class Transaction {
public:
    explicit Transaction(const std::string& logInfo);
    void logTransaction(const std::string& logInfo) const; // non-virtual
};

Transaction::Transaction(const std::string& logInfo)
{
    logTransaction(logInfo);
}

class BuyTransaction: public Transaction {
public:
    BuyTransaction(const std::string& info)
        :Transaction(createLogString(info))
    {}
private:
    static std::string createLogString(const std::string& info);
};

int main()
{
    BuyTransaction b(std::string());
    // 控制台输出: Transaction::logTransaction()
    // 在创建BuyTransition类时 先调用的是base class的析构函数
    // 此时调用的logTransition()是Transition内的版本 而不是BuyTransition的版本
    // 在析构和析构期间调用virtual函数 此类调用从不下降至derived class
    return 0;
}