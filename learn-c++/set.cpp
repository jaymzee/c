#include <iostream>
#include <set>

int main()
{
    using std::cout;
    using std::endl;
    using std::set;
    using std::string;

    set<string> s1;


    s1.insert("three");
    s1.insert("five");

    cout << "size: " << s1.size() << endl;
    for (auto str : s1)
        cout << str << endl;
}
