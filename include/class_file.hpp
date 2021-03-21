#ifndef CLASS_FILE_HPP
#define CLASS_FILE_HPP

#include "int_types.hpp"
#include "constant_pool.hpp"
#include "fields.hpp"
#include "methods.hpp"
#include "attributes.hpp"

typedef struct
{
  u4 magic;
  u2 minor_version;
  u2 major_version;
  u2 constant_pool_count;
  cp_info **constant_pool;
  u2 access_flags;
  u2 this_class;
  u2 super_class;
  u2 interfaces_count;
  u2 *interfaces;
  u2 fields_count;
  field_info **fields;
  u2 methods_count;
  method_info **methods;
  u2 attributes_count;
  attribute_info **attributes;
} ClassFile;

#endif