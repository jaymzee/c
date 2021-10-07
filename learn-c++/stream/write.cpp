#include <iostream>
#include <fstream>

const char *fname = "data.txt";

int main(int argc, char *argv[])
{
    std::ofstream f;
    std::string s;

    f.open(fname);
    if (f.fail()) {
        std::cout << fname << ": open failed" << std::endl;
        exit(1);
    }
    f << "hello" << std::endl;
    f.close();

    return 0;
}
