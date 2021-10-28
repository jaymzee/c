/*
 * dispatch's return type the same as it's argument
 * type of function performed depneds on the type of argument supplied
 */

#include <iostream>
#include <type_traits>

template <typename T>
T dispatch(T x)
{
    if constexpr (std::is_same<T, int>::value) {
        return x * x;
    } else if constexpr (std::is_same<T, const char *>::value) {
        return x;
    } else if constexpr (std::is_same<T, std::string>::value) {
        return "hi, " + x;  // std::string supports concatenation
    } else {
        return 2.0 * x;
    }
}

int main()
{
    std::cout << dispatch(3) << std::endl;
    std::cout << dispatch(3.1) << std::endl;
    std::cout << dispatch("hey") << std::endl;
    std::cout << dispatch(std::string("joe")) << std::endl;
    return 0;
}
