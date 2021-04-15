#ifndef CLASS_VIEWER_HPP
#define CLASS_VIEWER_HPP

#include "class_file.hpp"
#include "constant_pool.hpp"
#include "attributes.hpp"
#include <sstream>
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
  void printConstantClass(cp_info *class_info_entry);
  void printConstantFieldref(cp_info *constant_pool_fieldref);
  void printConstantMethodref(cp_info *methodref_info_entry);
  void printConstantInterfaceMethodref(cp_info *interfacemethodref_info_entry);
  void printConstantString(cp_info *string_info_entry);
  void printConstantInteger(CONSTANT_Integer_info *integer_info_entry);
  void printConstantFloat(CONSTANT_Float_info *float_info_entry);
  void printConstantLong(CONSTANT_Long_info *long_info_entry);
  void printConstantDouble(CONSTANT_Double_info *double_info_entry);
  void printConstantNameAndType(cp_info *nameandtype_info_entry);
  void printConstantUtf8(CONSTANT_Utf8_info *utf8_info_entry);
  void printConstantMethodHandle(cp_info *methodhandle_info_entry);
  void printConstantMethodType(cp_info *methodType_info_entry);
  void printConstantInvokeDynamic(cp_info *invokeDynamic_info_entry);
  void printAttributes(attribute_info **attributes, u2 attribute_count);
  void printAttributeByIndex(attribute_info *attribute);
  void printConstantValueAttribute(ConstantValue_attribute *constantvalue_attribute);
  void printCodeAttribute(Code_attribute *code_attribute);
  void printBytecode(u1 *code, u2 code_length);
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
  void printInstructionParameters(u1 *code, int &index);
  void printTableSwitch(u1 *code, int table_lines_count, int lowbytes, int defaultbytes, int index, int index_with_padding);

  std::string splitByToken(std::string str, int index);
};

#endif