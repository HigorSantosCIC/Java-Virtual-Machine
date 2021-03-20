#ifndef CLASS_LOADER_HPP
#define CLASS_LOADER_HPP

#include <iostream>
#include "int_types.hpp"
#include "class_file.hpp"
#include "constant_pool.hpp"
#include <iostream>
#include <fstream>

class ClassLoader
{
public:
  FILE *fp;
  ClassFile *class_file;

  ClassLoader(const char *file_name);

  void readClassFile();

private:
  u1 readU1();
  u2 readU2();
  u4 readU4();

  CONSTANT_Class_info readConstantClassInfo();
  CONSTANT_Fieldref_info readConstantFieldrefInfo();
  CONSTANT_Methodref_info readConstantMethodrefInfo();
  CONSTANT_InterfaceMethodref_info readConstantInterfaceMethodrefInfo();
  CONSTANT_String_info readConstantStringInfo();
  CONSTANT_MethodHandle_info readConstantMethodHandleInfo();
  CONSTANT_NameAndType_info readConstantNameAndTypeInfo();
  CONSTANT_Utf8_info readConstantUtf8Info();
  CONSTANT_Float_info readConstantFloatInfo();
  CONSTANT_Integer_info readConstantIntegerInfo();
  CONSTANT_Long_info readConstantLongInfo();
  CONSTANT_Double_info readConstantDoubleInfo();
  CONSTANT_MethodType_info readConstantMethodTypeInfo();
  CONSTANT_InvokeDynamic_info readConstantInvokeDynamicInfo();

  cp_info *loadCpInfo();

  bool verifyMagic(u4 magic);
};

#endif