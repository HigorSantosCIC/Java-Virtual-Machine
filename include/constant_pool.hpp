#ifndef CONSTANT_POOL_HPP
#define CONSTANT_POOL_HPP

#include "int_types.hpp"

typedef enum
{
  CONSTANT_Utf8 = 1,
  CONSTANT_Integer = 3,
  CONSTANT_Float = 4,
  CONSTANT_Long = 5,
  CONSTANT_Double = 6,
  CONSTANT_Class = 7,
  CONSTANT_String = 8,
  CONSTANT_Fieldref = 9,
  CONSTANT_Methodref = 10,
  CONSTANT_InterfaceMethodref = 11,
  CONSTANT_NameAndType = 12,
  CONSTANT_MethodHandle = 15,
  CONSTANT_MethodType = 16,
  CONSTANT_InvokeDynamic = 18,
} constant_types;

typedef struct
{
  u2 name_index;
} CONSTANT_Class_info;

typedef struct
{
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct
{
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct
{
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct
{
  u2 string_index;
} CONSTANT_String_info;

typedef struct
{
  u4 bytes;
} CONSTANT_Integer_info;

typedef struct
{
  u4 bytes;
} CONSTANT_Float_info;

typedef struct
{
  u4 high_bytes;
  u4 low_bytes;
} CONSTANT_Long_info;

typedef struct
{
  u4 high_bytes;
  u4 low_bytes;
} CONSTANT_Double_info;

typedef struct
{
  u2 name_index;
  u2 descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct
{
  u2 length;
  u1 *bytes;
} CONSTANT_Utf8_info;

typedef struct
{
  u1 reference_kind;
  u2 reference_index;
} CONSTANT_MethodHandle_info;

typedef struct
{
  u2 descriptor_index;
} CONSTANT_MethodType_info;

typedef struct
{
  u2 bootstrap_method_attr_index;
  u2 name_and_type_index;
} CONSTANT_InvokeDynamic_info;

typedef struct
{
  u1 tag;
  union
  {
    CONSTANT_Class_info *class_info;
    CONSTANT_Fieldref_info *fieldref_info;
    CONSTANT_Methodref_info *methodref_info;
    CONSTANT_InterfaceMethodref_info *interfaceMethodref_info;
    CONSTANT_String_info *string_info;
    CONSTANT_Integer_info *integer_info;
    CONSTANT_Float_info *float_info;
    CONSTANT_Long_info *long_info;
    CONSTANT_Double_info *double_info;
    CONSTANT_NameAndType_info *nameAndType_info;
    CONSTANT_Utf8_info *utf8_info;
    CONSTANT_MethodHandle_info *methodHandle_info;
    CONSTANT_MethodType_info *methodType_info;
    CONSTANT_InvokeDynamic_info *invokeDynamic_info;
  } info;
} cp_info;

#endif