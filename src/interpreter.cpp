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
    while (!runtime_data_area->frame_stack->isEmpty())
    {
        u1 instruction = runtime_data_area->fetchInstruction(0);

        switch (instruction)
        {
        case 0x14:
            ldc2_w();
            break;
        case 0x47:
            dstore_0();
            break;
        case 0x48:
            dstore_1();
            break;
        case 0x49:
            dstore_2();
            break;
        case 0x4a:
            dstore_3();
            break;
        case 0xb2:
            getstatic();
            break;
        default:
            break;
        }
    }
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
    current_frame->setPcByOffset(3);
}

void Interpreter::dstore_0()
{
    dstore_n(0);
}

void Interpreter::dstore_1()
{
    dstore_n(1);
}

void Interpreter::dstore_2()
{
    dstore_n(2);
}

void Interpreter::dstore_3()
{
    dstore_n(3);
}

void Interpreter::dstore_n(int index)
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    GenericType *value_generic = current_frame->getTopOperand();

    // TODO: Validate if is double

    current_frame->setLocalVariable(value_generic, index);

    current_frame->setPcByOffset(1);
}

void Interpreter::getstatic()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    cp_info **constant_pool = current_frame->getConstantPool();

    u1 index_byte1 = runtime_data_area->fetchInstruction(1);
    u1 index_byte2 = runtime_data_area->fetchInstruction(2);

    u2 index = (index_byte1 << 8) | index_byte2;

    if (constant_pool[index - 1]->tag != CONSTANT_Fieldref)
    {
        std::cout << "getstatic instruction is accessing an invalid entry in constant pool." << std::endl;
        exit(1);
    }

    std::string utf8_data = runtime_data_area->getNameFromConstantPoolEntry(constant_pool[index - 1]);

    std::string class_name = splitByToken(utf8_data, 0);
    std::string field_name = splitByToken(utf8_data, 1);
    std::string field_descriptor = splitByToken(utf8_data, 2);

    if (class_name == "java/lang/System" and field_descriptor == "Ljava/io/PrintStream;")
    {
        current_frame->setPcByOffset(3);
        return;
    }

    //TODO: Load class from method area
}

std::string Interpreter::splitByToken(std::string str, int position)
{
    std::istringstream iss(str);
    std::string token;

    int index = 0;

    while (std::getline(iss, token, ','))
    {
        if (index == position)
            return token;

        index++;
    }

    return str;
}