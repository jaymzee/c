#include <array>
#include <cstdio>
#include <iostream>

using namespace std;

constexpr int max(int a, int b) {
    return a > b ? a : b;
}

constexpr int min(int a, int b) {
    return a > b ? b : a;
}

int main()
{
    // you can use constexpr functions where you'd normally expect a
    // compile time constant
    array<int, max(2,3)> xs{};
    array<int, min(2,3)> ys{};
    int nums[min(3,4)];

    cout << "xs = [ ";
    for (auto x : xs)
        cout << x << ' ';
    cout << "]\n";

    cout << "ys = [ ";
    for (auto y : ys)
        cout << y << ' ';
    cout << "]\n";

    cout << "nums = [ ";
    for (auto n : nums)
        cout << n << ' ';
    cout << "]\n";


}
