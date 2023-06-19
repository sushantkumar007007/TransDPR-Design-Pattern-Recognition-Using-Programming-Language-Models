//This example take from StackOverflow user Tunvir Rahman Tusher
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

#include <Windows.h>
#include <iostream>

using namespace std;


class SingletonClass {

public:
    static SingletonClass* getInstance() {

        return (!m_instanceSingleton) ?
            m_instanceSingleton = new SingletonClass :
            m_instanceSingleton;
    }

private:
    // private constructor and destructor
    SingletonClass() { cout << "SingletonClass instance created!\n"; }
    ~SingletonClass() {}

    // private copy constructor and assignment operator
    SingletonClass(const SingletonClass&);
    SingletonClass& operator=(const SingletonClass&);

    static SingletonClass* m_instanceSingleton;
};

SingletonClass* SingletonClass::m_instanceSingleton = nullptr;



int main(int argc, const char* argv[]) {

    SingletonClass* singleton;
    singleton = singleton->getInstance();
    cout << singleton << endl;

    // Another object gets the reference of the first object!
    SingletonClass* anotherSingleton;
    anotherSingleton = anotherSingleton->getInstance();
    cout << anotherSingleton << endl;

    Sleep(5000);

    return 0;
}