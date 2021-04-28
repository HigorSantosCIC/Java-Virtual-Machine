#ifndef GENERIC_TYPE_HPP
#define GENERIC_TYPE_HPP

#include "int_types.hpp"
#include <string>

// Forward declaration to correct circular reference between Array and GenericType
class Array;
typedef struct
{
    union
    {
        bool boolean_value;
        int8_t byte_value;
        u1 char_value;
        double double_value;
        float float_value;
        int32_t int_value;
        int64_t long_value;
        int16_t short_value;
        std::string *string_value;
        Array *array_value;
    } data;
} GenericType;

#endif
