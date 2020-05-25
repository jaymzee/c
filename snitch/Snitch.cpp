#include <iostream>
#include "Snitch.h"

Snitch& Snitch::operator=(const Snitch& src)
{
    if (_logging_enabled) {
        std::cout << "S::op= [copy], S(" << _id << ") = S(" <<
                     src._id << "), " << this << std::endl;
    }
    _id = src._id;
    return *this;
}

Snitch& Snitch::operator=(Snitch&& src)
{
    if (_logging_enabled) {
        std::cout << "S::op= [move], S(" << _id << ") = S(" <<
                     src._id << "), " << this << std::endl;
    }
    _id = src._id; // std::swap if a resource
    return *this;
}

void Snitch::log(const char *msg)
{
    if (_logging_enabled) {
        std::cout << msg << " " <<
                     _id << " " << this << std::endl;
    }
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
