#include <iostream>
#include <vector>

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "[";
    for (auto elem : vec) {
        os << " " << elem;
    }
    os << " ]\n";
    return os;
}

int main(int argc, char *argv[])
{
    std::vector<double> x{1.1, 2.2, 3.3};
    std::vector<double> y(5, 4.4);

    std::cout << "x = " << x;
    std::cout << "y = " << y;

    return 0;
}
