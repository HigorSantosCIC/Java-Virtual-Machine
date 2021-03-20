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

cp_info *ClassLoader::loadCpInfo()
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
    constant_pool[i] = loadCpInfo();
    // std::cout << std::hex << "Tag cp_info: " << unsigned(constant_pool[i]->tag) << std::endl;
    if (constant_pool[i]->tag == CONSTANT_Double)
      i++;
  }

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

  u2 fields_count = readU2();
  class_file->fields_count = fields_count;

  std::cout << std::hex << "Minor version: " << minor_version << std::endl;
  std::cout << std::hex << "Major version: " << major_version << std::endl;
  std::cout << std::hex << "Constant pool count: " << constant_pool_count << std::endl;
  std::cout << "Access flags: " << access_flags << std::endl;
  std::cout << "This class: " << this_class << std::endl;
  std::cout << "Super class: " << super_class << std::endl;
  std::cout << "Interfaces count: " << interfaces_count << std::endl;
  std::cout << "Fields count: " << fields_count << std::endl;
}
