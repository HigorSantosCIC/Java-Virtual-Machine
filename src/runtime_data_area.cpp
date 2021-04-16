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

u1 RuntimeDataArea::fetchInstruction(u2 pc_offset)
{
    Frame *current_frame = frame_stack->getTop();

    // Get current frame info
    u4 pc = current_frame->getPc();
    pc += pc_offset;

    std::string class_name = current_frame->getClassName();
    ClassFile *class_file = method_area->getClassFile(class_name);

    std::string method_name = current_frame->getMethodName();
    std::string method_descriptor = current_frame->getMethodDescriptor();

    // Get instruction based on method info and pc
    u1 instruction = class_file->getInstructionOrOperand(method_name, method_descriptor, pc);

    return instruction;
}

std::string RuntimeDataArea::getNameFromConstantPoolEntry(cp_info *constant_pool_entry)
{
    Frame *current_frame = frame_stack->getTop();
    std::string class_name = current_frame->getClassName();
    ClassFile *class_file = method_area->getClassFile(class_name);

    return class_file->getNameFromConstantPoolEntry(constant_pool_entry);
}

//TODO: Split into 2 methods.
ClassFile *RuntimeDataArea::loadClassByName(std::string class_name)
{
    if (method_area->isClassLoaded(class_name))
    {
        return method_area->getClassFile(class_name);
    }

    ClassLoader class_loader((class_name + ".class").c_str());
    class_loader.readClassFile();

    ClassFile *class_file = class_loader.getClassFile();

    method_area->addClass(class_name, class_file);

    for (int i = 0; i < class_file->methods_count; i++)
    {
        u2 method_name_index = class_file->methods[i]->name_index;
        u2 descriptor_name_index = class_file->methods[i]->descriptor_index;

        std::string method_name =
            class_file->getNameFromConstantPoolEntry(class_file->constant_pool[method_name_index - 1]);

        std::string method_descriptor =
            class_file->getNameFromConstantPoolEntry(class_file->constant_pool[descriptor_name_index - 1]);

        if (method_name == "<init>" and method_descriptor == "()V")
        {
            Frame *init_frame = new Frame(class_file, "<init>", "()V");
            frame_stack->push(init_frame);
            break;
        }
    }

    return class_file;
}