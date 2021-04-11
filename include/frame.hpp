#ifndef FRAME_HPP
#define FRAME_HPP

#include <int_types.hpp>
#include <constant_pool.hpp>
#include <stack>
#include <map>
#include "generic_type.hpp"

/**
 * A frame is a data structure that contains information about the current method executed by the interpreter.
 
 */
class Frame
{
public:
    /**
     * @brief Creates a frame.
     * @param constant_pool reference to the constant pool of the frame method's class.
     */
    Frame(cp_info **constant_pool);
    ~Frame();

private:
    unordered_map<int, GenericType *> local_variables;
    stack<GenericType *> operand_stack;
    cp_info **constant_pool;
    u4 pc;
};

#endif