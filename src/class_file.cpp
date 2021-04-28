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

bool ClassFile::fieldExists(std::string field_name)
{
    for (int i = 0; i < fields_count; i++)
    {
        std::string current_field_name = getNameFromConstantPoolEntry(constant_pool[fields[i]->name_index - 1]);

        if (field_name == current_field_name)
            return true;
    }

    return false;
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
    {
        u4 high_bytes = constant_pool_entry->info.double_info->high_bytes;
        u4 low_bytes = constant_pool_entry->info.double_info->low_bytes;

        uint64_t long_value = ((uint64_t)high_bytes << 32) + (uint64_t)low_bytes;

        double double_value = *(double *)&long_value;

        s = std::to_string(double_value);

        return s;
    }
    case CONSTANT_Long:
    {
        u4 high_bytes = constant_pool_entry->info.long_info->high_bytes;
        u4 low_bytes = constant_pool_entry->info.long_info->low_bytes;

        int64_t long_value = ((int64_t)high_bytes << 32) + (int64_t)low_bytes;

        s = std::to_string(long_value);

        return s;
    }
    case CONSTANT_Float:
        s = std::to_string(*(float *)&constant_pool_entry->info.float_info->bytes);

        return s;
    case CONSTANT_Integer:
        s = std::to_string((int32_t)constant_pool_entry->info.integer_info->bytes);

        return s;
    default:
        std::cout << "Tag <" << constant_pool_entry->tag << "> not found." << std::endl;
        break;
    }

    return "";
}

u1 *ClassFile::getCodeByMethod(method_info *method)
{
    for (int i = 0; i < method->attributes_count; i++)
    {
        u2 attribute_name_index = method->attributes[i]->attribute_name_index;

        if (getNameFromConstantPoolEntry(constant_pool[attribute_name_index - 1]) == "Code")
            return method->attributes[i]->attribute.code_attribute->code;
    }

    return NULL;
}

u1 ClassFile::getInstructionOrOperand(std::string method_name, std::string method_descriptor, u4 pc)
{
    method_info *method = searchMethodByNameAndDescriptor(method_name, method_descriptor);

    if (method == NULL)
        return NULL;

    u1 *code = getCodeByMethod(method);

    if (code == NULL)
        return NULL;

    return code[pc];
}