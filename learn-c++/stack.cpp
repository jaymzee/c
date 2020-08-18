#include <iostream>
#include <stack>

int main()
{
    using std::cout;
    using std::endl;
    using std::stack;

    stack<int> s;

    cout << std::boolalpha;

    cout << "empty: " << s.empty() << endl;
    cout << "push(3)" << endl;
    s.push(3);

    cout << "empty: " << s.empty() << endl;
    cout << "top: " << s.top() << endl;
    cout << "pop()" << endl;
    s.pop();
    cout << "empty: " << s.empty() << endl;
    return 0;
}
