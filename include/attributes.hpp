#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include "int_types.hpp"
#include "constant_pool.hpp"
#include <iostream>
#include <string>

// Attribute names cannot be mapped to strings through enums
#define CONSTANT_VALUE "ConstantValue"
#define CODE "Code"
#define EXCEPTIONS "Exceptions"
#define INNER_CLASSES "InnerClasses"
#define SOURCE_FILE "SourceFile"
#define DEPRECATED "Deprecated"
#define SYNTHETIC "Synthetic"
#define LINE_NUMBER_TABLE "LineNumberTable"
#define LOCAL_VARIABLE_TABLE "LocalVariableTable"

namespace AttributeUtils
{
  // Attribute type is determined by an utf8_info in constant pool, indexed by attribute_name_index
  extern std::string getAttributeType(cp_info **constant_pool, u2 index);
}

struct attribute_info;

typedef struct
{
  u2 constantvalue_index;
} ConstantValue_attribute;

typedef struct
{
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} exception_table_info;

typedef struct
{
  u2 max_stack;
  u2 max_locals;
  u4 code_length;
  u1 *code;
  u2 exception_table_length;
  exception_table_info **exception_table;
  u2 attributes_count;
  attribute_info **attributes;
} Code_attribute;

typedef struct
{
  u2 number_of_exceptions;
  u2 *exception_index_table;
} Exceptions_attribute;

typedef struct attributes
{
  u2 inner_class_info_index;
  u2 outer_class_info_index;
  u2 inner_name_index;
  u2 inner_class_access_flags;
} classes_info;

typedef struct
{
  u2 number_of_classes;
  classes_info **classes;
} InnerClasses_attribute;

typedef struct
{

} Synthetic_attribute;

typedef struct
{
  u2 sourcefile_index;
} SourceFile_attribute;

typedef struct
{
  u2 start_pc;
  u2 line_number;
} line_number_table_info;

typedef struct
{
  u2 line_number_table_length;
  line_number_table_info **line_number_table;
} LineNumberTable_attribute;

typedef struct
{
  u2 start_pc;
  u2 length;
  u2 name_index;
  u2 descriptor_index;
  u2 index;
} local_variable_table_info;

typedef struct
{
  u2 local_variable_table_length;
  local_variable_table_info **local_variable_table;
} LocalVariableTable_attribute;

typedef struct
{

} Deprecated_attribute;

typedef struct attribute_info
{
  u2 attribute_name_index;
  u4 attribute_length;
  union
  {
    ConstantValue_attribute *constantvalue_attribute;
    Code_attribute *code_attribute;
    Exceptions_attribute *exceptions_attribute;
    Synthetic_attribute *synthetic_attribute;
    SourceFile_attribute *sourcefile_attribute;
    Deprecated_attribute *deprecated_attribute;
    InnerClasses_attribute *innerclasses_attribute;
    LineNumberTable_attribute *linenumbertable_attribute;
    LocalVariableTable_attribute *localvariabletable_attribute;
  } attribute;
} attribute_info;

#endif