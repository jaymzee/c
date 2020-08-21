#include <iostream>
#include <vector>
#include <thread>

void task(std::string msg)
{
    std::cout << "task says " << msg;
}

int main(int argc, char *argv[])
{
    using std::vector;
    using std::thread;
    using std::cout;
    using std::endl;

    vector<thread> vec(2);
    vec[0] = thread(task, "Hello\n");
    vec[1] = thread(task, "Välkommen\n");

    cout << "greetings..." << endl;

    for (auto &t : vec) {
        t.join();
    }

    cout << "done" << endl;
}
