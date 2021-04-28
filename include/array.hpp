#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <generic_type.hpp>
#include <vector>

class Array
{
public:
    Array();
    ~Array();

    std::vector<GenericType*> data;
};

#endif
