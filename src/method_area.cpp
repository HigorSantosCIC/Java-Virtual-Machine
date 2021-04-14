#include "method_area.hpp"

void MethodArea::addClass(std::string class_name, ClassFile *class_file)
{
    classes.insert(make_pair(class_name, class_file));
}

void MethodArea::removeClass(std::string class_name)
{
    classes.erase(classes.find(class_name));
}

method_info *MethodArea::getClassMethodByNameAndDescriptor(std::string class_name, std::string method_name, std::string method_descriptor)
{
    if (!isClassLoaded(class_name))
        return NULL;

    ClassFile *class_file = classes[class_name];

    return class_file->searchMethodByNameAndDescriptor(method_name, method_descriptor);
}

bool MethodArea::isClassLoaded(std::string class_name)
{
    return classes.find(class_name) != classes.end() ? true : false;
}