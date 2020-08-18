#include <string>
#include <iostream>

std::string foo(int x)
{
    return std::string("potato ") + std::to_string(x) + '*';
}

int main()
{
    using std::string;
    using std::cout;
    using std::endl;

    string msg = "hello";
    msg += " world!";

    msg += foo(3);
    msg += foo(8);

    cout << "char at offset 4 is " << msg.at(4) << endl;
    cout << "or found at " << msg.find("or") << endl;
    cout << msg << endl;
}
