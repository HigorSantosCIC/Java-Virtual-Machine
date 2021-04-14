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

u1 RuntimeDataArea::fetchInstruction()
{
    Frame *current_frame = frame_stack->getTop();

    // Get current frame info
    u4 pc = current_frame->getPc();

    std::string class_name = current_frame->getClassName();
    ClassFile *class_file = method_area->getClassFile(class_name);

    std::string method_name = current_frame->getMethodName();
    std::string method_descriptor = current_frame->getMethodDescriptor();

    // Get instruction based on method info and pc
    u1 instruction = class_file->getInstructionOrOperand(method_name, method_descriptor, pc);

    return instruction;
}