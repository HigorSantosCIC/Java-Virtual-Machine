#include "memory_cleaner.hpp"

MemoryCleaner::MemoryCleaner(ClassFile *cf)
{
  class_file = cf;
}

void MemoryCleaner::freeClassFileMemory()
{
  freeFields(class_file->fields, class_file->fields_count);
  freeMethods(class_file->methods, class_file->methods_count);
  freeAttributes(class_file->attributes, class_file->attributes_count);
  freeConstantPool(class_file->constant_pool, class_file->constant_pool_count);
}

void MemoryCleaner::freeConstantPool(cp_info **constant_pool, u2 constant_pool_count)
{
  for (int i = 0; i < constant_pool_count - 1; i++)
  {
    freeConstantPoolInfo(constant_pool[i]);

    if (constant_pool[i]->tag == CONSTANT_Double)
      i++;
  }

  free(constant_pool);
}

void MemoryCleaner::freeConstantPoolInfo(cp_info *constant_pool_entry)
{
  switch (constant_pool_entry->tag)
  {
  case CONSTANT_Class:
    free(constant_pool_entry->info.class_info);
    break;
  case CONSTANT_Fieldref:
    free(constant_pool_entry->info.fieldref_info);
    break;
  case CONSTANT_Methodref:
    free(constant_pool_entry->info.methodref_info);
    break;
  case CONSTANT_InterfaceMethodref:
    free(constant_pool_entry->info.interfaceMethodref_info);
    break;
  case CONSTANT_String:
    free(constant_pool_entry->info.string_info);
    break;
  case CONSTANT_Integer:
    free(constant_pool_entry->info.integer_info);
    break;
  case CONSTANT_Float:
    free(constant_pool_entry->info.float_info);
    break;
  case CONSTANT_Long:
    free(constant_pool_entry->info.long_info);
    break;
  case CONSTANT_Double:
    free(constant_pool_entry->info.double_info);
    break;
  case CONSTANT_NameAndType:
    free(constant_pool_entry->info.nameAndType_info);
    break;
  case CONSTANT_Utf8:
    free(constant_pool_entry->info.utf8_info->bytes);
    free(constant_pool_entry->info.utf8_info);
    break;
  case CONSTANT_MethodHandle:
    free(constant_pool_entry->info.methodHandle_info);
    break;
  case CONSTANT_MethodType:
    free(constant_pool_entry->info.methodType_info);
    break;
  case CONSTANT_InvokeDynamic:
    free(constant_pool_entry->info.invokeDynamic_info);
    break;
  default:
    break;
  }

  free(constant_pool_entry);
}

void MemoryCleaner::freeAttributes(attribute_info **attributes, u2 attributes_count)
{
  for (int i = 0; i < attributes_count; i++)
  {
    freeAttributeInfoByIndex(attributes[i]);
  }

  free(attributes);
}

void MemoryCleaner::freeAttributeInfoByIndex(attribute_info *attribute)
{
  std::string attribute_name = AttributeUtils::getAttributeType(class_file->constant_pool, attribute->attribute_name_index);

  if (attribute_name == CONSTANT_VALUE)
  {
    free(attribute->attribute.constantvalue_attribute);
  }
  else if (attribute_name == CODE)
  {
    freeCodeAttribute(attribute->attribute.code_attribute);
  }
  else if (attribute_name == EXCEPTIONS)
  {
    freeExceptionsAttribute(attribute->attribute.exceptions_attribute);
  }
  else if (attribute_name == INNER_CLASSES)
  {
    freeInnerClassesAttribute(attribute->attribute.innerclasses_attribute);
  }
  else if (attribute_name == SOURCE_FILE)
  {
    free(attribute->attribute.sourcefile_attribute);
  }
  else if (attribute_name == DEPRECATED)
  {
    free(attribute->attribute.deprecated_attribute);
  }
  else if (attribute_name == SYNTHETIC)
  {
    free(attribute->attribute.synthetic_attribute);
  }
  else if (attribute_name == LINE_NUMBER_TABLE)
  {
    freeLineNumberTableAttribute(attribute->attribute.linenumbertable_attribute);
  }
  else if (attribute_name == LOCAL_VARIABLE_TABLE)
  {
    freeLocalVariableTableAttribute(attribute->attribute.localvariabletable_attribute);
  }

  free(attribute);
}

void MemoryCleaner::freeCodeAttribute(Code_attribute *code_attribute)
{
  free(code_attribute->code);

  for (int i = 0; i < code_attribute->exception_table_length; i++)
  {
    free(code_attribute->exception_table[i]);
  }

  free(code_attribute->exception_table);

  freeAttributes(code_attribute->attributes, code_attribute->attributes_count);
  free(code_attribute->attributes);

  free(code_attribute);
}

void MemoryCleaner::freeExceptionsAttribute(Exceptions_attribute *exceptions_attribute)
{
  free(exceptions_attribute->exception_index_table);

  free(exceptions_attribute);
}

void MemoryCleaner::freeInnerClassesAttribute(InnerClasses_attribute *innerclasses_attribute)
{
  for (int i = 0; i < innerclasses_attribute->number_of_classes; i++)
  {
    free(innerclasses_attribute->classes[i]);
  }

  free(innerclasses_attribute->classes);

  free(innerclasses_attribute);
}

void MemoryCleaner::freeLineNumberTableAttribute(LineNumberTable_attribute *linenumbertable_attribute)
{
  for (int i = 0; i < linenumbertable_attribute->line_number_table_length; i++)
  {
    free(linenumbertable_attribute->line_number_table[i]);
  }

  free(linenumbertable_attribute->line_number_table);

  free(linenumbertable_attribute);
}

void MemoryCleaner::freeLocalVariableTableAttribute(LocalVariableTable_attribute *localvariabletable_attribute)
{
  for (int i = 0; i < localvariabletable_attribute->local_variable_table_length; i++)
  {
    free(localvariabletable_attribute->local_variable_table[i]);
  }

  free(localvariabletable_attribute->local_variable_table);

  free(localvariabletable_attribute);
}

void MemoryCleaner::freeMethods(method_info **methods, u2 methods_count)
{
  for (int i = 0; i < methods_count; i++)
  {
    freeMethodInfo(methods[i]);
  }

  free(methods);
}

void MemoryCleaner::freeMethodInfo(method_info *method)
{
  freeAttributes(method->attributes, method->attributes_count);

  free(method);
}

void MemoryCleaner::freeFields(field_info **fields, u2 fields_count)
{
  for (int i = 0; i < fields_count; i++)
  {
    freeFieldInfo(fields[i]);
  }

  free(fields);
}

void MemoryCleaner::freeFieldInfo(field_info *field)
{
  freeAttributes(field->attributes, field->attributes_count);

  free(field);
}