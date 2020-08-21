#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    const char *val = std::getenv("FOO");

    if (val) {
        std::cout << val << std::endl;
    } else {
        std::cout << "FOO not set" << std::endl;
    }
}
