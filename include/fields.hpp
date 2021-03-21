#ifndef FIELDS_HPP
#define FIELDS_HPP

#include "int_types.hpp"
#include "attributes.hpp"

typedef enum
{
  ACC_PUBLIC = 0x0001,
  ACC_PRIVATE = 0x0002,
  ACC_PROTECTED = 0x0004,
  ACC_STATIC = 0x0008,
  ACC_FINAL = 0x0010,
  ACC_VOLATILE = 0x0040,
  ACC_TRANSIENT = 0x0080,
  ACC_SYNTHETIC = 0x1000,
  ACC_ENUM = 0x4000
} access_flag_names;

typedef struct
{
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  attribute_info **attributes;
} field_info;

#endif