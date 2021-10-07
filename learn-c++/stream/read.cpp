#include <iostream>
#include <fstream>

const char *fname = "foo.txt";

int main(int argc, char *argv[])
{
    std::ifstream f;
    std::string s;

    f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        f.open(fname);
        f >> s;
        f.close();
    } catch (const std::ifstream::failure& e) {
        std::cout << fname << ": " << e.what() << std::endl;
        return 1;
    }

    std::cout << "string s = '" << s << "'" << std::endl;

    return 0;
}
