#include <iostream>
#include <queue>

int main()
{
    using std::cout;
    using std::endl;
    using std::greater;
    using std::priority_queue;
    using std::vector;

    priority_queue<int, vector<int>, greater<int> > q;

    q.push(3);
    q.push(5);
    q.push(1);

    cout << q.top() << endl;
}
