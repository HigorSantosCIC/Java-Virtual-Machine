#include "class_loader.hpp"
ClassLoader::ClassLoader(const char *file_name)
{
  fp = fopen(file_name, "r");
  class_file = (ClassFile *)malloc(sizeof(ClassFile));
}

bool ClassLoader::verifyMagic(u4 magic)
{
  return magic == 0xCAFEBABE;
}

u1 ClassLoader::readU1()
{
  u1 content = 0;

  fread(&content, sizeof(u1), 1, fp);

  return content;
}

u2 ClassLoader::readU2()
{
  u2 content = 0;

  // Shift bytes, as C++ stores bytes in little endian order
  for (int i = 0; i < 2; i++)
  {
    content += readU1() << (8 - 8 * i);
  }

  return content;
}

u4 ClassLoader::readU4()
{
  u4 content = 0;

  // Shift bytes, as C++ stores bytes in little endian order
  for (int i = 0; i < 4; i++)
  {
    content += readU1() << (24 - 8 * i);
  }

  return content;
}

CONSTANT_Class_info *ClassLoader::readConstantClassInfo()
{
  CONSTANT_Class_info *object = (CONSTANT_Class_info *)malloc(sizeof(CONSTANT_Class_info));

  object->name_index = readU2();

  return object;
}

CONSTANT_Fieldref_info *ClassLoader::readConstantFieldrefInfo()
{
  CONSTANT_Fieldref_info *object = (CONSTANT_Fieldref_info *)malloc(sizeof(CONSTANT_Fieldref_info));

  object->class_index = readU2();
  object->name_and_type_index = readU2();

  return object;
}

CONSTANT_Methodref_info *ClassLoader::readConstantMethodrefInfo()
{
  CONSTANT_Methodref_info *object = (CONSTANT_Methodref_info *)malloc(sizeof(CONSTANT_Methodref_info));

  object->class_index = readU2();
  object->name_and_type_index = readU2();

  return object;
}

CONSTANT_InterfaceMethodref_info *ClassLoader::readConstantInterfaceMethodrefInfo()
{
  CONSTANT_InterfaceMethodref_info *object = (CONSTANT_InterfaceMethodref_info *)malloc(sizeof(CONSTANT_InterfaceMethodref_info));

  object->class_index = readU2();
  object->name_and_type_index = readU2();

  return object;
}

CONSTANT_String_info *ClassLoader::readConstantStringInfo()
{
  CONSTANT_String_info *object = (CONSTANT_String_info *)malloc(sizeof(CONSTANT_String_info));

  object->string_index = readU2();

  return object;
}

CONSTANT_MethodHandle_info *ClassLoader::readConstantMethodHandleInfo()
{
  CONSTANT_MethodHandle_info *object = (CONSTANT_MethodHandle_info *)malloc(sizeof(CONSTANT_MethodHandle_info));

  object->reference_kind = readU1();
  object->reference_index = readU2();

  return object;
}

CONSTANT_NameAndType_info *ClassLoader::readConstantNameAndTypeInfo()
{
  CONSTANT_NameAndType_info *object = (CONSTANT_NameAndType_info *)malloc(sizeof(CONSTANT_NameAndType_info));

  object->name_index = readU2();
  object->descriptor_index = readU2();

  return object;
}

CONSTANT_Utf8_info *ClassLoader::readConstantUtf8Info()
{
  CONSTANT_Utf8_info *object = (CONSTANT_Utf8_info *)malloc(sizeof(CONSTANT_Utf8_info));

  object->length = readU2();

  u1 *bytes = (u1 *)malloc(sizeof(u1) * object->length);

  for (int i = 0; i < object->length; i++)
  {
    bytes[i] = readU1();
  }

  object->bytes = bytes;

  return object;
}

CONSTANT_Float_info *ClassLoader::readConstantFloatInfo()
{
  CONSTANT_Float_info *object = (CONSTANT_Float_info *)malloc(sizeof(CONSTANT_Float_info));

  object->bytes = readU4();

  return object;
}

CONSTANT_Integer_info *ClassLoader::readConstantIntegerInfo()
{
  CONSTANT_Integer_info *object = (CONSTANT_Integer_info *)malloc(sizeof(CONSTANT_Integer_info));

  object->bytes = readU4();

  return object;
}

CONSTANT_Long_info *ClassLoader::readConstantLongInfo()
{
  CONSTANT_Long_info *object = (CONSTANT_Long_info *)malloc(sizeof(CONSTANT_Long_info));

  object->high_bytes = readU4();
  object->low_bytes = readU4();

  return object;
}

CONSTANT_Double_info *ClassLoader::readConstantDoubleInfo()
{
  CONSTANT_Double_info *object = (CONSTANT_Double_info *)malloc(sizeof(CONSTANT_Double_info));

  object->high_bytes = readU4();
  object->low_bytes = readU4();

  return object;
}

CONSTANT_MethodType_info *ClassLoader::readConstantMethodTypeInfo()
{
  CONSTANT_MethodType_info *object = (CONSTANT_MethodType_info *)malloc(sizeof(CONSTANT_MethodType_info));

  object->descriptor_index = readU2();

  return object;
}

CONSTANT_InvokeDynamic_info *ClassLoader::readConstantInvokeDynamicInfo()
{
  CONSTANT_InvokeDynamic_info *object = (CONSTANT_InvokeDynamic_info *)malloc(sizeof(CONSTANT_InvokeDynamic_info));

  object->bootstrap_method_attr_index = readU2();
  object->name_and_type_index = readU2();

  return object;
}

cp_info *ClassLoader::readCpInfo()
{
  cp_info *constant_pool_entry = (cp_info *)malloc(sizeof(cp_info));

  constant_pool_entry->tag = readU1();

  switch (constant_pool_entry->tag)
  {
  case CONSTANT_Class:
    constant_pool_entry->info.class_info = readConstantClassInfo();
    break;
  case CONSTANT_Fieldref:
    constant_pool_entry->info.fieldref_info = readConstantFieldrefInfo();
    break;
  case CONSTANT_Methodref:
    constant_pool_entry->info.methodref_info = readConstantMethodrefInfo();
    break;
  case CONSTANT_InterfaceMethodref:
    constant_pool_entry->info.interfaceMethodref_info = readConstantInterfaceMethodrefInfo();
    break;
  case CONSTANT_String:
    constant_pool_entry->info.string_info = readConstantStringInfo();
    break;
  case CONSTANT_Integer:
    constant_pool_entry->info.integer_info = readConstantIntegerInfo();
    break;
  case CONSTANT_Float:
    constant_pool_entry->info.float_info = readConstantFloatInfo();
    break;
  case CONSTANT_Long:
    constant_pool_entry->info.long_info = readConstantLongInfo();
    break;
  case CONSTANT_Double:
    constant_pool_entry->info.double_info = readConstantDoubleInfo();
    break;
  case CONSTANT_NameAndType:
    constant_pool_entry->info.nameAndType_info = readConstantNameAndTypeInfo();
    break;
  case CONSTANT_Utf8:
    constant_pool_entry->info.utf8_info = readConstantUtf8Info();
    break;
  case CONSTANT_MethodHandle:
    constant_pool_entry->info.methodHandle_info = readConstantMethodHandleInfo();
    break;
  case CONSTANT_MethodType:
    constant_pool_entry->info.methodType_info = readConstantMethodTypeInfo();
    break;
  case CONSTANT_InvokeDynamic:
    constant_pool_entry->info.invokeDynamic_info = readConstantInvokeDynamicInfo();
    break;

  default:
    std::cout << "INVALID CONSTANT VALUE: " << unsigned(constant_pool_entry->tag) << std::endl;
    return NULL;
  }

  return constant_pool_entry;
}

field_info *ClassLoader::readFieldInfo()
{
  field_info *field_entry = (field_info *)malloc(sizeof(field_info));

  field_entry->access_flags = readU2();
  field_entry->name_index = readU2();
  field_entry->descriptor_index = readU2();
  field_entry->attributes_count = readU2();

  attribute_info **attributes = (attribute_info **)malloc(sizeof(attribute_info *) * field_entry->attributes_count);

  for (int i = 0; i < field_entry->attributes_count; i++)
  {
    attributes[i] = readAttributeInfo();
  }

  field_entry->attributes = attributes;

  return field_entry;
}

attribute_info *ClassLoader::readAttributeInfo()
{
  attribute_info *attribute_entry = (attribute_info *)malloc(sizeof(attribute_info));

  attribute_entry->attribute_name_index = readU2();
  attribute_entry->attribute_length = readU4();

  std::string attribute_name = AttributeUtils::getAttributeType(class_file->constant_pool, attribute_entry->attribute_name_index);

  if (attribute_name == CONSTANT_VALUE)
  {
    attribute_entry->attribute.constantvalue_attribute = readConstantValueAttribute();
  }
  else if (attribute_name == CODE)
  {
    attribute_entry->attribute.code_attribute = readCodeAttribute();
  }
  else if (attribute_name == EXCEPTIONS)
  {
    attribute_entry->attribute.exceptions_attribute = readExceptionsAttribute();
  }
  else if (attribute_name == INNER_CLASSES)
  {
    attribute_entry->attribute.innerclasses_attribute = readInnerClassesAttribute();
  }
  else if (attribute_name == SOURCE_FILE)
  {
    attribute_entry->attribute.sourcefile_attribute = readSourceFileAttribute();
  }
  else if (attribute_name == DEPRECATED)
  {
    attribute_entry->attribute.deprecated_attribute = readDeprecatedAttribute();
  }
  else if (attribute_name == SYNTHETIC)
  {
    attribute_entry->attribute.synthetic_attribute = readSyntheticAttribute();
  }
  else if (attribute_name == LINE_NUMBER_TABLE)
  {
    attribute_entry->attribute.linenumbertable_attribute = readLineNumberTableAttribute();
  }
  else if (attribute_name == LOCAL_VARIABLE_TABLE)
  {
    attribute_entry->attribute.localvariabletable_attribute = readLocalVariableTableAttribute();
  }

  return attribute_entry;
}

ConstantValue_attribute *ClassLoader::readConstantValueAttribute()
{
  ConstantValue_attribute *obj = (ConstantValue_attribute *)malloc(sizeof(ConstantValue_attribute));

  obj->constantvalue_index = readU2();

  return obj;
}

Code_attribute *ClassLoader::readCodeAttribute()
{
  Code_attribute *obj = (Code_attribute *)malloc(sizeof(Code_attribute));

  obj->max_stack = readU2();
  obj->max_locals = readU2();
  obj->code_length = readU4();

  u1 *code = (u1 *)malloc(sizeof(u1) * obj->code_length);

  for (int i = 0; i < (int)obj->code_length; i++)
  {
    code[i] = readU1();
  }

  obj->code = code;
  obj->exception_table_length = readU2();

  exception_table_info **exception_table = (exception_table_info **)malloc(sizeof(exception_table_info *) * obj->exception_table_length);

  for (int i = 0; i < obj->exception_table_length; i++)
  {
    exception_table[i] = readExceptionTableInfo();
  }

  obj->exception_table = exception_table;
  obj->attributes_count = readU2();

  attribute_info **attributes = (attribute_info **)malloc(sizeof(attribute_info *) * obj->attributes_count);

  for (int i = 0; i < obj->attributes_count; i++)
  {
    attributes[i] = readAttributeInfo();
  }

  obj->attributes = attributes;

  return obj;
}

exception_table_info *ClassLoader::readExceptionTableInfo()
{
  exception_table_info *exception_table = (exception_table_info *)malloc(sizeof(exception_table_info));

  exception_table->start_pc = readU2();
  exception_table->end_pc = readU2();
  exception_table->handler_pc = readU2();
  exception_table->catch_type = readU2();

  return exception_table;
}

Exceptions_attribute *ClassLoader::readExceptionsAttribute()
{
  Exceptions_attribute *obj = (Exceptions_attribute *)malloc(sizeof(Exceptions_attribute));

  obj->number_of_exceptions = readU2();

  u2 *exception_index_table = (u2 *)malloc(sizeof(u2) * obj->number_of_exceptions);

  for (int i = 0; i < obj->number_of_exceptions; i++)
  {
    exception_index_table[i] = readU2();
  }

  obj->exception_index_table = exception_index_table;

  return obj;
}

InnerClasses_attribute *ClassLoader::readInnerClassesAttribute()
{

  InnerClasses_attribute *obj = (InnerClasses_attribute *)malloc(sizeof(InnerClasses_attribute));

  obj->number_of_classes = readU2();

  classes_info **classes = (classes_info **)malloc(sizeof(classes_info *) * obj->number_of_classes);

  for (int i = 0; i < obj->number_of_classes; i++)
  {
    classes[i] = readClassesInfo();
  }

  obj->classes = classes;

  return obj;
}

classes_info *ClassLoader::readClassesInfo()
{
  classes_info *classes_table = (classes_info *)malloc(sizeof(classes_info));

  classes_table->inner_class_info_index = readU2();
  classes_table->outer_class_info_index = readU2();
  classes_table->inner_name_index = readU2();
  classes_table->inner_class_access_flags = readU2();

  return classes_table;
}

SourceFile_attribute *ClassLoader::readSourceFileAttribute()
{
  SourceFile_attribute *obj = (SourceFile_attribute *)malloc(sizeof(SourceFile_attribute));

  obj->sourcefile_index = readU2();

  return obj;
}

Deprecated_attribute *ClassLoader::readDeprecatedAttribute()
{
  Deprecated_attribute *obj = (Deprecated_attribute *)malloc(sizeof(Deprecated_attribute));

  return obj;
}

Synthetic_attribute *ClassLoader::readSyntheticAttribute()
{
  Synthetic_attribute *obj = (Synthetic_attribute *)malloc(sizeof(Synthetic_attribute));

  return obj;
}

LineNumberTable_attribute *ClassLoader::readLineNumberTableAttribute()
{
  LineNumberTable_attribute *obj = (LineNumberTable_attribute *)malloc(sizeof(LineNumberTable_attribute));

  obj->line_number_table_length = readU2();

  line_number_table_info **line_number_table = (line_number_table_info **)malloc(sizeof(line_number_table_info *) * obj->line_number_table_length);

  for (int i = 0; i < obj->line_number_table_length; i++)
  {
    line_number_table[i] = readLineNumberTable();
  }

  obj->line_number_table = line_number_table;

  return obj;
}

line_number_table_info *ClassLoader::readLineNumberTable()
{
  line_number_table_info *line_number_table = (line_number_table_info *)malloc(sizeof(line_number_table_info));

  line_number_table->start_pc = readU2();
  line_number_table->line_number = readU2();

  return line_number_table;
}

LocalVariableTable_attribute *ClassLoader::readLocalVariableTableAttribute()
{
  LocalVariableTable_attribute *obj = (LocalVariableTable_attribute *)malloc(sizeof(LocalVariableTable_attribute));

  obj->local_variable_table_length = readU2();

  local_variable_table_info **local_variable_table = (local_variable_table_info **)malloc(sizeof(local_variable_table_info *) * obj->local_variable_table_length);

  for (int i = 0; i < obj->local_variable_table_length; i++)
  {
    local_variable_table[i] = readLocalVariableTable();
  }

  obj->local_variable_table = local_variable_table;

  return obj;
}

local_variable_table_info *ClassLoader::readLocalVariableTable()
{
  local_variable_table_info *local_variable_table = (local_variable_table_info *)malloc(sizeof(local_variable_table_info));

  local_variable_table->start_pc = readU2();
  local_variable_table->length = readU2();
  local_variable_table->name_index = readU2();
  local_variable_table->descriptor_index = readU2();
  local_variable_table->index = readU2();

  return local_variable_table;
}

method_info *ClassLoader::readMethodInfo()
{
  method_info *method_entry = (method_info *)malloc(sizeof(method_info));

  method_entry->access_flags = readU2();
  method_entry->name_index = readU2();
  method_entry->descriptor_index = readU2();
  method_entry->attributes_count = readU2();

  attribute_info **attributes = (attribute_info **)malloc(sizeof(attribute_info *) * method_entry->attributes_count);

  for (int i = 0; i < method_entry->attributes_count; i++)
  {
    attributes[i] = readAttributeInfo();
  }

  method_entry->attributes = attributes;

  return method_entry;
}

void ClassLoader::readClassFile()
{
  u4 magic = readU4();

  if (!verifyMagic(magic))
    //TODO: return error
    return;

  class_file->magic = magic;

  u2 minor_version = readU2();
  class_file->minor_version = minor_version;

  u2 major_version = readU2();
  class_file->major_version = major_version;

  //TODO: Validate version number

  u2 constant_pool_count = readU2();
  class_file->constant_pool_count = constant_pool_count;

  cp_info **constant_pool = (cp_info **)malloc(sizeof(cp_info *) * constant_pool_count);

  for (int i = 0; i < constant_pool_count - 1; i++)
  {
    constant_pool[i] = readCpInfo();

    if (constant_pool[i]->tag == CONSTANT_Double || constant_pool[i]->tag == CONSTANT_Long)
      i++;
  }

  class_file->constant_pool = constant_pool;

  u2 access_flags = readU2();
  class_file->access_flags = access_flags;

  u2 this_class = readU2();
  class_file->this_class = this_class;

  u2 super_class = readU2();
  class_file->super_class = super_class;

  u2 interfaces_count = readU2();
  class_file->interfaces_count = interfaces_count;

  u2 *interfaces = (u2 *)malloc(sizeof(u2) * interfaces_count);

  for (int i = 0; i < interfaces_count; i++)
  {
    interfaces[i] = readU2();
  }

  class_file->interfaces = interfaces;

  u2 fields_count = readU2();
  class_file->fields_count = fields_count;

  field_info **fields = (field_info **)malloc(sizeof(field_info *) * fields_count);

  for (int i = 0; i < fields_count; i++)
  {
    fields[i] = readFieldInfo();
  }

  class_file->fields = fields;

  u2 methods_count = readU2();
  class_file->methods_count = methods_count;

  method_info **methods = (method_info **)malloc(sizeof(method_info *) * methods_count);

  for (int i = 0; i < methods_count; i++)
  {
    methods[i] = readMethodInfo();
  }

  class_file->methods = methods;

  u2 attributes_count = readU2();
  class_file->attributes_count = attributes_count;

  attribute_info **attributes = (attribute_info **)malloc(sizeof(attribute_info *) * attributes_count);

  for (int i = 0; i < attributes_count; i++)
  {
    attributes[i] = readAttributeInfo();
  }

  class_file->attributes = attributes;
}

ClassFile *ClassLoader::getClassFile()
{
  return class_file;
}