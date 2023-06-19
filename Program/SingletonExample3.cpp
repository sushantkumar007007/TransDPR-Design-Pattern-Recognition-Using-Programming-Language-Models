//This example take from StackOverflow user Milind Deore
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

#include <iostream>
#include <thread>


class Singleton
{
private:
    static Singleton* _instance;
    static std::mutex mutex_;

protected:
    Singleton(const std::string value) : value_(value)
    {
    }
    ~Singleton() {}
    std::string value_;

public:
    /**
     * Singletons should not be cloneable.
     */
    Singleton(Singleton& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const Singleton&) = delete;

    //static Singleton *GetInstance(const std::string& value);
    static Singleton* GetInstance(const std::string& value)
    {
        if (_instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (_instance == nullptr)
            {
                _instance = new Singleton(value);
            }
        }
        return _instance;
    }

    std::string value() const {
        return value_;
    }
};

/**
 * Static methods should be defined outside the class.
 */
Singleton* Singleton::_instance = nullptr;
std::mutex Singleton::mutex_;


void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

int main()
{
    std::cout << "If you see the same value, then singleton was reused (yay!\n" <<
        "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
        "RESULT:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
    std::cout << "Complete!" << std::endl;

    return 0;
}