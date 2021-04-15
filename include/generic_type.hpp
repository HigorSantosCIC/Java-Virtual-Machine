#ifndef GENERIC_TYPE_HPP
#define GENERIC_TYPE_HPP

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
    } data;
} GenericType;

#endif