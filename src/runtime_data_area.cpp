#include "runtime_data_area.hpp"

RuntimeDataArea::RuntimeDataArea()
{
    frame_stack = new FrameStack();
    method_area = new MethodArea();
}

RuntimeDataArea::~RuntimeDataArea()
{
}

void RuntimeDataArea::initializeFrameStack()
{
}