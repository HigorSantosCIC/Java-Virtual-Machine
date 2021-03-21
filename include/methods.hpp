#ifndef METHODS_HPP
#define METHODS_HPP

#include "int_types.hpp"
#include "attributes.hpp"

typedef struct
{
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  attribute_info **attributes;
} method_info;

#endif