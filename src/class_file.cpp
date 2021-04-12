#include "class_file.hpp"

std::string ClassFile::getClassName()
{
    u2 class_name_index = constant_pool[this_class-1]->info.class_info->name_index;

    u2 length = constant_pool[class_name_index-1]->info.utf8_info->length;
    u1 *name_bytes = constant_pool[class_name_index-1]->info.utf8_info->bytes;

    std::string class_name;

    for (int i = 0; i < length; i++)
    {
        class_name += name_bytes[i];
    }

    return class_name;
}