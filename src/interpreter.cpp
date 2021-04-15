#include "interpreter.hpp"

Interpreter::Interpreter(RuntimeDataArea *p_runtime_data_area)
{
    runtime_data_area = p_runtime_data_area;
}

Interpreter::~Interpreter()
{
}

void Interpreter::run()
{
    u1 instruction = runtime_data_area->fetchInstruction(0);

    if (instruction == 0x14)
        ldc2_w();
}

void Interpreter::ldc2_w()
{
    u1 index_byte1 = runtime_data_area->fetchInstruction(1);
    u1 index_byte2 = runtime_data_area->fetchInstruction(2);

    u2 index_value = (index_byte1 << 8) | index_byte2;

    GenericType *value_generic = (GenericType *)malloc(sizeof(GenericType));

    // Get reference to constant pool
    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    cp_info **constant_pool = current_frame->getConstantPool();

    // Constant pool will contain the value of the long or double to be pushed into operand stack
    cp_info *constant_pool_entry = constant_pool[index_value - 1];

    if (constant_pool_entry->tag == CONSTANT_Long)
    {
        u4 high_bytes = constant_pool_entry->info.long_info->high_bytes;
        u4 low_bytes = constant_pool_entry->info.long_info->low_bytes;

        int64_t long_value = ((int64_t)high_bytes << 32) + (int64_t)low_bytes;

        value_generic->data.long_value = long_value;
    }
    else if (constant_pool_entry->tag == CONSTANT_Double)
    {
        u4 high_bytes = constant_pool_entry->info.long_info->high_bytes;
        u4 low_bytes = constant_pool_entry->info.long_info->low_bytes;

        uint64_t long_value = ((uint64_t)high_bytes << 32) + (uint64_t)low_bytes;

        double double_value = *(double *)&long_value;
        value_generic->data.double_value = double_value;
    }
    else
    {
        // Invalid tag
    }

    current_frame->pushValueIntoOperandStack(value_generic);
    current_frame->setPcByOffset(2);
}