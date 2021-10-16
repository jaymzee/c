#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <memory>

class Number {
public:
    Number(int x) : _num(std::make_unique<int>(x)) {}

    // return a read-only view of the unique_ptr contents
    const int *ptr() const { return _num.get(); }
private:
    std::unique_ptr<int> _num;
};

/*
 * Follows the Rule of Four and half (Rule of Five with copy and swap idiom)
 * no destructor necessary since all members follow RAII
 */
class Buffer {
public:
    Buffer(size_t size) :
        _size(size),
        _buf(std::make_unique<char []>(size))
    { }

    Buffer(const Buffer& b) :
        _size(b._size),
        _buf(std::make_unique<char []>(_size))
    {
        char *src = b._buf.get();
        std::copy(src, src + _size, _buf.get());
    }

    Buffer(Buffer&& b) noexcept
    {
        swap(*this, b);
    }

    const Buffer& operator=(Buffer rhs) {
        swap(*this, rhs);
        return *this;
    }

    friend void swap(Buffer& b1, Buffer& b2)
    {
        std::swap(b1._size, b2._size);
        std::swap(b1._buf, b2._buf);
    }

    // return a view of the buffer
    char *ptr() { return _buf.get(); }

    size_t size() const { return _size; }
    size_t length() const { return _size; }
private:
    size_t _size;
    std::unique_ptr<char []> _buf;
};

#define BUF_SIZE 16

int main(int argc, char *argv[])
{
    Number num(42);
    std::cout << num.ptr() << " " << *num.ptr() << std::endl;

    Buffer buf(BUF_SIZE);
    strncpy(buf.ptr(), "Hello, World!", BUF_SIZE);
    Buffer buf2(buf);
    Buffer buf3 = buf;

    std::cout << buf.length() << " " << buf.ptr() << std::endl;
    std::cout << buf2.length() << " " << buf2.ptr() << std::endl;
    std::cout << buf3.length() << " " << buf3.ptr() << std::endl;

    return 0;
}
