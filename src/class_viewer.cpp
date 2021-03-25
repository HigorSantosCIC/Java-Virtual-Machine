#include "class_viewer.hpp"
#include <algorithm>

ClassViewer::ClassViewer(ClassFile *cf)
{
  class_file = cf;
}

void ClassViewer::printClassFile()
{
  std::cout << std::hex << "Magic number: 0x" << class_file->magic << std::dec << std::endl;
  std::cout << "Minor version: " << class_file->minor_version << std::endl;
  std::cout << "Major version: " << class_file->major_version << std::endl;
  std::cout << "Constant pool count: " << class_file->constant_pool_count << std::endl;
  printConstantPool(class_file->constant_pool, class_file->constant_pool_count);
  std::cout << std::hex << "Access flags: 0x" << class_file->access_flags << std::dec << std::endl;
  std::cout << "This class: " << class_file->this_class << std::endl;
  std::cout << "Super class: " << class_file->super_class << std::endl;
  std::cout << "Interfaces count: " << class_file->interfaces_count << std::endl;

  for (int i = 0; i < class_file->interfaces_count; i++)
  {
    std::cout << "Interface [" << i << "]: " << class_file->interfaces[i] << std::endl;
  }

  std::cout << "Fields count: " << class_file->fields_count << std::endl;
  printFields(class_file->fields, class_file->fields_count);
  std::cout << "Methods count: " << class_file->methods_count << std::endl;
  printMethods(class_file->methods, class_file->methods_count);
  std::cout << "Attribute count: " << class_file->attributes_count << std::endl;
  printAttributes(class_file->attributes, class_file->attributes_count);
}

void ClassViewer::printConstantPool(cp_info **constant_pool, u2 constant_pool_count)
{
  for (int i = 0; i < constant_pool_count - 1; i++)
  {
    std::cout << "Constant [" << i + 1 << "]: " << std::endl;

    printConstantPoolInfo(constant_pool[i]);

    if (constant_pool[i]->tag == CONSTANT_Double || constant_pool[i]->tag == CONSTANT_Long)
    {
      i++;
      std::cout << "Constant [" << i + 1 << "]: "
                << "\n\t(large numeric continued)" << std::endl;
    }
  }
}

void ClassViewer::printConstantPoolInfo(cp_info *constant_pool_entry)
{
  std::cout << "\ttag: " << unsigned(constant_pool_entry->tag) << std::endl;
  ;

  switch (constant_pool_entry->tag)
  {
  case CONSTANT_Class:
    printConstantClass(constant_pool_entry);
    break;
  case CONSTANT_Fieldref:
    printConstantFieldref(constant_pool_entry);
    break;
  case CONSTANT_Methodref:
    printConstantMethodref(constant_pool_entry);
    break;
  case CONSTANT_InterfaceMethodref:
    printConstantInterfaceMethodref(constant_pool_entry);
    break;
  case CONSTANT_String:
    printConstantString(constant_pool_entry);
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
    printConstantNameAndType(constant_pool_entry);
    break;
  case CONSTANT_Utf8:
    printConstantUtf8(constant_pool_entry->info.utf8_info);
    break;
  case CONSTANT_MethodHandle:
    printConstantMethodHandle(constant_pool_entry);
    break;
  case CONSTANT_MethodType:
    printConstantMethodType(constant_pool_entry);
    break;
  case CONSTANT_InvokeDynamic:
    printConstantInvokeDynamic(constant_pool_entry);
    break;
  default:
    break;
  }
}

void ClassViewer::printConstantClass(cp_info *class_info_entry)
{
  std::string name = getNameFromIndex(class_info_entry);
  std::cout << "\tname_index: " << class_info_entry->info.class_info->name_index  << " <" << name << ">" << std::endl;
}

void ClassViewer::printConstantFieldref(cp_info *constant_pool_fieldref)
{
  std::string name = getNameFromIndex(constant_pool_fieldref);
  std::string name_class_index = split(name,0);
  std::string name_and_type_index = split(name,1);
  name_and_type_index = replaceAll( name_and_type_index, ",", " : ");
  std::cout << "\tclass_index: " << constant_pool_fieldref->info.fieldref_info->class_index << " <" << name_class_index << ">" << std::endl;
  std::cout << "\tname_and_type_index: " << constant_pool_fieldref->info.fieldref_info->name_and_type_index  << " <" << name_and_type_index << ">" << std::endl;
}

void ClassViewer::printConstantMethodref(cp_info *methodref_info_entry)
{
  std::string name = getNameFromIndex(methodref_info_entry);
  std::string name_class_index = split(name,0);
  std::string name_and_type_index = split(name,1);
  name_and_type_index = replaceAll( name_and_type_index, ",", " : ");
  std::cout << "\tclass_index: " << methodref_info_entry->info.methodref_info->class_index << " <" << name_class_index << ">" << std::endl;
  std::cout << "\tname_and_type_index: " << methodref_info_entry->info.methodref_info->name_and_type_index  << " <" << name_and_type_index << ">" << std::endl;
}

void ClassViewer::printConstantInterfaceMethodref(cp_info *interfacemethodref_info_entry)
{
  std::string name = getNameFromIndex(interfacemethodref_info_entry);
  std::string name_class_index = split(name,0);
  std::string name_and_type_index = split(name,1);
  name_and_type_index = replaceAll( name_and_type_index, ",", " : ");
  std::cout << "\tclass_index: " << interfacemethodref_info_entry->info.interfaceMethodref_info->class_index << " <" << name_class_index << ">" << std::endl;
  std::cout << "\tname_and_type_index: " << interfacemethodref_info_entry->info.interfaceMethodref_info->name_and_type_index  << " <" << name_and_type_index << ">" << std::endl;
}

void ClassViewer::printConstantString(cp_info *string_info_entry)
{
  std::string name = getNameFromIndex(string_info_entry);
  std::cout << "\tstring_index: " << string_info_entry->info.string_info->string_index << " <" << name << ">" << std::endl;
}

void ClassViewer::printConstantInteger(CONSTANT_Integer_info *integer_info_entry)
{
  std::cout << std::hex << "\tbytes: " << integer_info_entry->bytes << std::dec << std::endl;
}

void ClassViewer::printConstantFloat(CONSTANT_Float_info *float_info_entry)
{
  std::cout << std::hex << "\tbytes: " << float_info_entry->bytes << std::dec << std::endl;
}

void ClassViewer::printConstantLong(CONSTANT_Long_info *long_info_entry)
{
  std::cout << std::hex << "\thigh_bytes: 0x" << long_info_entry->high_bytes << std::dec << std::endl;
  std::cout << std::hex << "\tlow_bytes: 0x" << long_info_entry->low_bytes << std::dec << std::endl;
}

void ClassViewer::printConstantDouble(CONSTANT_Double_info *double_info_entry)
{
  std::cout << std::hex << "\thigh_bytes: 0x" << double_info_entry->high_bytes << std::dec << std::endl;
  std::cout << std::hex << "\tlow_bytes: 0x" << double_info_entry->low_bytes << std::dec << std::endl;
}

void ClassViewer::printConstantNameAndType(cp_info *nameandtype_info_entry)
{
  std::string name = getNameFromIndex(nameandtype_info_entry);
  std::string name_class_index = split(name,0);
  std::string name_descriptor_index = split(name,1);
  name_descriptor_index = replaceAll(name_descriptor_index, ",", " : ");
 
  std::cout << "\tname_index: " << nameandtype_info_entry->info.nameAndType_info->name_index << " <" << name_class_index << ">" << std::endl;
  std::cout << "\tdescriptor_index: " << nameandtype_info_entry->info.nameAndType_info->descriptor_index  << " <" << name_descriptor_index << ">" << std::endl;
}

void ClassViewer::printConstantUtf8(CONSTANT_Utf8_info *utf8_info_entry)
{
  std::cout << "\tlength: " << utf8_info_entry->length << std::endl;
  std::cout << "\tbytes: " << utf8_info_entry->bytes << std::endl;
}

void ClassViewer::printConstantMethodHandle(cp_info *methodhandle_info_entry)
{
  std::string name = getNameFromIndex(methodhandle_info_entry);
  std::cout << "\treference_kind: " << methodhandle_info_entry->info.methodHandle_info->reference_kind << std::endl;
  std::cout << "\treference_index: " << methodhandle_info_entry->info.methodHandle_info->reference_index << " <" << name << ">" << std::endl;
}

void ClassViewer::printConstantMethodType(cp_info *methodType_info_entry)
{
  std::string name = getNameFromIndex(methodType_info_entry);
  std::cout << "\tdescriptor_index: " << methodType_info_entry->info.methodType_info->descriptor_index << " <" << name << ">" << std::endl;
}

void ClassViewer::printConstantInvokeDynamic(cp_info *invokeDynamic_info_entry)
{
  std::string name = getNameFromIndex(invokeDynamic_info_entry);
  std::string name_bootstrap_index = split(name,0);
  std::string name_and_type_index = split(name,1);
  name_and_type_index = replaceAll(name_and_type_index, ",", " : ");
 
  std::cout << "\tbootstrap_method_attr_index: " << invokeDynamic_info_entry->info.invokeDynamic_info->bootstrap_method_attr_index << " <" << name_bootstrap_index << ">" << std::endl;
  std::cout << "\tname_and_type_index: " << invokeDynamic_info_entry->info.invokeDynamic_info->name_and_type_index << " <" << name_and_type_index << ">" << std::endl;
}

void ClassViewer::printAttributes(attribute_info **attributes, u2 attribute_count)
{
  std::string tabs = std::string(tab_count, '\t');

  for (int i = 0; i < attribute_count; i++)
  {
    std::cout << tabs << "Attribute [" << i << "]:" << std::endl;

    printAttributeByIndex(attributes[i]);
  }
}

void ClassViewer::printAttributeByIndex(attribute_info *attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tattribute_name_index: " << attribute->attribute_name_index << std::endl;
  std::cout << tabs << "\tattribute_length: " << attribute->attribute_length << std::endl;

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
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tconstantvalue_index: " << constantvalue_attribute->constantvalue_index << std::endl;
}

void ClassViewer::printCodeAttribute(Code_attribute *code_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tmax_stack: " << code_attribute->max_stack << std::endl;
  std::cout << tabs << "\tmax_locals: " << code_attribute->max_locals << std::endl;
  std::cout << tabs << "\tcode_length: " << code_attribute->code_length << std::endl;

  std::cout << tabs << "\tcode: ";

  for (int i = 0; i < (int)code_attribute->code_length; i++)
  {
    std::cout << unsigned(code_attribute->code[i]);
  }

  std::cout << std::endl;

  std::cout << tabs << "\texception_table_length: " << code_attribute->exception_table_length << std::endl;

  tab_count++;

  for (int i = 0; i < code_attribute->exception_table_length; i++)
  {
    std::cout << tabs << "Exception[" << i << "]" << std::endl;

    printExceptionTable(code_attribute->exception_table[i]);
  }

  tab_count--;

  std::cout << tabs << "\tattributes_count: " << code_attribute->attributes_count << std::endl;

  tab_count++;

  printAttributes(code_attribute->attributes, code_attribute->attributes_count);

  tab_count--;
}

void ClassViewer::printExceptionTable(exception_table_info *exception_table_entry)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tstart_pc: " << exception_table_entry->start_pc << std::endl;
  std::cout << tabs << "\tend_pc: " << exception_table_entry->end_pc << std::endl;
  std::cout << tabs << "\thandler_pc: " << exception_table_entry->handler_pc << std::endl;
  std::cout << tabs << "\tcatch_type: " << exception_table_entry->catch_type << std::endl;
}

void ClassViewer::printExceptionsAttribute(Exceptions_attribute *exceptions_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tnumber_of_exceptions: " << exceptions_attribute->number_of_exceptions << std::endl;
  std::cout << tabs << "\texception_index_table: " << exceptions_attribute->exception_index_table << std::endl;
}

void ClassViewer::printInnerClassesAttribute(InnerClasses_attribute *innerclasses_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tnumber_of_classes: " << innerclasses_attribute->number_of_classes << std::endl;

  tab_count++;

  for (int i = 0; i < innerclasses_attribute->number_of_classes; i++)
  {
    std::cout << tabs << "Class[" << i << "]" << std::endl;

    printClassInfo(innerclasses_attribute->classes[i]);
  }

  tab_count--;
}

void ClassViewer::printClassInfo(classes_info *classes_entry)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tinner_class_info_index: " << classes_entry->inner_class_info_index << std::endl;
  std::cout << tabs << "\touter_class_info_index: " << classes_entry->outer_class_info_index << std::endl;
  std::cout << tabs << "\tinner_name_index: " << classes_entry->inner_name_index << std::endl;
  std::cout << tabs << "\tinner_class_access_flags: " << classes_entry->inner_class_access_flags << std::endl;
}

void ClassViewer::printSourceFileAttribute(SourceFile_attribute *sourcefile_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tsourcefile_index: " << sourcefile_attribute->sourcefile_index << std::endl;
}

void ClassViewer::printLineNumberTableAttribute(LineNumberTable_attribute *linenumbertable_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tline_number_table_length: " << linenumbertable_attribute->line_number_table_length << std::endl;

  tab_count++;

  for (int i = 0; i < linenumbertable_attribute->line_number_table_length; i++)
  {
    std::cout << tabs << "\tLine number table [" << i << "]" << std::endl;

    printLineNumberTable(linenumbertable_attribute->line_number_table[i]);
  }

  tab_count--;
}

void ClassViewer::printLineNumberTable(line_number_table_info *line_number_table_entry)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tstart_pc: " << line_number_table_entry->start_pc << std::endl;
  std::cout << tabs << "\tline_number: " << line_number_table_entry->line_number << std::endl;
}

void ClassViewer::printLocalVariableTableAttribute(LocalVariableTable_attribute *localvariabletable_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tlocal_variable_table_length: " << localvariabletable_attribute->local_variable_table_length << std::endl;

  tab_count++;

  for (int i = 0; i < localvariabletable_attribute->local_variable_table_length; i++)
  {
    std::cout << tabs << "\tLocal variable table [" << i << "]" << std::endl;

    printLocalVariableTable(localvariabletable_attribute->local_variable_table[i]);
  }

  tab_count--;
}

void ClassViewer::printLocalVariableTable(local_variable_table_info *local_variable_table_entry)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "\tstart_pc: " << local_variable_table_entry->start_pc << std::endl;
  std::cout << tabs << "\tlength: " << local_variable_table_entry->length << std::endl;
  std::cout << tabs << "\tname_index: " << local_variable_table_entry->name_index << std::endl;
  std::cout << tabs << "\tdescriptor_index: " << local_variable_table_entry->descriptor_index << std::endl;
  std::cout << tabs << "\tindex: " << local_variable_table_entry->index << std::endl;
}

void ClassViewer::printMethods(method_info **methods, u2 methods_count)
{
  for (int i = 0; i < methods_count; i++)
  {
    std::cout << "Method [" << i << "]:" << std::endl;

    printMethodInfo(methods[i]);
  }
}

void ClassViewer::printMethodInfo(method_info *method)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << std::hex << "\taccess_flags: 0x" << method->access_flags << std::dec << std::endl;
  std::cout << tabs << "\tname_index: " << method->name_index << std::endl;
  std::cout << tabs << "\tdescriptor_index: " << method->descriptor_index << std::endl;
  std::cout << tabs << "\tattributes_count: " << method->attributes_count << std::endl;

  tab_count++;

  printAttributes(method->attributes, method->attributes_count);

  tab_count--;
}

void ClassViewer::printFields(field_info **fields, u2 fields_count)
{
  for (int i = 0; i < fields_count; i++)
  {
    std::cout << "Field [" << i << "]:" << std::endl;

    printFieldInfo(fields[i]);
  }
}

void ClassViewer::printFieldInfo(field_info *field)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << std::hex << "\taccess_flags: 0x" << field->access_flags << std::dec << std::endl;
  std::cout << tabs << "\tname_index: " << field->name_index << std::endl;
  std::cout << tabs << "\tdescriptor_index: " << field->descriptor_index << std::endl;
  std::cout << tabs << "\tattributes_count: " << field->attributes_count << std::endl;

  tab_count++;

  printAttributes(field->attributes, field->attributes_count);

  tab_count--;
}

std::string ClassViewer::getNameFromIndex(cp_info *constant_pool_getname)
{
  std::string s = "";
  std::string s1 = "";
  std::string s2 = "";
  u2 index;

  switch (constant_pool_getname->tag)
  {
  case CONSTANT_Class:
    index = constant_pool_getname->info.class_info->name_index - 1;
    return getNameFromIndex(class_file->constant_pool[index]);
    break;
  case CONSTANT_String:
    index = constant_pool_getname->info.string_info->string_index - 1;
    return getNameFromIndex(class_file->constant_pool[index]);
    break;
  case CONSTANT_Fieldref:
    index = constant_pool_getname->info.fieldref_info->class_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);
    index = constant_pool_getname->info.fieldref_info->name_and_type_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);
    return s1+","+s2;
    break;
  case CONSTANT_Methodref:
    index = constant_pool_getname->info.methodref_info->class_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);
    index = constant_pool_getname->info.methodref_info->name_and_type_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);
    return s1+","+s2;
    break;
  case CONSTANT_InterfaceMethodref:
    index = constant_pool_getname->info.interfaceMethodref_info->class_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);
    index = constant_pool_getname->info.interfaceMethodref_info->name_and_type_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);
    return s1+","+s2;
    break;
  case CONSTANT_NameAndType:
    index = constant_pool_getname->info.nameAndType_info->name_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);
    index = constant_pool_getname->info.nameAndType_info->descriptor_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);
    return s1+","+s2;
    break;
  case CONSTANT_MethodHandle:
    index = constant_pool_getname->info.methodHandle_info->reference_index - 1;
    return getNameFromIndex(class_file->constant_pool[index]);
    break;
  case CONSTANT_MethodType:
    index = constant_pool_getname->info.methodType_info->descriptor_index - 1;
    return getNameFromIndex(class_file->constant_pool[index]);
    break;
  case CONSTANT_InvokeDynamic:
    index = constant_pool_getname->info.invokeDynamic_info->bootstrap_method_attr_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);
    index = constant_pool_getname->info.invokeDynamic_info->name_and_type_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);
    return s1+","+s2;
    break;
  case CONSTANT_Utf8:
    for(int i = 0; i < constant_pool_getname->info.utf8_info->length;i++){
      s += constant_pool_getname->info.utf8_info->bytes[i];
    }
    return s;
    break;
  
  default:
    std::cout << "VALOR DE TAG NÃO ENCONTRADO! tag: " <<  constant_pool_getname->tag << std::endl;
    return "";
    break;
  }

}

std::string ClassViewer::replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::string ClassViewer::split(std::string str, int position){
int i = 0;
std::string result = "";
bool flag = false;
if(position){
  while(str[i] != '\0'){
    if(flag)
      result += str[i];
    if(str[i] == ',')
      flag = true;
    i++;
  }
}else{
  while(str[i] != ',' && str[i] != '\0'){
    result += str[i];
    i++;
  }
}
return result;
}