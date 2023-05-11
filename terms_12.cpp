// Terms12: 复制对象时勿忘其每一个成分
#include <iostream>

class Date {};
void logCall(const std::string& funcName);
class Customer {
public:
    Customer(const Customer& rhs);
    Customer& operator=(const Customer& rhs);

private:
    std::string name;
    Date lastTransaction;
};

Customer::Customer(const Customer& rhs)
    :name(rhs.name)
{
    logCall("Customer copy constructor");
}

Customer& Customer::operator=(const Customer& rhs)
{
    logCall("Customer copy assignment operator");
    name = rhs.name;
    return *this;
}

class PriorityCustomer: public Customer {
public:
    PriorityCustomer(const PriorityCustomer& rhs);
    PriorityCustomer& operator=(const PriorityCustomer& rhs);
private:
    int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
    :Customer(rhs),    // 调用base class的copy构造函数
    priority(rhs.priority)
{
    logCall("PriorityCustomer copy constructor");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
    logCall("PriorityCustomer copy assignment operator");
    Customer::operator=(rhs);   // 调用base class的operator=赋值动作
    priority = rhs.priority;
    return *this;
}