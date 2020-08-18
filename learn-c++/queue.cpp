#include <iostream>
#include <queue>

int main()
{
    using std::cout;
    using std::endl;
    using std::queue;

    queue<int> q;

    q.push(1);
    q.push(3);
    q.push(7);

    cout << q.front() << endl;
    q.pop();
    cout << q.front() << endl;
    q.pop();
    cout << q.front() << endl;
    q.pop();

    return 0;
}
