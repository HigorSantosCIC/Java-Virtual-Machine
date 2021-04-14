#include "frame_stack.hpp"

FrameStack::FrameStack()
{
}

FrameStack::~FrameStack()
{
}

void FrameStack::push(Frame *frame)
{
    frame_stack.push(frame);
}

void FrameStack::pop()
{
    frame_stack.pop();
}

bool FrameStack::isEmpty()
{
    return frame_stack.empty();
}

Frame *FrameStack::getTop()
{
    return frame_stack.top();
}
