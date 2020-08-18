#include <iostream>
#include <list>

int main()
{
    using std::cout;
    using std::endl;

    std::list<int> nums;

    nums.push_front(5);
    nums.push_back(7);

    for (auto i : nums)
        cout << i << endl;
}
