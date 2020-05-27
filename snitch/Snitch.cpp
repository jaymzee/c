#include <iostream>
#include "Snitch.h"

Snitch::Snitch(int id) : _id(id)
{
    log("S::ctor");
}

Snitch::Snitch(const Snitch& src) noexcept : _id(src._id)
{
    log("S::ctor [copy]");
}

Snitch::Snitch(Snitch&& src) noexcept : _id(src._id)
{
    log("S::ctor [move]");
}

Snitch::~Snitch()
{
    log("S::dtor");
}

Snitch& Snitch::operator=(const Snitch& rhs)
{
    if (_logging_enabled) {
        std::cout << "S::op= [copy], S(" << _id << ") = S(" <<
                     rhs._id << "), " << this << std::endl;
    }
    _id = rhs._id;
    return *this;
}

Snitch& Snitch::operator=(Snitch&& rhs)
{
    if (_logging_enabled) {
        std::cout << "S::op= [move], S(" << _id << ") = S(" <<
                     rhs._id << "), " << this << std::endl;
    }
    _id = rhs._id; // std::swap if a resource
    return *this;
}

void Snitch::log(const char *msg)
{
    if (_logging_enabled) {
        std::cout << msg << " " <<
                     _id << " " << this << std::endl;
    }
}

int Snitch::get_id() const
{
    return _id;
}

void Snitch::disable_log()
{
    Snitch::_logging_enabled = false;
}

void Snitch::enable_log()
{
    Snitch::_logging_enabled = true;
}

bool Snitch::_logging_enabled = true;
