//  And example from github using singletons for multi-threaded cases https://github.com/dcblack/singleton by dcblack
// main header and cpp files combined to one file


// Multi-thread example that uses a singleton class
#include <cstddef>
#include <atomic>
#include <mutex>
#include <cstdint>
#include <cassert>
#include <iostream>

#ifndef SINGLETON_H
#define SINGLETON_H


extern std::mutex cout_mutex;

struct Singleton {

    static Singleton& instance();

    // Other public methods
    void whoami();
    void increment();
    // Accessors
    size_t get_count() const { return m_count; }
    static size_t get_refs() { return s_refs; }

    Singleton(const Singleton& rhs) = delete;  // copy constructor
    const Singleton& operator=(const Singleton& rhs) = delete;  // copy assignment
    Singleton(const Singleton&& rhs) = delete;  // move constructor
    const Singleton& operator=(const Singleton&& rhs) = delete;  // move assignment

private:
    Singleton(); // Default constructor
    ~Singleton(); // Destructor
    // attributes
    std::atomic<size_t> m_count{ 0U };
    static std::atomic<size_t> s_refs;
};
#endif

////////////////////////////////////////////////////////////////////////////////
//
//   Copyright 2017 Doulos Inc.
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////

const size_t PER_JOB_RANDOM_DELAY_COUNT = 1'000;
const size_t PER_JOB_INCREMENT_COUNT = 1'000;
const size_t NUMBER_OF_THREADS = 500;

////////////////////////////////////////////////////////////////////////////////
// 
// 
//#include "singleton.h"

//This is an example of using a "Meyers" singleton class usable with threads.

//#include "singleton.h"

std::mutex cout_mutex;

std::atomic<size_t> Singleton::s_refs{ 0U };

// This is the key method that returns the singleton reference
Singleton& Singleton::instance()
{
    ++s_refs;
    static Singleton instance{};
    return instance;
}

Singleton::Singleton() // Default constructor
{
    std::cout << "Constructing Singleton" << std::endl;
}

Singleton::~Singleton() // Destructor
{
    std::cout << "Destroying Singleton" << std::endl;
}

void Singleton::whoami()
{
    std::lock_guard<std::mutex> lock(cout_mutex);
    printf("Singleton at @%p\n", static_cast<void*>(this));
}

void Singleton::increment() {
    ++m_count;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Copyright 2017 Doulos Inc.
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////
#include <deque>
std::mutex finish_mutex;
std::deque<size_t> finished;

#include <mutex>
std::mutex              go_mutex;
std::condition_variable go_condition;
volatile bool           go_ready = false;

#include <random>

// Function to launch as multiple threads
void do_work(size_t id)
{
    // Wait for `go' signal
    std::unique_lock<std::mutex> lck(go_mutex);

    while (!go_ready) {
        go_condition.wait(lck);
    }

    // Random delay
    std::uniform_int_distribution<size_t> dist{ 1, 10 };
    std::random_device gen;
    volatile double x = 0.0;

    for (size_t i = PER_JOB_RANDOM_DELAY_COUNT * dist(gen); i > 0; --i) {
        ++x;
    }

    // Increment shared data
    Singleton& s{ Singleton::instance() };
    for (size_t i = PER_JOB_INCREMENT_COUNT; i > 0; --i) {
        s.increment();
    }

    // Record order of completion
    {
        std::lock_guard<std::mutex> lock(finish_mutex);
        finished.push_back(id);
    }
}

void go()
{
    std::unique_lock<std::mutex> lck(go_mutex);
    go_ready = true;
    go_condition.notify_all();
}

////////////////////////////////////////////////////////////////////////////////
//#include <deque>
#include <thread>
#include <iostream>
#include <iomanip>
int main()
{
    // Create threads
    std::deque<std::thread> threads;
    for (size_t i = NUMBER_OF_THREADS; i > 0; --i) {
        threads.emplace_back(std::thread(do_work, i));
    }
    std::cout << threads.size() << " threads ready to race" << std::endl;

    // Start threads
    go();

    // Wait for finish
    for (auto& t : threads) {
        t.join();
    }

    // Report results
    std::cout << "Finishing order:\n" << std::flush;
    size_t n = 0;
    for (auto v : finished) {
        std::cout << " " << std::setw(4) << v;
        if ((++n % 20) == 0) std::cout << std::endl;
    }
    Singleton::instance().whoami();
    std::cout << "Got reference to singleton " << Singleton::get_refs() << " times." << std::endl;
    std::cout << "Final count is " << Singleton::instance().get_count() << std::endl;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Copyright 2017 Doulos Inc.
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////