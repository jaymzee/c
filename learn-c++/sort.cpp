#include <iostream>
#include <algorithm>

int mygreater(int x, int y)
{
    return x > y;
}

int myless(int x, int y)
{
    return x < y;
}

int main()
{
    int nums[] = {5,3,7,1,2,8};

    // either one works
    std::sort(nums, nums + 6, myless);
    std::sort(nums, nums + 6, std::less<int>());

    for (int i : nums)
        std::cout << i << std::endl;
}
