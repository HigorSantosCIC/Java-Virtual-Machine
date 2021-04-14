#ifndef METHOD_AREA_HPP
#define METHOD_AREA_HPP

#include <stdlib.h>
#include <string>
#include <unordered_map>

#include "class_file.hpp"

/**
 * Method area is a storage area for compiled code. When a class file is loaded, it must be inserted into the method area.
 */
class MethodArea
{
public:
    /**
     * @brief 
     * @param class_name Name of the class used as key in the classes map. This is a valid key because class names must be unique.
     * @param class_file Pointer to a loaded class_file.
     */
    void addClass(std::string class_name, ClassFile *class_file);

    /**
     * @brief remove a class from the method area.
     * @param class_name The name of the class to be removed.
     */
    void removeClass(std::string class_name);

    /**
     * @brief Search a given method in the specified class_file.
     * @param class_name Key to the class file pointer in classes unordered map.
     * @param method_name Method name to be searched in class file identified by class_name
     * @param method_descriptor Method descriptor to be searched in class file identified by class_name
     * @return (method_info *) object that corresponds to the method_name argument.
     * @return (NULL) if name or descriptor doesn't match any existing method in classfile.
     */
    method_info *getClassMethodByNameAndDescriptor(std::string class_name, std::string method_name, std::string method_descriptor);

private:
    std::unordered_map<std::string, ClassFile *> classes;

    /**
     * @brief Asserts if a given class is loaded into classes map.
     * @param class_name Key to the class file pointer in classes unordered map.
     */
    bool isClassLoaded(std::string class_name);
};

#endif