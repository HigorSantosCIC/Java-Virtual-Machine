#ifndef FRAME_STACK_HPP
#define FRAME_STACK_HPP

#include <stack>
#include <stdlib.h>
#include "frame.hpp"

/**
 * A frame stack stores all frames being executed by the JVM interpreter. 
 * The current context is referenced by the top of the stack.
 * 
 * Everytime a new method is called by the current context, a new frame is created and pushed into the top of the stack. 
 * When its execution finishes, the frame will be popped and its return value appended to the operand stack of the new top frame.
 * 
 * When the frame stack is empty, no context is currently being executed, indicating that the program has finished running.
 */
class FrameStack
{
public:
    FrameStack();
    ~FrameStack();

    /**
     * @brief Push frame to the stack.
     * @param frame a pointer to the frame to be added.
     */
    void push(Frame *frame);

    /**
     * @brief Pop the top frame of the stack.
     */
    void pop();

    /**
     * @brief Verify if the frame stack is empty.
     * @return Boolean value indicating wheter the stack is empty (true) or non-empty (false).
     */
    bool isEmpty();

private: 
    stack<Frame *> frame_stack;
};

#endif