#include "method_area.hpp"

MethodArea::MethodArea()
{
}

MethodArea::~MethodArea()
{
}

void MethodArea::addClass(std::string class_name, ClassFile *class_file)
{
    classes[class_name] = class_file;
}

void MethodArea::removeClass(std::string class_name)
{
    classes.erase(classes.find(class_name));
}