#include "runtime_data_area.hpp"

RuntimeDataArea::RuntimeDataArea()
{
    frame_stack = (FrameStack *)malloc(sizeof(FrameStack));
    method_area = (MethodArea *)malloc(sizeof(MethodArea));
}

RuntimeDataArea::~RuntimeDataArea()
{
}

void RuntimeDataArea::initializeFrameStack()
{
}