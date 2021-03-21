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

CONSTANT_Class_info ClassLoader::readConstantClassInfo()
{
  u2 name_index = readU2();

  CONSTANT_Class_info object = {.name_index = name_index};

  return object;
}

CONSTANT_Fieldref_info ClassLoader::readConstantFieldrefInfo()
{
  u2 class_index = readU2();
  u2 name_and_type_index = readU2();

  CONSTANT_Fieldref_info object = {.class_index = class_index, .name_and_type_index = name_and_type_index};

  return object;
}

CONSTANT_Methodref_info ClassLoader::readConstantMethodrefInfo()
{
  u2 class_index = readU2();
  u2 name_and_type_index = readU2();

  CONSTANT_Methodref_info object;
  object.class_index = class_index,
  object.name_and_type_index = name_and_type_index;

  return object;
}

CONSTANT_InterfaceMethodref_info ClassLoader::readConstantInterfaceMethodrefInfo()
{
  u2 class_index = readU2();
  u2 name_and_type_index = readU2();

  CONSTANT_InterfaceMethodref_info object = {
      .class_index = class_index,
      .name_and_type_index = name_and_type_index};

  return object;
}

CONSTANT_String_info ClassLoader::readConstantStringInfo()
{
  u2 string_index = readU2();

  CONSTANT_String_info object = {
      .string_index = string_index};

  return object;
}

CONSTANT_MethodHandle_info ClassLoader::readConstantMethodHandleInfo()
{
  u1 reference_kind = readU1();
  u2 reference_index = readU2();

  CONSTANT_MethodHandle_info object = {
      .reference_kind = reference_kind,
      .reference_index = reference_index};

  return object;
}

CONSTANT_NameAndType_info ClassLoader::readConstantNameAndTypeInfo()
{
  u2 name_index = readU2();
  u2 descriptor_index = readU2();

  CONSTANT_NameAndType_info object = {
      .name_index = name_index,
      .descriptor_index = descriptor_index};

  return object;
}

CONSTANT_Utf8_info ClassLoader::readConstantUtf8Info()
{
  u2 length = readU2();

  u1 *bytes = (u1 *)malloc(sizeof(u1) * length);

  for (int i = 0; i < length; i++)
  {
    bytes[i] = readU1();
  }

  CONSTANT_Utf8_info object = {
      .length = length,
      .bytes = bytes};

  return object;
}

CONSTANT_Float_info ClassLoader::readConstantFloatInfo()
{
  u4 bytes = readU4();
  CONSTANT_Float_info obj{
      .bytes = bytes};
  return obj;
}

CONSTANT_Integer_info ClassLoader::readConstantIntegerInfo()
{
  u4 bytes = readU4();

  CONSTANT_Integer_info object = {
      .bytes = bytes};

  return object;
}

CONSTANT_Long_info ClassLoader::readConstantLongInfo()
{
  u4 high_bytes = readU4();
  u4 low_bytes = readU4();

  CONSTANT_Long_info object = {
      .high_bytes = high_bytes,
      .low_bytes = low_bytes};

  return object;
}

CONSTANT_Double_info ClassLoader::readConstantDoubleInfo()
{
  u4 high_bytes = readU4();
  u4 low_bytes = readU4();

  CONSTANT_Double_info obj = {
      .high_bytes = high_bytes,
      .low_bytes = low_bytes};

  return obj;
}

CONSTANT_MethodType_info ClassLoader::readConstantMethodTypeInfo()
{
  u2 descriptor_index = readU2();

  CONSTANT_MethodType_info obj = {
      .descriptor_index = descriptor_index};

  return obj;
}

CONSTANT_InvokeDynamic_info ClassLoader::readConstantInvokeDynamicInfo()
{
  u2 bootstrap_method_attr_index = readU2();
  u2 name_and_type_index = readU2();

  CONSTANT_InvokeDynamic_info obj = {
      .bootstrap_method_attr_index = bootstrap_method_attr_index,
      .name_and_type_index = name_and_type_index};

  return obj;
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

  std::cout << "Attribute name: " << class_file->constant_pool[attribute_entry->attribute_name_index - 1]->info.utf8_info.bytes << std::endl;

  u1 *attribute_identifier = class_file->constant_pool[attribute_entry->attribute_name_index - 1]->info.utf8_info.bytes;

  // Cast attribute_identifier to char* in order to compare with constant strings
  char *attribute_name = (char *)attribute_identifier;
  if (strcmp(attribute_name, CONSTANT_VALUE) == 0)
  {
    attribute_entry->attribute.constantvalue_attribute = readConstantValueAttribute();
  }
  else if (strcmp(attribute_name, CODE) == 0)
  {
    attribute_entry->attribute.code_attribute = readCodeAttribute();
  }
  else if (strcmp(attribute_name, EXCEPTIONS) == 0)
  {
    attribute_entry->attribute.exceptions_attribute = readExceptionsAttribute();
  }
  else if (strcmp(attribute_name, INNER_CLASSES) == 0)
  {
    attribute_entry->attribute.innerclasses_attribute = readInnerClassesAttribute();
  }
  else if (strcmp(attribute_name, SOURCE_FILE) == 0)
  {
    attribute_entry->attribute.sourcefile_attribute = readSourceFileAttribute();
  }
  else if (strcmp(attribute_name, DEPRECATED) == 0)
  {
    attribute_entry->attribute.deprecated_attribute = readDeprecatedAttribute();
  }
  else if (strcmp(attribute_name, SYNTHETIC) == 0)
  {
    attribute_entry->attribute.synthetic_attribute = readSyntheticAttribute();
  }
  else if (strcmp(attribute_name, LINE_NUMBER_TABLE) == 0)
  {
    attribute_entry->attribute.linenumbertable_attribute = readLineNumberTableAttribute();
  }
  else if (strcmp(attribute_name, LOCAL_VARIABLE_TABLE) == 0)
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

  std::cout << "Method name: " << class_file->constant_pool[method_entry->name_index - 1]->info.utf8_info.bytes << std::endl;
  std::cout << "Method descriptor: " << class_file->constant_pool[method_entry->descriptor_index - 1]->info.utf8_info.bytes << std::endl;

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

  std::cout << std::hex << "Magic number: " << magic << std::endl;

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
    // std::cout << std::hex << "Tag cp_info: " << unsigned(constant_pool[i]->tag) << std::endl;
    if (constant_pool[i]->tag == CONSTANT_Double)
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
    // std::cout << "Interfaces[" << i << "]: " << interfaces << std::endl;
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

  for (int i = 0; i < methods_count; i++)
  {
    attributes[i] = readAttributeInfo();
  }

  class_file->attributes = attributes;

  std::cout << std::hex << "Minor version: " << minor_version << std::endl;
  std::cout << std::hex << "Major version: " << major_version << std::endl;
  std::cout << std::hex << "Constant pool count: " << constant_pool_count << std::endl;
  std::cout << "Access flags: " << access_flags << std::endl;
  std::cout << "This class: " << this_class << std::endl;
  std::cout << "Super class: " << super_class << std::endl;
  std::cout << "Interfaces count: " << interfaces_count << std::endl;
  std::cout << "Fields count: " << fields_count << std::endl;
  std::cout << "Methods count: " << methods_count << std::endl;
  std::cout << "Attribute count: " << attributes_count << std::endl;
  
  //TODO: Exibidor
  //exemplo: exibidor.set(leitor.get())

}
