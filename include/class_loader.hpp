#ifndef CLASS_LOADER_HPP
#define CLASS_LOADER_HPP

#include <iostream>
#include <string.h>
#include <string>
#include "int_types.hpp"
#include "class_file.hpp"
#include "constant_pool.hpp"
#include "fields.hpp"
#include "attributes.hpp"
#include "methods.hpp"

class ClassLoader
{
public:
  ClassLoader(const char *file_name);

  void readClassFile();

  ClassFile *getClassFile();

private:
  FILE *fp;
  ClassFile *class_file;

  u1 readU1();
  u2 readU2();
  u4 readU4();
  CONSTANT_Class_info *readConstantClassInfo();
  CONSTANT_Fieldref_info *readConstantFieldrefInfo();
  CONSTANT_Methodref_info *readConstantMethodrefInfo();
  CONSTANT_InterfaceMethodref_info *readConstantInterfaceMethodrefInfo();
  CONSTANT_String_info *readConstantStringInfo();
  CONSTANT_MethodHandle_info *readConstantMethodHandleInfo();
  CONSTANT_NameAndType_info *readConstantNameAndTypeInfo();
  CONSTANT_Utf8_info *readConstantUtf8Info();
  CONSTANT_Float_info *readConstantFloatInfo();
  CONSTANT_Integer_info *readConstantIntegerInfo();
  CONSTANT_Long_info *readConstantLongInfo();
  CONSTANT_Double_info *readConstantDoubleInfo();
  CONSTANT_MethodType_info *readConstantMethodTypeInfo();
  CONSTANT_InvokeDynamic_info *readConstantInvokeDynamicInfo();

  ConstantValue_attribute *readConstantValueAttribute();
  Code_attribute *readCodeAttribute();
  Exceptions_attribute *readExceptionsAttribute();
  Synthetic_attribute *readSyntheticAttribute();
  SourceFile_attribute *readSourceFileAttribute();
  Deprecated_attribute *readDeprecatedAttribute();
  InnerClasses_attribute *readInnerClassesAttribute();
  LineNumberTable_attribute *readLineNumberTableAttribute();
  LocalVariableTable_attribute *readLocalVariableTableAttribute();

  field_info *readFieldInfo();
  cp_info *readCpInfo();
  attribute_info *readAttributeInfo();
  exception_table_info *readExceptionTableInfo();
  classes_info *readClassesInfo();
  line_number_table_info *readLineNumberTable();
  local_variable_table_info *readLocalVariableTable();
  method_info *readMethodInfo();

  bool verifyMagic(u4 magic);
};

#endif