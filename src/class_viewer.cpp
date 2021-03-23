#include "class_viewer.hpp"

ClassViewer::ClassViewer(ClassFile *cf)
{
  class_file = cf;
}

void ClassViewer::printClassFile()
{
  std::cout << std::hex << "Minor version: " << class_file->minor_version << std::endl;
  std::cout << std::hex << "Major version: " << class_file->major_version << std::endl;
  std::cout << std::hex << "Constant pool count: " << class_file->constant_pool_count << std::endl;
  printConstantPool(class_file->constant_pool, class_file->constant_pool_count);
  std::cout << "Access flags: " << class_file->access_flags << std::endl;
  std::cout << "This class: " << class_file->this_class << std::endl;
  std::cout << "Super class: " << class_file->super_class << std::endl;
  std::cout << "Interfaces count: " << class_file->interfaces_count << std::endl;
  std::cout << "Interfaces: " << class_file->interfaces << std::endl;
  std::cout << "Fields count: " << class_file->fields_count << std::endl;
  // TODO: printFields();
  std::cout << "Methods count: " << class_file->methods_count << std::endl;
  // TODO: methods();
  std::cout << "Attribute count: " << class_file->attributes_count << std::endl;
  printAttributes(class_file->attributes, class_file->attributes_count);
}

void ClassViewer::printConstantPool(cp_info **constant_pool, u2 constant_pool_count)
{
  for (int i = 0; i < constant_pool_count - 1; i++)
  {
    printConstantPoolInfo(constant_pool[i]);
  }
}

void ClassViewer::printConstantPoolInfo(cp_info *constant_pool_entry)
{
  std::cout << "Constant pool tag: " << constant_pool_entry->tag << std::endl;

  switch (constant_pool_entry->tag)
  {
  case CONSTANT_Class:
    printConstantClass(constant_pool_entry->info.class_info);
    break;
  case CONSTANT_Fieldref:
    printConstantFieldref(constant_pool_entry->info.fieldref_info);
    break;
  case CONSTANT_Methodref:
    printConstantMethodref(constant_pool_entry->info.methodref_info);
    break;
  case CONSTANT_InterfaceMethodref:
    printConstantInterfaceMethodref(constant_pool_entry->info.interfaceMethodref_info);
    break;
  case CONSTANT_String:
    printConstantString(constant_pool_entry->info.string_info);
    break;
  case CONSTANT_Integer:
    printConstantInteger(constant_pool_entry->info.integer_info);
    break;
  case CONSTANT_Float:
    printConstantFloat(constant_pool_entry->info.float_info);
    break;
  case CONSTANT_Long:
    printConstantLong(constant_pool_entry->info.long_info);
    break;
  case CONSTANT_Double:
    printConstantDouble(constant_pool_entry->info.double_info);
    break;
  case CONSTANT_NameAndType:
    printConstantNameAndType(constant_pool_entry->info.nameAndType_info);
    break;
  case CONSTANT_Utf8:
    printConstantUtf8(constant_pool_entry->info.utf8_info);
    break;
  case CONSTANT_MethodHandle:
    printConstantMethodHandle(constant_pool_entry->info.methodHandle_info);
    break;
  case CONSTANT_MethodType:
    printConstantMethodType(constant_pool_entry->info.methodType_info);
    break;
  case CONSTANT_InvokeDynamic:
    printConstantInvokeDynamic(constant_pool_entry->info.invokeDynamic_info);
    break;
  default:
    break;
  }
}

void ClassViewer::printConstantClass(CONSTANT_Class_info *class_info_entry)
{
  std::cout << "\tname_index: " << class_info_entry->name_index << std::endl;
}

void ClassViewer::printConstantFieldref(CONSTANT_Fieldref_info *fieldref_info_entry)
{
  std::cout << "\tclass_index: " << fieldref_info_entry->class_index << std::endl;
  std::cout << "\tname_and_type_index: " << fieldref_info_entry->name_and_type_index << std::endl;
}

void ClassViewer::printConstantMethodref(CONSTANT_Methodref_info *methodref_info_entry)
{
  std::cout << "\tclass_index: " << methodref_info_entry->class_index << std::endl;
  std::cout << "\tname_and_type_index: " << methodref_info_entry->name_and_type_index << std::endl;
}

void ClassViewer::printConstantInterfaceMethodref(CONSTANT_InterfaceMethodref_info *interfacemethodref_info_entry)
{
  std::cout << "\tclass_index: " << interfacemethodref_info_entry->class_index << std::endl;
  std::cout << "\tname_and_type_index: " << interfacemethodref_info_entry->name_and_type_index << std::endl;
}

void ClassViewer::printConstantString(CONSTANT_String_info *string_info_entry)
{
  std::cout << "\tstring_index: " << string_info_entry->string_index << std::endl;
}

void ClassViewer::printConstantInteger(CONSTANT_Integer_info *integer_info_entry)
{
  std::cout << "\tbytes: " << integer_info_entry->bytes << std::endl;
}

void ClassViewer::printConstantFloat(CONSTANT_Float_info *float_info_entry)
{
  std::cout << "\tbytes: " << float_info_entry->bytes << std::endl;
}

void ClassViewer::printConstantLong(CONSTANT_Long_info *long_info_entry)
{
  std::cout << "\thigh_bytes: " << long_info_entry->high_bytes << std::endl;
  std::cout << "\tlow_bytes: " << long_info_entry->low_bytes << std::endl;
}

void ClassViewer::printConstantDouble(CONSTANT_Double_info *double_info_entry)
{
  std::cout << "\thigh_bytes: " << double_info_entry->high_bytes << std::endl;
  std::cout << "\tlow_bytes: " << double_info_entry->low_bytes << std::endl;
}

void ClassViewer::printConstantNameAndType(CONSTANT_NameAndType_info *nameandtype_info_entry)
{
  std::cout << "\tname_index: " << nameandtype_info_entry->name_index << std::endl;
  std::cout << "\tdescriptor_index: " << nameandtype_info_entry->descriptor_index << std::endl;
}

void ClassViewer::printConstantUtf8(CONSTANT_Utf8_info *utf8_info_entry)
{
  std::cout << "\tlength: " << utf8_info_entry->length << std::endl;
  std::cout << "\tbytes: " << utf8_info_entry->bytes << std::endl;
}

void ClassViewer::printConstantMethodHandle(CONSTANT_MethodHandle_info *methodhandle_info_entry)
{
  std::cout << "\treference_kind: " << methodhandle_info_entry->reference_kind << std::endl;
  std::cout << "\treference_index: " << methodhandle_info_entry->reference_index << std::endl;
}

void ClassViewer::printConstantMethodType(CONSTANT_MethodType_info *methodType_info_entry)
{
  std::cout << "\tdescriptor_index: " << methodType_info_entry->descriptor_index << std::endl;
}

void ClassViewer::printConstantInvokeDynamic(CONSTANT_InvokeDynamic_info *invokeDynamic_info_entry)
{
  std::cout << "\tbootstrap_method_attr_index: " << invokeDynamic_info_entry->bootstrap_method_attr_index << std::endl;
  std::cout << "\tname_and_type_index: " << invokeDynamic_info_entry->name_and_type_index << std::endl;
}

void ClassViewer::printAttributes(attribute_info **attributes, u2 attribute_count)
{
  for (int i = 0; i < attribute_count; i++)
  {
    printAttributeByIndex(attributes[i]);
  }
}

void ClassViewer::printAttributeByIndex(attribute_info *attribute)
{
  std::cout << "attribute_name_index: " << attribute->attribute_name_index << std::endl;
  std::cout << "attribute_length: " << attribute->attribute_length << std::endl;

  std::string attribute_name = AttributeUtils::getAttributeType(class_file->constant_pool, attribute->attribute_name_index);

  if (attribute_name == CONSTANT_VALUE)
  {
    printConstantValueAttribute(attribute->attribute.constantvalue_attribute);
  }
  else if (attribute_name == CODE)
  {
    printCodeAttribute(attribute->attribute.code_attribute);
  }
  else if (attribute_name == EXCEPTIONS)
  {
    printExceptionsAttribute(attribute->attribute.exceptions_attribute);
  }
  else if (attribute_name == INNER_CLASSES)
  {
    printInnerClassesAttribute(attribute->attribute.innerclasses_attribute);
  }
  else if (attribute_name == SOURCE_FILE)
  {
    printSourceFileAttribute(attribute->attribute.sourcefile_attribute);
  }
  else if (attribute_name == LINE_NUMBER_TABLE)
  {
    printLineNumberTableAttribute(attribute->attribute.linenumbertable_attribute);
  }
  else if (attribute_name == LOCAL_VARIABLE_TABLE)
  {
    printLocalVariableTableAttribute(attribute->attribute.localvariabletable_attribute);
  }
}

void ClassViewer::printConstantValueAttribute(ConstantValue_attribute *constantvalue_attribute)
{
  std::cout << "constantvalue_index: " << constantvalue_attribute->constantvalue_index << std::endl;
}

void ClassViewer::printCodeAttribute(Code_attribute *code_attribute)
{
  std::cout << "max_stack: " << code_attribute->max_stack << std::endl;
  std::cout << "max_locals: " << code_attribute->max_locals << std::endl;
  std::cout << "code_length: " << code_attribute->code_length << std::endl;
  std::cout << "code: " << code_attribute->code << std::endl;
  std::cout << "exception_table_length: " << code_attribute->exception_table_length << std::endl;

  for (int i = 0; i < code_attribute->exception_table_length; i++)
  {
    printExceptionTable(code_attribute->exception_table[i]);
  }

  std::cout << "attributes_count: " << code_attribute->attributes_count << std::endl;

  for (int i = 0; i < code_attribute->attributes_count; i++)
  {
    printAttributes(code_attribute->attributes, code_attribute->attributes_count);
  }
}

void ClassViewer::printExceptionTable(exception_table_info *exception_table_entry)
{
  std::cout << "start_pc: " << exception_table_entry->start_pc << std::endl;
  std::cout << "end_pc: " << exception_table_entry->end_pc << std::endl;
  std::cout << "handler_pc: " << exception_table_entry->handler_pc << std::endl;
  std::cout << "catch_type: " << exception_table_entry->catch_type << std::endl;
}

void ClassViewer::printExceptionsAttribute(Exceptions_attribute *exceptions_attribute)
{
  std::cout << "number_of_exceptions: " << exceptions_attribute->number_of_exceptions << std::endl;
  std::cout << "exception_index_table: " << exceptions_attribute->exception_index_table << std::endl;
}

void ClassViewer::printInnerClassesAttribute(InnerClasses_attribute *innerclasses_attribute)
{
  std::cout << "number_of_classes: " << innerclasses_attribute->number_of_classes << std::endl;

  for (int i = 0; i < innerclasses_attribute->number_of_classes; i++)
  {
    printClassInfo(innerclasses_attribute->classes[i]);
  }
}

void ClassViewer::printClassInfo(classes_info *classes_entry)
{
  std::cout << "inner_class_info_index: " << classes_entry->inner_class_info_index << std::endl;
  std::cout << "outer_class_info_index: " << classes_entry->outer_class_info_index << std::endl;
  std::cout << "inner_name_index: " << classes_entry->inner_name_index << std::endl;
  std::cout << "inner_class_access_flags: " << classes_entry->inner_class_access_flags << std::endl;
}

void ClassViewer::printSourceFileAttribute(SourceFile_attribute *sourcefile_attribute)
{
  std::cout << "sourcefile_index: " << sourcefile_attribute->sourcefile_index << std::endl;
}

void ClassViewer::printLineNumberTableAttribute(LineNumberTable_attribute *linenumbertable_attribute)
{
  std::cout << "line_number_table_length: " << linenumbertable_attribute->line_number_table_length << std::endl;

  for (int i = 0; i < linenumbertable_attribute->line_number_table_length; i++)
  {
    printLineNumberTable(linenumbertable_attribute->line_number_table[i]);
  }
}

void ClassViewer::printLineNumberTable(line_number_table_info *line_number_table_entry)
{
  std::cout << "start_pc: " << line_number_table_entry->start_pc << std::endl;
  std::cout << "line_number: " << line_number_table_entry->line_number << std::endl;
}

void ClassViewer::printLocalVariableTableAttribute(LocalVariableTable_attribute *localvariabletable_attribute)
{
  std::cout << "local_variable_table_length: " << localvariabletable_attribute->local_variable_table_length << std::endl;

  for (int i = 0; i < localvariabletable_attribute->local_variable_table_length; i++)
  {
    printLocalVariableTable(localvariabletable_attribute->local_variable_table[i]);
  }
}

void ClassViewer::printLocalVariableTable(local_variable_table_info *local_variable_table_entry)
{
  std::cout << "start_pc: " << local_variable_table_entry->start_pc << std::endl;
  std::cout << "length: " << local_variable_table_entry->length << std::endl;
  std::cout << "name_index: " << local_variable_table_entry->name_index << std::endl;
  std::cout << "descriptor_index: " << local_variable_table_entry->descriptor_index << std::endl;
  std::cout << "index: " << local_variable_table_entry->index << std::endl;
}