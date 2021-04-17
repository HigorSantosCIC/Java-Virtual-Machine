#include <frame.hpp>

Frame::Frame(ClassFile *class_file, std::string p_method_name, std::string p_method_descriptor)
{
    constant_pool = class_file->constant_pool;
    class_name = class_file->getNameFromConstantPoolEntry(constant_pool[class_file->this_class - 1]);
    method_name = p_method_name;
    method_descriptor = p_method_descriptor;
    pc = 0;
}

Frame::~Frame()
{
}

u4 Frame::getPc()
{
    return pc;
}

std::string Frame::getClassName()
{
    return class_name;
}

std::string Frame::getMethodName()
{
    return method_name;
}

std::string Frame::getMethodDescriptor()
{
    return method_descriptor;
}

cp_info **Frame::getConstantPool()
{
    return constant_pool;
}

GenericType *Frame::getTopOperand()
{
    return operand_stack.top();
}

GenericType *Frame::getLocalVariable(int index)
{
    return local_variables[index];
}

void Frame::setPcByOffset(int offset)
{
    pc += offset;
}

void Frame::setLocalVariable(GenericType *value, int index)
{
    local_variables[index] = value;
}

void Frame::pushValueIntoOperandStack(GenericType *value)
{
    operand_stack.push(value);
}

GenericType *Frame::popValueFromOperandStack()
{
    GenericType *value = operand_stack.top();
    operand_stack.pop();

    return value;
}
