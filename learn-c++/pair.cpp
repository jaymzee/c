#include <iostream>
#include <utility>

int main()
{
    using std::cout;
    using std::endl;
    using std::string;
    using std::pair;

    pair<string, double> p("pi", 3.14);

    p.first.push_back('p');
    p.first.insert(0,"item");

    cout << "(\"" << p.first << "\", " << p.second << ')' << endl;

    return 0;
}
