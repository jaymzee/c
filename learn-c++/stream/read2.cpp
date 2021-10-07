#include <iostream>
#include <fstream>

const char *fname = "foo.txt";

int main(int argc, char *argv[])
{
    std::ifstream f;
    std::string s;

    f.open(fname);
    if (f.fail()) {
        std::cout << fname << ": open failed" << std::endl;
        exit(1);
    }
    f >> s;
    f.close();

    std::cout << "string s = '" << s << "'" << std::endl;

    return 0;
}
