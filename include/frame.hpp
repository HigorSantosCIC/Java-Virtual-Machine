#ifndef FRAME_HPP
#define FRAME_HPP

#include <int_types.hpp>
#include <class_file.hpp>
#include <stack>
#include <unordered_map>
#include "generic_type.hpp"
#include <vector>

/**
 * A frame is a data structure that contains information about the methods executed by the interpreter. All frames are stack in a FrameStack.
 
 */

class Frame
{
public:
    /**
     * @brief Creates a frame.
     */
    Frame(ClassFile *class_file, std::string p_method_name, std::string p_method_descriptor);
    Frame(ClassFile *class_file, std::string p_method_name, std::string p_method_descriptor, std::vector<GenericType *> arguments);
    ~Frame();

    void pushValueIntoOperandStack(GenericType *value);
    GenericType *popValueFromOperandStack();

    // Getters
    u4 getPc();
    std::string getClassName();
    std::string getMethodName();
    std::string getMethodDescriptor();
    cp_info **getConstantPool();
    GenericType *getTopOperand();
    GenericType *getLocalVariable(int index);

    // Setters
    void setPcByOffset(int offset);
    void setLocalVariable(GenericType *value, int index);

private:
    std::unordered_map<int, GenericType *> local_variables;
    std::stack<GenericType *> operand_stack;
    std::string class_name;
    std::string method_name;
    std::string method_descriptor;
    cp_info **constant_pool;
    u4 pc;
};

#endif