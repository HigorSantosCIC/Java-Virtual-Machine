#ifndef CLASS_VIEWER_HPP
#define CLASS_VIEWER_HPP

#include "class_file.hpp"
#include "constant_pool.hpp"
#include "attributes.hpp"
#include <string>

class ClassViewer
{
public:
  ClassViewer(ClassFile *cf);

  void printClassFile();

private:
  ClassFile *class_file;
  int tab_count = 0;

  void printInterfaces();
  void printConstantPool(cp_info **constant_pool, u2 constant_pool_count);
  void printConstantPoolInfo(cp_info *constant_pool_entry);
  void printConstantClass(CONSTANT_Class_info *class_info_entry);
  void printConstantFieldref(CONSTANT_Fieldref_info *fieldref_info_entry);
  void printConstantMethodref(CONSTANT_Methodref_info *methodref_info_entry);
  void printConstantInterfaceMethodref(CONSTANT_InterfaceMethodref_info *interfacemethodref_info_entry);
  void printConstantString(CONSTANT_String_info *string_info_entry);
  void printConstantInteger(CONSTANT_Integer_info *integer_info_entry);
  void printConstantFloat(CONSTANT_Float_info *float_info_entry);
  void printConstantLong(CONSTANT_Long_info *long_info_entry);
  void printConstantDouble(CONSTANT_Double_info *double_info_entry);
  void printConstantNameAndType(CONSTANT_NameAndType_info *nameandtype_info_entry);
  void printConstantUtf8(CONSTANT_Utf8_info *utf8_info_entry);
  void printConstantMethodHandle(CONSTANT_MethodHandle_info *methodhandle_info_entry);
  void printConstantMethodType(CONSTANT_MethodType_info *methodType_info_entry);
  void printConstantInvokeDynamic(CONSTANT_InvokeDynamic_info *invokeDynamic_info_entry);
  void printAttributes(attribute_info **attributes, u2 attribute_count);
  void printAttributeByIndex(attribute_info *attribute);
  void printConstantValueAttribute(ConstantValue_attribute *constantvalue_attribute);
  void printCodeAttribute(Code_attribute *code_attribute);
  void printExceptionTable(exception_table_info *exception_table_entry);
  void printExceptionsAttribute(Exceptions_attribute *exceptions_attribute);
  void printInnerClassesAttribute(InnerClasses_attribute *innerclasses_attribute);
  void printClassInfo(classes_info *classes_entry);
  void printSourceFileAttribute(SourceFile_attribute *sourcefile_attribute);
  void printLineNumberTableAttribute(LineNumberTable_attribute *linenumbertable_attribute);
  void printLineNumberTable(line_number_table_info *line_number_table_entry);
  void printLocalVariableTableAttribute(LocalVariableTable_attribute *localvariabletable_attribute);
  void printLocalVariableTable(local_variable_table_info *local_variable_table_entry);
  void printMethods(method_info **methods, u2 methods_count);
  void printMethodInfo(method_info *method);
  void printFields(field_info **fields, u2 fields_count);
  void printFieldInfo(field_info *field);
};

#endif