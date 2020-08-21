#include <iostream>
#include <thread>

// compile and link with pthread library
// gcc -pthread thread.cpp

void foo()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main()
{
    std::thread first(foo);
    std::thread second(bar, 0);

    std::cout << "main, foo, and bar now execute concurrently...\n";

    first.join();  // pauses until first finishes
    std::cout << "waiting for second to finish up...\n";
    second.join(); // pauses until second finishes
    return 0;
}
