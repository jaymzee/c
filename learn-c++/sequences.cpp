#include <iostream>
#include <numeric>
#include <array>
#include <vector>

// compile with c++17 enabled for std::size to work

template <class ForwardIt>
void print(ForwardIt first, ForwardIt last)
{
    for (auto it = first; it != last; ++it)
        std::cout << *it << std::endl;
}

template <class ForwardIt>
void do_stuff(const char *msg, int num,
              ForwardIt first, ForwardIt last,
              size_t size)
{
    const int el_size = sizeof *first;

    std::cout << msg << " [" << size << "] " << el_size << std::endl;
    std::iota(first, last, num);
    print(first, last);
}

template <class T>
void do_stuff(const char *msg, int num, T& seq)
{
    do_stuff(msg, num,
             std::begin(seq), std::end(seq),
             std::size(seq));
}

int main()
{
    {
        int nums[5];
        do_stuff("normal c array", 100,
                 std::begin(nums), std::end(nums),
                 sizeof nums / sizeof *nums);
    }
    {
        std::array<int, 5> nums;
        do_stuff("std::array", 200, nums);
    }
    {
        std::vector<int> nums(5);
        do_stuff("std::vector", 300, nums);
    }
}
