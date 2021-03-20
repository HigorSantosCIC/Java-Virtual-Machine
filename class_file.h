#ifndef CLASS_FILE_H
#define CLASS_FILE_H

#include "int_types.h"
#include "constant_pool.h"

typedef struct
{
  u4 magic;
  u2 minor_version;
  u2 major_version;
  u2 constant_pool_count;
  cp_info *constant_pool;
  u2 access_flags;
  u2 this_class;
  u2 super_class;
  u2 interfaces_count;
  u2 *interfaces;
  u2 fields_count;
  //TODO: field_info *fields;
  u2 methods_count;
  //TODO: method_info *methods;
  u2 attributes_count;
  //TODO: attribute_info *attributes;
} ClassFile;

#endif