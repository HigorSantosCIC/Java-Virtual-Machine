#ifndef RUNTIME_DATA_AREA_HPP
#define RUNTIME_DATA_AREA_HPP

#include <stdlib.h>
#include <frame_stack.hpp>
#include <method_area.hpp>

class RuntimeDataArea
{
public:
    RuntimeDataArea();
    ~RuntimeDataArea();

    void initializeFrameStack();

    FrameStack *frame_stack;
    MethodArea *method_area;
};

#endif