// This example is a combination of the wikipedia Coin example and the Wikipedia C++ singleton example, with modifications
// https://en.wikipedia.org/wiki/Singleton_pattern

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class SingletonCoin {

public:
    static SingletonCoin* GetInstance() {
        // Allocate with `new` in case Singleton is not trivially destructible.
        static SingletonCoin* singleton = new SingletonCoin();
        return singleton;
    }

    void addCoin() {
        coin++;
    }

    void removeCoin() {
        coin--;
    }

private:
    SingletonCoin() = default;
    int coin = 0;

    // Delete copy/move so extra instances can't be created/moved.
    SingletonCoin(const SingletonCoin&) = delete;
    SingletonCoin& operator=(const SingletonCoin&) = delete;
    SingletonCoin(SingletonCoin&&) = delete;
    SingletonCoin& operator=(SingletonCoin&&) = delete;

};

int main()
{

    // Create and open a text file
    ofstream MyFile("monies.txt");

    // Write to the file
    MyFile << "73";

    // Close the file
    MyFile.close();

    ifstream ReadFile;

    SingletonCoin* coin;
    coin = coin->GetInstance();

    int money = 0;

    ReadFile.open("monies.txt", ios::in);

    if (ReadFile.is_open()) {
        ReadFile >> money;

        for (int i = 0; i < money; i++) {

            coin->addCoin();
        }

        std::cout << "I have " << money << " monies!";

    }

};