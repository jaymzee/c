/* lint with:
 *
 *   clang-tidy -checks='modernize*, readability*'  hey.cpp -- -std=c++14
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

auto main() -> int {
    int a;

    std::string hello{"hello"};
    std::string world{"world"};
    if ((hello + world).empty()) {
        std::cout << "empty!\n";
    }

    std::unique_ptr<std::string> ptr{new std::string{"abc"}};
    ptr = std::make_unique<std::string>("xyz");
    ptr.reset(nullptr);

    std::vector<int> vec{ 1, 2, 3, 4 };
    for (int it : vec) {
        std::cout << it << '\n';
    }
}
