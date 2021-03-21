#ifndef MEMORY_CLEANER_HPP
#define MEMORY_CLEANER_HPP

#include <cstdlib>
#include <string.h>

#include "class_file.hpp"
#include "constant_pool.hpp"
#include "methods.hpp"
#include "attributes.hpp"
#include "int_types.hpp"

class MemoryCleaner
{
public:
  MemoryCleaner(ClassFile *class_file);

  void freeClassFileMemory();

private:
  ClassFile *class_file;

  void freeConstantPool(cp_info **constant_pool, u2 constant_pool_count);
  void freeConstantPoolInfo(cp_info *constant_pool_entry);

  void freeAttributes(attribute_info **attributes, u2 attributes_count);
  void freeAttributeInfoByIndex(attribute_info *attribute);

  void freeCodeAttribute(Code_attribute *code_attribute);
  void freeExceptionsAttribute(Exceptions_attribute *exceptions_attribute);
  void freeInnerClassesAttribute(InnerClasses_attribute *innerclasses_attribute);
  void freeLineNumberTableAttribute(LineNumberTable_attribute *linenumbertable_attribute);
  void freeLocalVariableTableAttribute(LocalVariableTable_attribute *localvariabletable_attribute);

  void freeMethods(method_info **methods, u2 method_count);
  void freeMethodInfo(method_info *method);

  void freeFields(field_info **fields, u2 fields_count);
  void freeFieldInfo(field_info *field);
};

#endif