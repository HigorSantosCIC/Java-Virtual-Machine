#include "class_file.hpp"

std::string ClassFile::getClassName()
{
    u2 class_name_index = constant_pool[this_class - 1]->info.class_info->name_index;

    u2 length = constant_pool[class_name_index - 1]->info.utf8_info->length;
    u1 *name_bytes = constant_pool[class_name_index - 1]->info.utf8_info->bytes;

    std::string class_name;

    for (int i = 0; i < length; i++)
    {
        class_name += name_bytes[i];
    }

    return class_name;
}

method_info *ClassFile::searchMethodByNameAndDescriptor(std::string method_name, std::string method_descriptor)
{
    for (int i = 0; i < methods_count; i++)
    {
        method_info *current_method = methods[i];

        std::string current_method_name = getNameFromConstantPoolEntry(constant_pool[current_method->name_index - 1]);
        std::string current_method_descriptor = getNameFromConstantPoolEntry(constant_pool[current_method->descriptor_index - 1]);

        if (method_name == current_method_name and method_descriptor == current_method_descriptor)
            return current_method;
    }

    return NULL;
}

std::string ClassFile::getNameFromConstantPoolEntry(cp_info *constant_pool_entry)
{
    std::string s = "";
    std::string s1 = "";
    std::string s2 = "";
    u2 index;

    switch (constant_pool_entry->tag)
    {
    case CONSTANT_Class:
        index = constant_pool_entry->info.class_info->name_index - 1;

        return getNameFromConstantPoolEntry(constant_pool[index]);
    case CONSTANT_String:
        index = constant_pool_entry->info.string_info->string_index - 1;

        return getNameFromConstantPoolEntry(constant_pool[index]);
    case CONSTANT_Fieldref:
        index = constant_pool_entry->info.fieldref_info->class_index - 1;
        s1 = getNameFromConstantPoolEntry(constant_pool[index]);

        index = constant_pool_entry->info.fieldref_info->name_and_type_index - 1;
        s2 = getNameFromConstantPoolEntry(constant_pool[index]);

        return s1 + "," + s2;
    case CONSTANT_Methodref:
        index = constant_pool_entry->info.methodref_info->class_index - 1;
        s1 = getNameFromConstantPoolEntry(constant_pool[index]);

        index = constant_pool_entry->info.methodref_info->name_and_type_index - 1;
        s2 = getNameFromConstantPoolEntry(constant_pool[index]);

        return s1 + "," + s2;
    case CONSTANT_InterfaceMethodref:
        index = constant_pool_entry->info.interfaceMethodref_info->class_index - 1;
        s1 = getNameFromConstantPoolEntry(constant_pool[index]);

        index = constant_pool_entry->info.interfaceMethodref_info->name_and_type_index - 1;
        s2 = getNameFromConstantPoolEntry(constant_pool[index]);

        return s1 + "," + s2;
    case CONSTANT_NameAndType:
        index = constant_pool_entry->info.nameAndType_info->name_index - 1;
        s1 = getNameFromConstantPoolEntry(constant_pool[index]);

        index = constant_pool_entry->info.nameAndType_info->descriptor_index - 1;
        s2 = getNameFromConstantPoolEntry(constant_pool[index]);

        return s1 + "," + s2;
    case CONSTANT_MethodHandle:
        index = constant_pool_entry->info.methodHandle_info->reference_index - 1;

        return getNameFromConstantPoolEntry(constant_pool[index]);
    case CONSTANT_MethodType:
        index = constant_pool_entry->info.methodType_info->descriptor_index - 1;

        return getNameFromConstantPoolEntry(constant_pool[index]);
    case CONSTANT_InvokeDynamic:
        index = constant_pool_entry->info.invokeDynamic_info->bootstrap_method_attr_index - 1;
        s1 = getNameFromConstantPoolEntry(constant_pool[index]);

        index = constant_pool_entry->info.invokeDynamic_info->name_and_type_index - 1;
        s2 = getNameFromConstantPoolEntry(constant_pool[index]);

        return s1 + "," + s2;
    case CONSTANT_Utf8:
        for (int i = 0; i < constant_pool_entry->info.utf8_info->length; i++)
        {
            s += constant_pool_entry->info.utf8_info->bytes[i];
        }

        return s;
    case CONSTANT_Double:
        //TODO

        return "TODO";
    default:
        std::cout << "Tag <" << constant_pool_entry->tag << "> not found." << std::endl;

        return "";
    }
}