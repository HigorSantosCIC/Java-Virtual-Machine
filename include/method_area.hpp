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
    MethodArea();
    ~MethodArea();

    /**
     * @brief 
     * @param class_name Name of the class used as key in the classes map.
     * @param class_file Pointer to a loaded class_file.
     
    */
    void addClass(std::string class_name, ClassFile *class_file);

    /**
    * @brief remove a class from the method area.
    * @param class_name The name of the class to be removed.
   */
    void removeClass(std::string class_name);

private:
    std::unordered_map<std::string, ClassFile *> classes;
};

#endif