#ifndef FRAME_HPP
#define FRAME_HPP

#include <int_types.hpp>
#include <constant_pool.hpp>
#include <stack>
#include <unordered_map>
#include "generic_type.hpp"

/**
 * A frame is a data structure that contains information about the methods executed by the interpreter. All frames are stack in a FrameStack.
 
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

    u4 getPc();

private:
    std::unordered_map<int, GenericType *> local_variables;
    std::stack<GenericType *> operand_stack;
    cp_info **constant_pool;
    u4 pc;
};

#endif