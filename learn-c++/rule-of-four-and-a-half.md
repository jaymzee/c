# 1 - the destructor
can be left undefined if all non-trivial members use RAII
# 2 - the copy constructor
Put what you can in member initialization list. Call std::copy on any member
data that still needs to be copied.
# 3 - the assignment operator
Copy and swap by passing the rhs by value and call the class's swap function
on all members. Since rhs is passed by value, assignment and move assignement
are unified.
# 4 - move constructor
Declare as noexcept to ensure move constructor is used in all possible cases.
Call the class's swap function.
# and a half - copy swap idiom
class should implement a swap function (friend)
