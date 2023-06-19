//This example take from StackOverflow user Andrushenko Alexander
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

#include<iostream>
#include<string>

class DoNotCopy
{
protected:
    DoNotCopy(void) = default;
    DoNotCopy(const DoNotCopy&) = delete;
    DoNotCopy& operator=(const DoNotCopy&) = delete;
};

class DoNotMove
{
protected:
    DoNotMove(void) = default;
    DoNotMove(DoNotMove&&) = delete;
    DoNotMove& operator=(DoNotMove&&) = delete;
};

class DoNotCopyMove : public DoNotCopy,
    public DoNotMove
{
protected:
    DoNotCopyMove(void) = default;
};

template<class T>
class Singleton : public DoNotCopyMove
{
public:
    static T& Instance(void)
    {
        static T instance;
        return instance;
    }

protected:
    Singleton(void) = default;
};

class Logger final : public Singleton<Logger>
{
public:
    void log(const std::string& str) { std::cout << str << std::endl; }
};



int main()
{
    Logger::Instance().log("xx");
}