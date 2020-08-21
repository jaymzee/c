#include <iostream>
#include <thread>

void task(std::string msg)
{
    std::cout << "task says " << msg;
}

int main(int argc, char *argv[])
{
    std::thread t1(task, "Hello\n");
    std::thread t2(task, "Välkommen\n");

    t1.join();
    t2.join();
}
