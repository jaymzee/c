#include <iostream>
#include <map>

int main()
{
    using std::cout;
    using std::endl;
    using std::pair;
    using std::map;
    using std::string;

    map<string, int> m;

    m.insert(pair<string, int>("george", 5));
    m.insert(pair<string, int>("mike", 3));

    auto it = m.find("mike");
    if (it != m.end())
        cout << "found mike " << it->second << endl;

    cout << "map members:" << endl;
    for (auto i = m.begin(); i != m.end(); i++)
        cout << "  " << i->first << ":" << i->second << endl;
}
