#include "attributes.hpp"

std::string AttributeUtils::getAttributeType(cp_info **constant_pool, u2 index)
{
  if (constant_pool[index - 1]->tag == CONSTANT_Utf8)
  {
    return std::string((char *)constant_pool[index - 1]->info.utf8_info->bytes);
  }

  return NULL;
}
