#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<char> buffer((char *)malloc(1000));
    if (buffer) {
        char *p = buffer.get();
        strcpy(p, "Hello World");
        std::cout << p << std::endl;
    }
}
