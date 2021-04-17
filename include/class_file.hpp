#ifndef CLASS_FILE_HPP
#define CLASS_FILE_HPP

#include "int_types.hpp"
#include "constant_pool.hpp"
#include "fields.hpp"
#include "methods.hpp"
#include "attributes.hpp"
#include <string>

typedef struct
{
  u4 magic;
  u2 minor_version;
  u2 major_version;
  u2 constant_pool_count;
  cp_info **constant_pool;
  u2 access_flags;
  u2 this_class;
  u2 super_class;
  u2 interfaces_count;
  u2 *interfaces;
  u2 fields_count;
  field_info **fields;
  u2 methods_count;
  method_info **methods;
  u2 attributes_count;
  attribute_info **attributes;

  std::string getClassName();
  method_info *searchMethodByNameAndDescriptor(std::string method_name, std::string method_descriptor);
  std::string getNameFromConstantPoolEntry(cp_info *constant_pool_entry);
  u1 *getCodeByMethod(method_info *method);

  /**
     * @brief Verify if a given field exists in the class file
     * @param field_name
     * @return (true) if field exists.
     * @return (false) if field doesn't exists.
     */
  bool fieldExists(std::string field_name);

  /**
     * @brief 
     * 1) Fetch method in class_file;
     * 
     * 2) Fetch code in method attributes;
     * 
     * 3) Extract instruction or operand indexed by pc register.
     * @param class_name Key to the class file pointer in classes unordered map.
     * @param method_name Method name to be searched in class file identified by class_name.
     * @param method_descriptor Method descriptor to be searched in class file identified by class_name.
     * @param pc index that points to code[] position to be returned.
     * @return (u1) instruction or operand indexed by pc
     * @return (NULL) if class, method or code is not found.
     */
  u1 getInstructionOrOperand(std::string method_name, std::string method_descriptor, u4 pc);

} ClassFile;

#endif