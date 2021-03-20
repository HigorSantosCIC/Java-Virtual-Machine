#include "int_types.h"
#include "class_file.h"
#include "constant_pool.h"
#include <iostream>
#include <fstream>

/*
  CONSTANT_Class = 7,-- RAPHAEL
  CONSTANT_Fieldref = 9, -- RAPHAEL
  CONSTANT_Methodref = 10, -- RAPHAEL
  CONSTANT_InterfaceMethodref = 11, 
  CONSTANT_String = 8, -- RAPHAEL
  CONSTANT_Integer = 3, - DALLE
  CONSTANT_Long = 5, - DALLE
  
  CONSTANT_NameAndType = 12, - HIGOR
  CONSTANT_Utf8 = 1, - HIGOR
  CONSTANT_MethodHandle = 15, - HIGOR
  CONSTANT_MethodType = 16, - MARANHA
  CONSTANT_InvokeDynamic = 18, - MARANHA
*/

bool verifyMagic(u4 magic)
{
  return magic == 0xCAFEBABE;
}

u1 readU1(FILE *fp)
{
  u1 content = 0;

  fread(&content, sizeof(u1), 1, fp);

  return content;
}

u2 readU2(FILE *fp)
{
  u2 content = 0;

  // Shift bytes, as C++ stores bytes in little endian order
  for (int i = 0; i < 2; i++)
  {
    content += readU1(fp) << (8 - 8 * i);
  }

  return content;
}

u4 readU4(FILE *fp)
{
  u4 content = 0;

  // Shift bytes, as C++ stores bytes in little endian order
  for (int i = 0; i < 4; i++)
  {
    content += readU1(fp) << (24 - 8 * i);
  }

  return content;
}

CONSTANT_Class_info readConstantClassInfo(FILE *fp)
{
  u2 name_index = readU2(fp);

  CONSTANT_Class_info object = {.name_index = name_index};

  return object;
}

CONSTANT_Fieldref_info readConstantFieldrefInfo(FILE *fp)
{
  u2 class_index = readU2(fp);
  u2 name_and_type_index = readU2(fp);

  CONSTANT_Fieldref_info object = {.class_index = class_index, .name_and_type_index = name_and_type_index};

  return object;
}

CONSTANT_Methodref_info readConstantMethodrefInfo(FILE *fp)
{
  u2 class_index = readU2(fp);
  u2 name_and_type_index = readU2(fp);

  CONSTANT_Methodref_info object;
  object.class_index = class_index,
  object.name_and_type_index = name_and_type_index;

  return object;
}

CONSTANT_InterfaceMethodref_info readConstantInterfaceMethodrefInfo(FILE *fp)
{
  u2 class_index = readU2(fp);
  u2 name_and_type_index = readU2(fp);

  CONSTANT_InterfaceMethodref_info object = {
      .class_index = class_index,
      .name_and_type_index = name_and_type_index};

  return object;
}

CONSTANT_String_info readConstantStringInfo(FILE *fp)
{
  u2 string_index = readU2(fp);

  CONSTANT_String_info object = {
      .string_index = string_index};

  return object;
}

// Função MethodHandle

CONSTANT_MethodHandle_info readConstantMethodHandleInfo(FILE *fp)
{
  u1 reference_kind = readU1(fp);
  u2 reference_index = readU2(fp);

  CONSTANT_MethodHandle_info object = {
      .reference_kind = reference_kind,
      .reference_index = reference_index};

  return object;
}

// Função CONSTANT_NameAndType_info;

CONSTANT_NameAndType_info readConstantNameAndTypeInfo(FILE *fp)
{
  u2 name_index = readU2(fp);
  u2 descriptor_index = readU2(fp);

  CONSTANT_NameAndType_info object = {
      .name_index = name_index,
      .descriptor_index = descriptor_index};

  return object;
}

// Função CONSTANT_Utf8_info

CONSTANT_Utf8_info readConstantUtf8Info(FILE *fp)
{
  u2 length = readU2(fp);

  u1 *bytes = (u1 *)malloc(sizeof(u1) * length);

  for (int i = 0; i < length; i++)
  {
    bytes[i] = readU1(fp);
  }

  CONSTANT_Utf8_info object = {
      .length = length,
      .bytes = bytes};

  return object;
}

CONSTANT_Float_info readConstantFloatInfo(FILE *fp)
{
  u4 bytes = readU4(fp);
  CONSTANT_Float_info obj{
      .bytes = bytes};
  return obj;
}

CONSTANT_Integer_info readConstantIntegerInfo(FILE *fp)
{
  u4 bytes = readU4(fp);

  CONSTANT_Integer_info object = {
      .bytes = bytes};

  return object;
}

CONSTANT_Long_info readConstantLongInfo(FILE *fp)
{
  u4 high_bytes = readU4(fp);
  u4 low_bytes = readU4(fp);

  CONSTANT_Long_info object = {
      .high_bytes = high_bytes,
      .low_bytes = low_bytes};

  return object;
}

CONSTANT_Double_info readConstantDoubleInfo(FILE *fp)
{
  u4 high_bytes = readU4(fp);
  u4 low_bytes = readU4(fp);

  CONSTANT_Double_info obj = {
      .high_bytes = high_bytes,
      .low_bytes = low_bytes};

  return obj;
}

CONSTANT_MethodType_info readConstantMethodTypeInfo(FILE *fp)
{
  u2 descriptor_index = readU2(fp);

  CONSTANT_MethodType_info obj = {
      .descriptor_index = descriptor_index};

  return obj;
}

CONSTANT_InvokeDynamic_info readConstantInvokeDynamicInfo(FILE *fp)
{
  u2 bootstrap_method_attr_index = readU2(fp);
  u2 name_and_type_index = readU2(fp);

  CONSTANT_InvokeDynamic_info obj = {
      .bootstrap_method_attr_index = bootstrap_method_attr_index,
      .name_and_type_index = name_and_type_index};
  return obj;
}

cp_info *loadCpInfo(FILE *fp)
{
  cp_info *constant_pool_entry = (cp_info *)malloc(sizeof(cp_info));

  constant_pool_entry->tag = readU1(fp);

  switch (constant_pool_entry->tag)
  {
  case CONSTANT_Class:
    constant_pool_entry->info.class_info = readConstantClassInfo(fp);
    break;
  case CONSTANT_Fieldref:
    constant_pool_entry->info.fieldref_info = readConstantFieldrefInfo(fp);
    break;
  case CONSTANT_Methodref:
    constant_pool_entry->info.methodref_info = readConstantMethodrefInfo(fp);
    break;
  case CONSTANT_InterfaceMethodref:
    constant_pool_entry->info.interfaceMethodref_info = readConstantInterfaceMethodrefInfo(fp);
    break;
  case CONSTANT_String:
    constant_pool_entry->info.string_info = readConstantStringInfo(fp);
    break;
  case CONSTANT_Integer:
    constant_pool_entry->info.integer_info = readConstantIntegerInfo(fp);
    break;
  case CONSTANT_Float:
    constant_pool_entry->info.float_info = readConstantFloatInfo(fp);
    break;
  case CONSTANT_Long:
    constant_pool_entry->info.long_info = readConstantLongInfo(fp);
    break;
  case CONSTANT_Double:
    constant_pool_entry->info.double_info = readConstantDoubleInfo(fp);
    break;
  case CONSTANT_NameAndType:
    constant_pool_entry->info.nameAndType_info = readConstantNameAndTypeInfo(fp);
    break;
  case CONSTANT_Utf8:
    constant_pool_entry->info.utf8_info = readConstantUtf8Info(fp);
    break;
  case CONSTANT_MethodHandle:
    constant_pool_entry->info.methodHandle_info = readConstantMethodHandleInfo(fp);
    break;
  case CONSTANT_MethodType:
    constant_pool_entry->info.methodType_info = readConstantMethodTypeInfo(fp);
    break;
  case CONSTANT_InvokeDynamic:
    constant_pool_entry->info.invokeDynamic_info = readConstantInvokeDynamicInfo(fp);
    break;

  default:

    std::cout << "INVALID CONSTANT VALUE: " << unsigned(constant_pool_entry->tag) << std::endl;
    return NULL;
  }

  return constant_pool_entry;
}

void readClassFile(FILE *fp)
{
  ClassFile *class_file = (ClassFile *)malloc(sizeof(ClassFile));

  u4 magic = readU4(fp);

  std::cout << std::hex << "Magic number: " << magic << std::endl;

  if (!verifyMagic(magic))
    //TODO: return error
    return;

  class_file->magic = magic;

  u2 minor_version = readU2(fp);
  class_file->minor_version = minor_version;

  u2 major_version = readU2(fp);
  class_file->major_version = major_version;

  //TODO: Validate version number

  u2 constant_pool_count = readU2(fp);
  class_file->constant_pool_count = constant_pool_count;

  cp_info **constant_pool = (cp_info **)malloc(sizeof(cp_info *) * constant_pool_count);

  for (int i = 0; i < constant_pool_count - 1; i++)
  {
    constant_pool[i] = loadCpInfo(fp);
    // std::cout << std::hex << "Tag cp_info: " << unsigned(constant_pool[i]->tag) << std::endl;
    if (constant_pool[i]->tag == CONSTANT_Double)
      i++;
  }

  u2 access_flags = readU2(fp);
  class_file->access_flags = access_flags;

  u2 this_class = readU2(fp);
  class_file->this_class = this_class;

  u2 super_class = readU2(fp);
  class_file->super_class = super_class;

  u2 interfaces_count = readU2(fp);
  class_file->interfaces_count = interfaces_count;

  u2 *interfaces = (u2 *)malloc(sizeof(u2) * interfaces_count);

  for (int i = 0; i < interfaces_count; i++)
  {
    interfaces[i] = readU2(fp);
    // std::cout << "Interfaces[" << i << "]: " << interfaces << std::endl;
  }

  u2 fields_count = readU2(fp);
  class_file->fields_count = fields_count;

  // Printer
  std::cout << std::hex << "Minor version: " << minor_version << std::endl;
  std::cout << std::hex << "Major version: " << major_version << std::endl;
  std::cout << std::hex << "Constant pool count: " << constant_pool_count << std::endl;
  std::cout << "Access flags: " << access_flags << std::endl;
  std::cout << "This class: " << this_class << std::endl;
  std::cout << "Super class: " << super_class << std::endl;
  std::cout << "Interfaces count: " << interfaces_count << std::endl;
  std::cout << "Fields count: " << fields_count << std::endl;
}
