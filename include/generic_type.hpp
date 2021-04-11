#ifndef GENERIC_TYPE_HPP
#define GENERIC_TYPE_HPP

typedef struct
{
    union
    {
        bool booleanValue;
        int8_t byteValue;
        u1 charValue;
        double doubleValue;
        float floatValue;
        int32_t intValue;
        int64_t longValue;
        int16_t shortValue;
    } data;
} GenericType;

#endif