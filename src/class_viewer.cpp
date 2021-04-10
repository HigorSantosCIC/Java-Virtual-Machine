#include "class_viewer.hpp"
#include <algorithm>

std::string getInstructionNameByOpcode(u1 opcode)
{
  switch (opcode)
  {
  case (0x00):
    return "nop";

  case (0x01):
    return "aconst_null";

  case (0x02):
    return "iconst_m1";

  case (0x03):
    return "iconst_0";

  case (0x04):
    return "iconst_1";

  case (0x05):
    return "iconst_2";

  case (0x06):
    return "iconst_3";

  case (0x07):
    return "iconst_4";

  case (0x08):
    return "iconst_5";

  case (0x09):
    return "lconst_0";

  case (0x0a):
    return "lconst_1";

  case (0x0b):
    return "fconst_0";

  case (0x0c):
    return "fconst_1";

  case (0x0d):
    return "fconst_2";

  case (0x0e):
    return "dconst_0";

  case (0x0f):
    return "dconst_1";

  case (0x10):
    return "bipush";

  case (0x11):
    return "sipush";

  case (0x12):
    return "ldc";

  case (0x13):
    return "ldc_w";

  case (0x14):
    return "ldc2_w";

  case (0x15):
    return "iload";

  case (0x16):
    return "lload";

  case (0x17):
    return "fload";

  case (0x18):
    return "dload";

  case (0x19):
    return "aload";

  case (0x1a):
    return "iload_0";

  case (0x1b):
    return "iload_1";

  case (0x1c):
    return "iload_2";

  case (0x1d):
    return "iload_3";

  case (0x1e):
    return "lload_0";

  case (0x1f):
    return "lload_1";

  case (0x20):
    return "lload_2";

  case (0x21):
    return "lload_3";

  case (0x22):
    return "fload_0";

  case (0x23):
    return "fload_1";

  case (0x24):
    return "fload_2";

  case (0x25):
    return "fload_3";

  case (0x26):
    return "dload_0";

  case (0x27):
    return "dload_1";

  case (0x28):
    return "dload_2";

  case (0x29):
    return "dload_3";

  case (0x2a):
    return "aload_0";

  case (0x2b):
    return "aload_1";

  case (0x2c):
    return "aload_2";

  case (0x2d):
    return "aload_3";

  case (0x2e):
    return "iaload";

  case (0x2f):
    return "laload";

  case (0x30):
    return "faload";

  case (0x31):
    return "daload";

  case (0x32):
    return "aaload";

  case (0x33):
    return "baload";

  case (0x34):
    return "caload";

  case (0x35):
    return "saload";

  case (0x36):
    return "istore";

  case (0x37):
    return "lstore";

  case (0x38):
    return "fstore";

  case (0x39):
    return "dstore";

  case (0x3a):
    return "astore";

  case (0x3b):
    return "istore_0";

  case (0x3c):
    return "istore_1";

  case (0x3d):
    return "istore_2";

  case (0x3e):
    return "istore_3";

  case (0x3f):
    return "lstore_0";

  case (0x40):
    return "lstore_1";

  case (0x41):
    return "lstore_2";

  case (0x42):
    return "lstore_3";

  case (0x43):
    return "fstore_0";

  case (0x44):
    return "fstore_1";

  case (0x45):
    return "fstore_2";

  case (0x46):
    return "fstore_3";

  case (0x47):
    return "dstore_0";

  case (0x48):
    return "dstore_1";

  case (0x49):
    return "dstore_2";

  case (0x4a):
    return "dstore_3";

  case (0x4b):
    return "astore_0";

  case (0x4c):
    return "astore_1";

  case (0x4d):
    return "astore_2";

  case (0x4e):
    return "astore_3";

  case (0x4f):
    return "iastore";

  case (0x50):
    return "lastore";

  case (0x51):
    return "fastore";

  case (0x52):
    return "dastore";

  case (0x53):
    return "aastore";

  case (0x54):
    return "bastore";

  case (0x55):
    return "castore";

  case (0x56):
    return "sastore";

  case (0x57):
    return "pop";

  case (0x58):
    return "pop2";

  case (0x59):
    return "dup";

  case (0x5a):
    return "dup_x1";

  case (0x5b):
    return "dup_x2";

  case (0x5c):
    return "dup2";

  case (0x5d):
    return "dup2_x1";

  case (0x5e):
    return "dup2_x2";

  case (0x5f):
    return "swap";

  case (0x60):
    return "iadd";

  case (0x61):
    return "ladd";

  case (0x62):
    return "fadd";

  case (0x63):
    return "dadd";

  case (0x64):
    return "isub";

  case (0x65):
    return "lsub";

  case (0x66):
    return "fsub";

  case (0x67):
    return "dsub";

  case (0x68):
    return "imul";

  case (0x69):
    return "lmul";

  case (0x6a):
    return "fmul";

  case (0x6b):
    return "dmul";

  case (0x6c):
    return "idiv";

  case (0x6d):
    return "ldiv";

  case (0x6e):
    return "fdiv";

  case (0x6f):
    return "ddiv";

  case (0x70):
    return "irem";

  case (0x71):
    return "lrem";

  case (0x72):
    return "frem";

  case (0x73):
    return "drem";

  case (0x74):
    return "ineg";

  case (0x75):
    return "lneg";

  case (0x76):
    return "fneg";

  case (0x77):
    return "dneg";

  case (0x78):
    return "ishl";

  case (0x79):
    return "lshl";

  case (0x7a):
    return "ishr";

  case (0x7b):
    return "lshr";

  case (0x7c):
    return "iushr";

  case (0x7d):
    return "lushr";

  case (0x7e):
    return "iand";

  case (0x7f):
    return "land";

  case (0x80):
    return "ior";

  case (0x81):
    return "lor";

  case (0x82):
    return "ixor";

  case (0x83):
    return "lxor";

  case (0x84):
    return "iinc";

  case (0x85):
    return "i2l";

  case (0x86):
    return "i2f";

  case (0x87):
    return "i2d";

  case (0x88):
    return "l2i";

  case (0x89):
    return "l2f";

  case (0x8a):
    return "l2d";

  case (0x8b):
    return "f2i";

  case (0x8c):
    return "f2l";

  case (0x8d):
    return "f2d";

  case (0x8e):
    return "d2i";

  case (0x8f):
    return "d2l";

  case (0x90):
    return "d2f";

  case (0x91):
    return "i2b";

  case (0x92):
    return "i2c";

  case (0x93):
    return "i2s";

  case (0x94):
    return "lcmp";

  case (0x95):
    return "fcmpl";

  case (0x96):
    return "fcmpg";

  case (0x97):
    return "dcmpl";

  case (0x98):
    return "dcmpg";

  case (0x99):
    return "ifeq";

  case (0x9a):
    return "ifne";

  case (0x9b):
    return "iflt";

  case (0x9c):
    return "ifge";

  case (0x9d):
    return "ifgt";

  case (0x9e):
    return "ifle";

  case (0x9f):
    return "if_icmpeq";

  case (0xa0):
    return "if_icmpne";

  case (0xa1):
    return "if_icmplt";

  case (0xa2):
    return "if_icmpge";

  case (0xa3):
    return "if_icmpgt";

  case (0xa4):
    return "if_icmple";

  case (0xa5):
    return "if_acmpeq";

  case (0xa6):
    return "if_acmpne";

  case (0xa7):
    return "goto";

  case (0xa8):
    return "jsr";

  case (0xa9):
    return "ret";

  case (0xaa):
    return "tableswitch";

  case (0xab):
    return "lookupswitch";

  case (0xac):
    return "ireturn";

  case (0xad):
    return "lreturn";

  case (0xae):
    return "freturn";

  case (0xaf):
    return "dreturn";

  case (0xb0):
    return "areturn";

  case (0xb1):
    return "return";

  case (0xb2):
    return "getstatic";

  case (0xb3):
    return "putstatic";

  case (0xb4):
    return "getfield";

  case (0xb5):
    return "putfield";

  case (0xb6):
    return "invokevirtual";

  case (0xb7):
    return "invokespecial";

  case (0xb8):
    return "invokestatic";

  case (0xb9):
    return "invokeinterface";

  case (0xba):
    return "invokedynamic";

  case (0xbb):
    return "new";

  case (0xbc):
    return "newarray";

  case (0xbd):
    return "anewarray";

  case (0xbe):
    return "arraylength";

  case (0xbf):
    return "athrow";

  case (0xc0):
    return "checkcast";

  case (0xc1):
    return "instanceof";

  case (0xc2):
    return "monitorenter";

  case (0xc3):
    return "monitorexit";

  case (0xc4):
    return "wide";

  case (0xc5):
    return "multianewarray";

  case (0xc6):
    return "ifnull";

  case (0xc7):
    return "ifnonnull";

  case (0xc8):
    return "goto_w";

  case (0xc9):
    return "jsr_w";

  case (0xca):
    return "breakpoint";

  case (0xfe):
    return "impdep1";

  case (0xff):
    return "impdep2";

  default:
    return "Invalid instruction.";
  }
}

void ClassViewer::printInstructionParameters(u1 *code, int &index)
{
  if (code[index] == 0x10 or (code[index] >= 0x15 and code[index] <= 0x19) or (code[index] >= 0x36 and code[index] <= 0x3a) or code[index] == 0xa9)
  {
    std::cout << unsigned(code[index + 1]) << std::endl;
    index += 1;
  }
  else if (code[index] == 0x11)
  {
    std::cout << ((code[index + 1] << 8) | code[index + 2]) << std::endl;
    index += 2;
  }
  else if (code[index] == 0x12)
  {
    u1 cp_index = code[index + 1];

    std::cout << "#" << unsigned(cp_index) << " <" << getNameFromIndex(class_file->constant_pool[cp_index - 1]) << ">" << std::endl;
    index += 1;
  }
  else if (code[index] == 0x13 or code[index] == 0x14 or (code[index] >= 0xb2 and code[index] <= 0xb8) or code[index] == 0xbb or code[index] == 0xbd or code[index] == 0xc0 or code[index] == 0xc1)
  {
    u2 cp_index = ((code[index + 1] << 8) | code[index + 2]);

    std::string constant_name = getNameFromIndex(class_file->constant_pool[cp_index - 1]);

    std::string name = splitByToken(constant_name, 0);
    std::string type = splitByToken(constant_name, 1);
    std::string name_and_type = "<" + name + "." + type + ">";

    std::cout << "#" << cp_index << " " << name_and_type << std::endl;
    index += 2;
  }
  else if (code[index] == 0x84)
  {
    std::cout << unsigned(code[index + 1]) << " by " << unsigned(code[index + 2]) << std::endl;
    index += 2;
  }
  else if ((code[index] >= 0x99 && code[index] <= 0xa8) || code[index] == 0xc6 || code[index] == 0xc7)
  {
    std::cout << index + ((code[index + 1] << 8) | code[index + 2]) << " (" << ((code[index + 1] << 8) | code[index + 2]) << ")" << std::endl;
    index += 2;
  }
  else if (code[index] == 0xaa)
  {
    u1 padding = (index + 1) % 4;

    int32_t defaultbytes = (code[padding + index + 1] << 24) | (code[padding + index + 2] << 16) | (code[padding + index + 3] << 8) | code[padding + index + 4];
    int32_t lowbytes = (code[padding + index + 5] << 24) | (code[padding + index + 6] << 16) | (code[padding + index + 7] << 8) | code[padding + index + 8];
    int32_t highbytes = (code[padding + index + 9] << 24) | (code[padding + index + 10] << 16) | (code[padding + index + 11] << 8) | code[padding + index + 12];

    // Recalculates padding to skip the 12 bytes read above
    padding += 12;

    std::cout << lowbytes << " to " << highbytes << std::endl;

    int table_lines_count = highbytes - lowbytes + 1;

    tab_count++;

    printTableSwitch(code, table_lines_count, lowbytes, defaultbytes, index, padding + index + 1);

    tab_count--;

    index += padding + 4 * table_lines_count;
  }
  else if (code[index] == 0xbc)
  {
    // atype is read with a +4 offset. When acessing types[idx], make sure that idx = atype - 4.
    u1 atype = code[index + 1];

    // Types are ordered as specified in JVMS8 documentation
    const char *types[] = {"boolean", "char", "float", "double", "byte", "short", "int", "long"};

    std::cout << unsigned(atype) << " (" << types[atype - 4] << ")" << std::endl;

    index += 1;
  }
  else if (code[index] == 0xc5)
  {
    u2 cp_index = (code[index + 1] << 8) | code[index + 2];

    std::cout << "#" << cp_index << " <" << getNameFromIndex(class_file->constant_pool[cp_index - 1]) << "> dim " << unsigned(code[index + 3]) << std::endl;
    index += 3;
  }
  else
  {
    std::cout << std::endl;
  }
}

void ClassViewer::printTableSwitch(u1 *code, int table_lines_count, int lowbytes, int defaultbytes, int index, int index_with_padding)
{
  std::string tabs = std::string(tab_count, '\t');

  for (int i = 0; i < table_lines_count; i++)
  {
    int32_t jump_offset = (code[index_with_padding] << 24) | (code[index_with_padding + 1] << 16) | (code[index_with_padding + 2] << 8) | code[index_with_padding + 3];

    std::cout << tabs << lowbytes << ": " << index + jump_offset << " (+" << jump_offset << ")" << std::endl;

    index_with_padding += 4;
    lowbytes++;
  }

  std::cout << tabs << "default: " << index + defaultbytes << " (+" << defaultbytes << ")" << std::endl;
}

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

    if (constant_pool[i]->tag == CONSTANT_Double or constant_pool[i]->tag == CONSTANT_Long)
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

  std::cout << "\tname_index: " << class_info_entry->info.class_info->name_index << " <" << name << ">" << std::endl;
}

void ClassViewer::printConstantFieldref(cp_info *constant_pool_fieldref)
{
  std::string name = getNameFromIndex(constant_pool_fieldref);

  std::string name_class_index = splitByToken(name, 0);
  std::string name_and_type_index = splitByToken(name, 1) + " : " + splitByToken(name, 2);

  std::cout << "\tclass_index: " << constant_pool_fieldref->info.fieldref_info->class_index << " <" << name_class_index << ">" << std::endl;
  std::cout << "\tname_and_type_index: " << constant_pool_fieldref->info.fieldref_info->name_and_type_index << " <" << name_and_type_index << ">" << std::endl;
}

void ClassViewer::printConstantMethodref(cp_info *methodref_info_entry)
{
  std::string name = getNameFromIndex(methodref_info_entry);

  std::string name_class_index = splitByToken(name, 0);
  std::string name_and_type_index = splitByToken(name, 1) + " : " + splitByToken(name, 2);

  std::cout << "\tclass_index: " << methodref_info_entry->info.methodref_info->class_index << " <" << name_class_index << ">" << std::endl;
  std::cout << "\tname_and_type_index: " << methodref_info_entry->info.methodref_info->name_and_type_index << " <" << name_and_type_index << ">" << std::endl;
}

void ClassViewer::printConstantInterfaceMethodref(cp_info *interfacemethodref_info_entry)
{
  std::string name = getNameFromIndex(interfacemethodref_info_entry);
  std::string name_class_index = splitByToken(name, 0);
  std::string name_and_type_index = splitByToken(name, 1) + " : " + splitByToken(name, 2);

  std::cout << "\tclass_index: " << interfacemethodref_info_entry->info.interfaceMethodref_info->class_index << " <" << name_class_index << ">" << std::endl;
  std::cout << "\tname_and_type_index: " << interfacemethodref_info_entry->info.interfaceMethodref_info->name_and_type_index << " <" << name_and_type_index << ">" << std::endl;
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

  std::string name_class_index = splitByToken(name, 0);
  std::string name_descriptor_index = splitByToken(name, 1);

  std::cout << "\tname_index: " << nameandtype_info_entry->info.nameAndType_info->name_index << " <" << name_class_index << ">" << std::endl;
  std::cout << "\tdescriptor_index: " << nameandtype_info_entry->info.nameAndType_info->descriptor_index << " <" << name_descriptor_index << ">" << std::endl;
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
  std::string name_bootstrap_index = splitByToken(name, 0);
  std::string name_and_type_index = splitByToken(name, 1) + " : " + splitByToken(name, 2);

  std::cout << "\tbootstrap_method_attr_index: " << invokeDynamic_info_entry->info.invokeDynamic_info->bootstrap_method_attr_index << " <" << name_bootstrap_index << ">" << std::endl;
  std::cout << "\tname_and_type_index: " << invokeDynamic_info_entry->info.invokeDynamic_info->name_and_type_index << " <" << name_and_type_index << ">" << std::endl;
}

void ClassViewer::printAttributes(attribute_info **attributes, u2 attribute_count)
{
  std::string tabs = std::string(tab_count, '\t');

  for (int i = 0; i < attribute_count; i++)
  {
    std::cout << tabs << "Attribute [" << i << "]:" << std::endl;

    tab_count++;

    printAttributeByIndex(attributes[i]);

    tab_count--;
  }
}

void ClassViewer::printAttributeByIndex(attribute_info *attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "attribute_name_index: " << attribute->attribute_name_index << std::endl;
  std::cout << tabs << "attribute_length: " << attribute->attribute_length << std::endl;

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

  std::cout << tabs << "max_stack: " << code_attribute->max_stack << std::endl;
  std::cout << tabs << "max_locals: " << code_attribute->max_locals << std::endl;
  std::cout << tabs << "code_length: " << code_attribute->code_length << std::endl;
  std::cout << tabs << "code: " << std::endl;

  tab_count++;

  printBytecode(code_attribute->code, code_attribute->code_length);

  tab_count--;

  std::cout << tabs << "exception_table_length: " << code_attribute->exception_table_length << std::endl;

  tab_count++;

  for (int i = 0; i < code_attribute->exception_table_length; i++)
  {
    std::cout << tabs << "Exception[" << i << "]: " << std::endl;

    printExceptionTable(code_attribute->exception_table[i]);
  }

  tab_count--;

  std::cout << tabs << "attributes_count: " << code_attribute->attributes_count << std::endl;

  printAttributes(code_attribute->attributes, code_attribute->attributes_count);
}

void ClassViewer::printBytecode(u1 *code, u2 code_length)
{
  std::string tabs = std::string(tab_count, '\t');

  for (int i = 0; i < code_length; i++)
  {
    std::cout << tabs << i << " " << getInstructionNameByOpcode(code[i]) << " ";
    printInstructionParameters(code, i);
  }
}

void ClassViewer::printExceptionTable(exception_table_info *exception_table_entry)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "start_pc: " << exception_table_entry->start_pc << std::endl;
  std::cout << tabs << "end_pc: " << exception_table_entry->end_pc << std::endl;
  std::cout << tabs << "handler_pc: " << exception_table_entry->handler_pc << std::endl;
  std::cout << tabs << "catch_type: " << exception_table_entry->catch_type << std::endl;
}

void ClassViewer::printExceptionsAttribute(Exceptions_attribute *exceptions_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "number_of_exceptions: " << exceptions_attribute->number_of_exceptions << std::endl;
  std::cout << tabs << "exception_index_table: " << exceptions_attribute->exception_index_table << std::endl;
}

void ClassViewer::printInnerClassesAttribute(InnerClasses_attribute *innerclasses_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "number_of_classes: " << innerclasses_attribute->number_of_classes << std::endl;

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

  std::cout << tabs << "inner_class_info_index: " << classes_entry->inner_class_info_index << std::endl;
  std::cout << tabs << "outer_class_info_index: " << classes_entry->outer_class_info_index << std::endl;
  std::cout << tabs << "inner_name_index: " << classes_entry->inner_name_index << std::endl;
  std::cout << tabs << "inner_class_access_flags: " << classes_entry->inner_class_access_flags << std::endl;
}

void ClassViewer::printSourceFileAttribute(SourceFile_attribute *sourcefile_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "sourcefile_index: " << sourcefile_attribute->sourcefile_index << std::endl;
}

void ClassViewer::printLineNumberTableAttribute(LineNumberTable_attribute *linenumbertable_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "line_number_table_length: " << linenumbertable_attribute->line_number_table_length << std::endl;

  tab_count++;

  for (int i = 0; i < linenumbertable_attribute->line_number_table_length; i++)
  {
    std::cout << tabs << "Line number table [" << i << "]:" << std::endl;

    printLineNumberTable(linenumbertable_attribute->line_number_table[i]);
  }

  tab_count--;
}

void ClassViewer::printLineNumberTable(line_number_table_info *line_number_table_entry)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "start_pc: " << line_number_table_entry->start_pc << std::endl;
  std::cout << tabs << "line_number: " << line_number_table_entry->line_number << std::endl;
}

void ClassViewer::printLocalVariableTableAttribute(LocalVariableTable_attribute *localvariabletable_attribute)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "local_variable_table_length: " << localvariabletable_attribute->local_variable_table_length << std::endl;

  tab_count++;

  for (int i = 0; i < localvariabletable_attribute->local_variable_table_length; i++)
  {
    std::cout << tabs << "Local variable table [" << i << "]" << std::endl;

    printLocalVariableTable(localvariabletable_attribute->local_variable_table[i]);
  }

  tab_count--;
}

void ClassViewer::printLocalVariableTable(local_variable_table_info *local_variable_table_entry)
{
  std::string tabs = std::string(tab_count, '\t');

  std::cout << tabs << "start_pc: " << local_variable_table_entry->start_pc << std::endl;
  std::cout << tabs << "length: " << local_variable_table_entry->length << std::endl;
  std::cout << tabs << "name_index: " << local_variable_table_entry->name_index << std::endl;
  std::cout << tabs << "descriptor_index: " << local_variable_table_entry->descriptor_index << std::endl;
  std::cout << tabs << "index: " << local_variable_table_entry->index << std::endl;
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
  case CONSTANT_String:
    index = constant_pool_getname->info.string_info->string_index - 1;

    return getNameFromIndex(class_file->constant_pool[index]);
  case CONSTANT_Fieldref:
    index = constant_pool_getname->info.fieldref_info->class_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);

    index = constant_pool_getname->info.fieldref_info->name_and_type_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);

    return s1 + "," + s2;
  case CONSTANT_Methodref:
    index = constant_pool_getname->info.methodref_info->class_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);

    index = constant_pool_getname->info.methodref_info->name_and_type_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);

    return s1 + "," + s2;
  case CONSTANT_InterfaceMethodref:
    index = constant_pool_getname->info.interfaceMethodref_info->class_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);

    index = constant_pool_getname->info.interfaceMethodref_info->name_and_type_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);

    return s1 + "," + s2;
  case CONSTANT_NameAndType:
    index = constant_pool_getname->info.nameAndType_info->name_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);

    index = constant_pool_getname->info.nameAndType_info->descriptor_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);

    return s1 + "," + s2;
  case CONSTANT_MethodHandle:
    index = constant_pool_getname->info.methodHandle_info->reference_index - 1;

    return getNameFromIndex(class_file->constant_pool[index]);
  case CONSTANT_MethodType:
    index = constant_pool_getname->info.methodType_info->descriptor_index - 1;

    return getNameFromIndex(class_file->constant_pool[index]);
  case CONSTANT_InvokeDynamic:
    index = constant_pool_getname->info.invokeDynamic_info->bootstrap_method_attr_index - 1;
    s1 = getNameFromIndex(class_file->constant_pool[index]);

    index = constant_pool_getname->info.invokeDynamic_info->name_and_type_index - 1;
    s2 = getNameFromIndex(class_file->constant_pool[index]);

    return s1 + "," + s2;
  case CONSTANT_Utf8:
    for (int i = 0; i < constant_pool_getname->info.utf8_info->length; i++)
    {
      s += constant_pool_getname->info.utf8_info->bytes[i];
    }

    return s;
  case CONSTANT_Double:
    //TODO

    return "TODO";
  default:
    std::cout << "Tag <" << constant_pool_getname->tag << "> not found." << std::endl;

    return "";
  }
}

std::string ClassViewer::splitByToken(std::string str, int position)
{
  std::istringstream iss(str);
  std::string token;

  int index = 0;

  while (std::getline(iss, token, ','))
  {
    if (index == position)
      return token;

    index++;
  }

  return str;
}