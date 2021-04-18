#include "interpreter.hpp"

Interpreter::Interpreter(RuntimeDataArea *p_runtime_data_area)
{
    runtime_data_area = p_runtime_data_area;
    isInstructionWide = false;
}

Interpreter::~Interpreter()
{
}

void Interpreter::run()
{
    int i = 1;

    while (!runtime_data_area->frame_stack->isEmpty())
    {
        u1 instruction = runtime_data_area->fetchInstruction(0);

        std::cout << i << ". Executing " << std::hex << unsigned(instruction) << std::dec << std::endl;

        switch (instruction)
        {
        case 0x02:
            iconst_m1();
            break;
        case 0x03:
            iconst_0();
            break;
        case 0x04:
            iconst_1();
            break;
        case 0x05:
            iconst_2();
            break;
        case 0x06:
            iconst_3();
            break;
        case 0x07:
            iconst_4();
            break;
        case 0x08:
            iconst_5();
            break;
        case 0xb:
            fconst_0();
            break;
        case 0xc:
            fconst_1();
            break;
        case 0xd:
            fconst_2();
            break;
        case 0x10:
            bipush();
            break;
        case 0x11:
            sipush();
            break;
        case 0x12:
            ldc();
            break;
        case 0x14:
            ldc2_w();
            break;
        case 0x15:
            iload();
            break;
        case (0x2a):
            aload_0();
            break;
        case (0x2b):
            aload_1();
            break;
        case (0x2c):
            aload_2();
            break;
        case (0x2d):
            aload_3();
            break;
        case (0x26):
            dload_0();
            break;
        case (0x27):
            dload_1();
            break;
        case (0x28):
            dload_2();
            break;
        case (0x29):
            dload_3();
            break;
        case (0x32):
            aaload();
            break;
        case (0x1a):
            iload_0();
            break;
        case (0x1b):
            iload_1();
            break;
        case (0x1c):
            iload_2();
            break;
        case (0x1d):
            iload_3();
            break;
        case (0x36):
            istore();
            break;
        case (0x3a):
            astore();
            break;
        case (0x4b):
            astore_0();
            break;
        case (0x4c):
            astore_1();
            break;
        case (0x4d):
            astore_2();
            break;
        case (0x4e):
            astore_3();
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
        case 0x4f:
            iastore();
            break;
        case 0x50:
            lastore();
            break;
        case 0x51:
            fastore();
            break;
        case 0x52:
            dastore();
            break;
        case (0x53):
            aastore();
            break;
        case 0x54:
            bastore();
            break;
        case 0x55:
            castore();
            break;
        case 0x56:
            sastore();
            break;
        case 0x59:
            dup();
            break;
        case 0x63:
            dadd();
            break;
        case 0x67:
            dsub();
            break;
        case 0x6b:
            dmul();
            break;
        case 0x6f:
            ddiv();
            break;
        case 0x73:
            drem();
            break;
        case 0x77:
            dneg();
            break;
        case 0x84:
            iinc();
            break;
        case (0xa2):
            if_icmpge();
            break;
        case (0xa7):
            gotoInstruction();
            break;
        case (0xaa):
            tableswitch();
            break;
        case (0xac):
            ireturn();
            break;
        case (0xb1):
            returnInstruction();
            break;
        case 0xb2:
            getstatic();
            break;
        case (0xb6):
            invokevirtual();
            break;
        case (0xb8):
            invokestatic();
            break;
        case (0xbc):
            newarray();
            break;
        case (0xc5):
            multianewarray();
            break;
        default:
            std::cout << "Exiting interpreter on opcode " << std::hex << unsigned(instruction) <<  std::dec << std::endl;
            return;
        }

        i++;
    }
}

void Interpreter::iinc()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    //TODO: Add support for wide instructions.

    u2 index = (u2)runtime_data_area->fetchInstruction(1);
    int32_t inc = (int32_t)runtime_data_area->fetchInstruction(2);

    GenericType *value_generic = current_frame->getLocalVariable(index);

    value_generic->data.int_value += inc;

    current_frame->setLocalVariable(value_generic, index);
    current_frame->setPcByOffset(3);
}

void Interpreter::gotoInstruction()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    u1 byte1 = runtime_data_area->fetchInstruction(1);
    u1 byte2 = runtime_data_area->fetchInstruction(2);

    int16_t offset = (byte1 << 8) | byte2;

    current_frame->setPcByOffset(offset);
}

void Interpreter::if_icmpge()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic1 = current_frame->popValueFromOperandStack();
    GenericType *value_generic2 = current_frame->popValueFromOperandStack();

    if (value_generic2->data.int_value >= value_generic1->data.int_value)
    {
        u1 byte1 = runtime_data_area->fetchInstruction(1);
        u1 byte2 = runtime_data_area->fetchInstruction(2);

        int16_t offset = (byte1 << 8) | byte2;
        current_frame->setPcByOffset(offset);

        return;
    }

    current_frame->setPcByOffset(3);
}

void Interpreter::iload()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    u1 byte1 = runtime_data_area->fetchInstruction(1);
    int16_t index = (int16_t)byte1;

    //TODO: Add support for wide instruction.

    GenericType *value_generic = current_frame->getLocalVariable(index);

    current_frame->pushValueIntoOperandStack(value_generic);
    current_frame->setPcByOffset(2);
}

void Interpreter::istore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();

    //TODO: Validate if value_generic is an array

    u1 byte1 = runtime_data_area->fetchInstruction(1);
    int16_t index = (int16_t)byte1;

    //TODO: Add support for wide operator

    current_frame->setLocalVariable(value_generic, index);
    current_frame->setPcByOffset(2);
}

void Interpreter::astore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();

    //TODO: Validate if value_generic is an array

    u1 byte1 = runtime_data_area->fetchInstruction(1);
    int16_t index = (int16_t)byte1;

    //TODO: Add support for wide operator

    current_frame->setLocalVariable(value_generic, index);
    current_frame->setPcByOffset(2);
}

void Interpreter::dastore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();
    GenericType *index_generic = current_frame->popValueFromOperandStack();
    GenericType *array_generic = current_frame->popValueFromOperandStack();

    if (array_generic->data.array_value == NULL)
    {
        std::cout << "NullPointerException" << std::endl;
        exit(1);
    }

    array_generic->data.array_value->data[index_generic->data.int_value] = value_generic;

    current_frame->setPcByOffset(1);
}

void Interpreter::lastore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();

    // TODO: Validate if value_generic is long.

    GenericType *index_generic = current_frame->popValueFromOperandStack();
    GenericType *array_generic = current_frame->popValueFromOperandStack();

    if (array_generic->data.array_value == NULL)
    {
        std::cout << "NullPointerException" << std::endl;
        exit(1);
    }

    array_generic->data.array_value->data[index_generic->data.int_value] = value_generic;

    current_frame->setPcByOffset(1);
}

void Interpreter::fastore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();

    // TODO: Validate if value_generic is float.

    GenericType *index_generic = current_frame->popValueFromOperandStack();
    GenericType *array_generic = current_frame->popValueFromOperandStack();

    if (array_generic->data.array_value == NULL)
    {
        std::cout << "NullPointerException" << std::endl;
        exit(1);
    }

    array_generic->data.array_value->data[index_generic->data.int_value] = value_generic;

    std::cout << "Value: " << value_generic->data.float_value << std::endl;

    current_frame->setPcByOffset(1);
}

void Interpreter::bastore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();

    // TODO: Validate if value_generic is byte.

    GenericType *index_generic = current_frame->popValueFromOperandStack();
    GenericType *array_generic = current_frame->popValueFromOperandStack();

    if (array_generic->data.array_value == NULL)
    {
        std::cout << "NullPointerException" << std::endl;
        exit(1);
    }

    array_generic->data.array_value->data[index_generic->data.int_value] = value_generic;

    current_frame->setPcByOffset(1);
}

void Interpreter::castore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();

    // TODO: Validate if value_generic is a char.

    GenericType *index_generic = current_frame->popValueFromOperandStack();
    GenericType *array_generic = current_frame->popValueFromOperandStack();

    if (array_generic->data.array_value == NULL)
    {
        std::cout << "NullPointerException" << std::endl;
        exit(1);
    }

    array_generic->data.array_value->data[index_generic->data.int_value] = value_generic;

    current_frame->setPcByOffset(1);
}

void Interpreter::sastore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();

    // TODO: Validate if value_generic is a short.

    GenericType *index_generic = current_frame->popValueFromOperandStack();
    GenericType *array_generic = current_frame->popValueFromOperandStack();

    if (array_generic->data.array_value == NULL)
    {
        std::cout << "NullPointerException" << std::endl;
        exit(1);
    }

    array_generic->data.array_value->data[index_generic->data.int_value] = value_generic;

    current_frame->setPcByOffset(1);
}

void Interpreter::iastore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();

    // TODO: Validate if value_generic is integer.

    GenericType *index_generic = current_frame->popValueFromOperandStack();
    GenericType *array_generic = current_frame->popValueFromOperandStack();

    if (array_generic->data.array_value == NULL)
    {
        std::cout << "NullPointerException" << std::endl;
        exit(1);
    }

    array_generic->data.array_value->data[index_generic->data.int_value] = value_generic;

    current_frame->setPcByOffset(1);
}

void Interpreter::dup()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->getTopOperand();

    // TODO: Validate if value_generic is not double or long

    current_frame->pushValueIntoOperandStack(value_generic);

    current_frame->setPcByOffset(1);
}

void Interpreter::newarray()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *count_generic = current_frame->popValueFromOperandStack();

    // TODO: Validate if count_generic is an integer

    GenericType *array_default_value_generic = (GenericType *)malloc(sizeof(GenericType));

    Array *array = new Array();
    u1 array_type = runtime_data_area->fetchInstruction(1);

    // Initialize value_generic with default value of array_type
    switch (array_type)
    {
    case 4:
        array_default_value_generic->data.boolean_value = false;
        break;
    case 5:
        array_default_value_generic->data.char_value = '\u0000';
        break;
    case 6:
        array_default_value_generic->data.float_value = 0;
        break;
    case 7:
        array_default_value_generic->data.double_value = 0;
        break;
    case 8:
        array_default_value_generic->data.byte_value = 0;
        break;
    case 9:
        array_default_value_generic->data.short_value = 0;
        break;
    case 10:
        array_default_value_generic->data.int_value = 0;
        break;
    case 11:
        array_default_value_generic->data.long_value = 0;
        break;
    }

    for (int i = 0; i < count_generic->data.int_value; i++)
    {
        array->data.push_back(array_default_value_generic);
    }

    GenericType *array_generic = (GenericType *)malloc(sizeof(GenericType));
    array_generic->data.array_value = array;

    current_frame->pushValueIntoOperandStack(array_generic);
    current_frame->setPcByOffset(2);
}

void Interpreter::aastore()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();
    // TODO: Validate if value is an array reference

    GenericType *index_generic = current_frame->popValueFromOperandStack();
    // TODO: Validate if index is an integer

    GenericType *array_value_generic = current_frame->popValueFromOperandStack();
    // TODO: Validate if array is an array reference

    if (array_value_generic->data.array_value == NULL)
    {
        std::cout << "NullPointerException" << std::endl;
        exit(1);
    }

    array_value_generic->data.array_value->data[index_generic->data.int_value] = value_generic;

    current_frame->setPcByOffset(1);
}

void Interpreter::ldc()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    cp_info **constant_pool = current_frame->getConstantPool();

    u1 index = runtime_data_area->fetchInstruction(1);

    GenericType *value_generic = (GenericType *)malloc(sizeof(GenericType));

    if (constant_pool[index - 1]->tag == CONSTANT_Float)
    {
        u4 bytes = constant_pool[index - 1]->info.float_info->bytes;

        float float_value = *(float *)&bytes;
        value_generic->data.float_value = float_value;
    }
    else if (constant_pool[index - 1]->tag == CONSTANT_Integer)
    {
        value_generic->data.int_value = (int32_t)constant_pool[index - 1]->info.integer_info->bytes;
    }
    else if (constant_pool[index - 1]->tag == CONSTANT_String)
    {
        std::string string_value = runtime_data_area->getNameFromConstantPoolEntry(constant_pool[index - 1]);

        value_generic->data.string_value = new std::string(string_value);
    }

    current_frame->pushValueIntoOperandStack(value_generic);
    current_frame->setPcByOffset(2);
}

void Interpreter::tableswitch()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    u1 padding_bytes = 4 - (current_frame->getPc() + 1) % 4;

    if (padding_bytes == 4)
        padding_bytes = 0;

    u1 default_byte1 = runtime_data_area->fetchInstruction(padding_bytes + 1);
    u1 default_byte2 = runtime_data_area->fetchInstruction(padding_bytes + 2);
    u1 default_byte3 = runtime_data_area->fetchInstruction(padding_bytes + 3);
    u1 default_byte4 = runtime_data_area->fetchInstruction(padding_bytes + 4);

    u1 low_byte1 = runtime_data_area->fetchInstruction(padding_bytes + 5);
    u1 low_byte2 = runtime_data_area->fetchInstruction(padding_bytes + 6);
    u1 low_byte3 = runtime_data_area->fetchInstruction(padding_bytes + 7);
    u1 low_byte4 = runtime_data_area->fetchInstruction(padding_bytes + 8);

    u1 high_byte1 = runtime_data_area->fetchInstruction(padding_bytes + 9);
    u1 high_byte2 = runtime_data_area->fetchInstruction(padding_bytes + 10);
    u1 high_byte3 = runtime_data_area->fetchInstruction(padding_bytes + 11);
    u1 high_byte4 = runtime_data_area->fetchInstruction(padding_bytes + 12);

    int32_t default_bytes = (default_byte1 << 24) | (default_byte2 << 16) | (default_byte3 << 8) | default_byte4;
    int32_t low_bytes = (low_byte1 << 24) | (low_byte2 << 16) | (low_byte3 << 8) | low_byte4;
    int32_t high_bytes = (high_byte1 << 24) | (high_byte2 << 16) | (high_byte3 << 8) | high_byte4;

    GenericType *index_generic = current_frame->popValueFromOperandStack();
    int32_t index = index_generic->data.int_value;

    int32_t jump_offsets = high_bytes - low_bytes + 1;

    padding_bytes += 12;

    bool flag_index_found = false;

    for (int i = 0; i < jump_offsets; i++)
    {
        if (index == low_bytes)
        {
            flag_index_found = true;

            u1 jump_byte_1 = runtime_data_area->fetchInstruction(padding_bytes + 1);
            u1 jump_byte_2 = runtime_data_area->fetchInstruction(padding_bytes + 2);
            u1 jump_byte_3 = runtime_data_area->fetchInstruction(padding_bytes + 3);
            u1 jump_byte_4 = runtime_data_area->fetchInstruction(padding_bytes + 4);

            int32_t jump_bytes = (jump_byte_1 << 24) | (jump_byte_2 << 16) | (jump_byte_3 << 8) | jump_byte_4;

            current_frame->setPcByOffset(jump_bytes);

            break;
        }
        low_bytes++;
        padding_bytes += 4;
    }

    if (!flag_index_found)
        current_frame->setPcByOffset(default_bytes);
}

void Interpreter::invokestatic()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    cp_info **constant_pool = current_frame->getConstantPool();

    u1 index_byte1 = runtime_data_area->fetchInstruction(1);
    u1 index_byte2 = runtime_data_area->fetchInstruction(2);

    u2 index = (index_byte1 << 8) | index_byte2;

    cp_info *method_ref = constant_pool[index - 1];

    if (method_ref->tag != CONSTANT_Methodref)
    {
        std::cout << "Index must reference a method." << std::endl;
    }

    std::string utf8_data = runtime_data_area->getNameFromConstantPoolEntry(method_ref);

    std::string class_name = splitByToken(utf8_data, 0);
    std::string method_name = splitByToken(utf8_data, 1);
    std::string method_descriptor = splitByToken(utf8_data, 2);

    if (class_name.compare("java/lang/Object") == 0 and method_name.compare("registerNatives") == 0)
    {
        current_frame->setPcByOffset(3);
        return;
    }

    if (class_name.find("java/") == 0)
    {
        std::cout << "Invoking static method from java/* class is not allowed." << std::endl;
    }

    // Number of arguments of invoked method's operand stack and local variable array
    u2 nargs = (u2)getNumberOfArgumentsByDescriptor(method_descriptor);

    std::vector<GenericType *> method_arguments;

    for (int i = 0; i < nargs; i++)
    {
        GenericType *value_generic = current_frame->popValueFromOperandStack();

        method_arguments.push_back(value_generic);
    }

    std::reverse(method_arguments.begin(), method_arguments.end());

    ClassFile *class_file = runtime_data_area->loadClassByName(class_name);

    Frame *invoked_method_frame = new Frame(class_file, method_name, method_descriptor, method_arguments);

    // TODO: Resume execution in <clinit> method, if exists.

    runtime_data_area->frame_stack->push(invoked_method_frame);

    current_frame->setPcByOffset(3);
}

int Interpreter::getNumberOfArgumentsByDescriptor(std::string method_descriptor)
{
    int args_count = 0;

    for (long unsigned int i = 0; i < method_descriptor.length(); i++)
    {
        if (method_descriptor[i] == '(')
            continue;

        if (method_descriptor[i] == ')')
            break;

        char current_argument_type = method_descriptor[i];

        if (current_argument_type == 'D' || current_argument_type == 'J')
        {
            // ? Should double and long values include a padding? If so, increment args_count by 2.
            args_count += 1;
        }
        else if (current_argument_type == 'L')
        {
            args_count++;

            while (method_descriptor[++i] != ';')
            {
                i++;
            }
        }
        else if (current_argument_type == '[')
        {
            args_count++;

            while (method_descriptor[i] == '[')
            {
                i++;
            }

            if (method_descriptor[i] == 'L')
            {
                while (method_descriptor[i] != ';')
                {
                    i++;
                }
            }
        }
        else
        {
            args_count++;
        }
    }

    return args_count;
}

void Interpreter::iload_n(int value)
{
    GenericType *value_generic = runtime_data_area->frame_stack->getTop()->getLocalVariable(value);

    // TODO: Verify if value_generic is an integer.

    runtime_data_area->frame_stack->getTop()->pushValueIntoOperandStack(value_generic);
    runtime_data_area->frame_stack->getTop()->setPcByOffset(1);
}

void Interpreter::iload_0()
{
    iload_n(0);
}

void Interpreter::iload_1()
{
    iload_n(1);
}

void Interpreter::iload_2()
{
    iload_n(2);
}

void Interpreter::iload_3()
{
    iload_n(3);
}

void Interpreter::iconst_n(int value)
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = (GenericType *)malloc(sizeof(GenericType));

    value_generic->data.int_value = value;

    current_frame->pushValueIntoOperandStack(value_generic);

    current_frame->setPcByOffset(1);
}

void Interpreter::iconst_m1()
{
    iconst_n(-1);
}

void Interpreter::iconst_0()
{
    iconst_n(0);
}

void Interpreter::iconst_1()
{
    iconst_n(1);
}

void Interpreter::iconst_2()
{
    iconst_n(2);
}

void Interpreter::iconst_3()
{
    iconst_n(3);
}

void Interpreter::iconst_4()
{
    iconst_n(4);
}

void Interpreter::iconst_5()
{
    iconst_n(5);
}

void Interpreter::fconst_0()
{
    fconst_n(0);
}

void Interpreter::fconst_1()
{
    fconst_n(1);
}

void Interpreter::fconst_2()
{
    fconst_n(2);
}

void Interpreter::fconst_n(int value)
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = (GenericType *)malloc(sizeof(GenericType));

    value_generic->data.float_value = value;

    current_frame->pushValueIntoOperandStack(value_generic);

    current_frame->setPcByOffset(1);
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
        // TODO: Throw exception.
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
    GenericType *value_generic = current_frame->popValueFromOperandStack();

    // TODO: Validate if is double

    current_frame->setLocalVariable(value_generic, index);

    current_frame->setPcByOffset(1);
}

void Interpreter::astore_0()
{
    astore_n(0);
}

void Interpreter::astore_1()
{
    astore_n(1);
}

void Interpreter::astore_2()
{
    astore_n(2);
}

void Interpreter::astore_3()
{
    astore_n(3);
}

void Interpreter::astore_n(int index)
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    GenericType *value_generic = current_frame->popValueFromOperandStack();

    // TODO: Validate if is reference

    current_frame->setLocalVariable(value_generic, index);

    current_frame->setPcByOffset(1);
}

void Interpreter::aaload()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *int_value_generic = current_frame->popValueFromOperandStack();
    // TODO: Validate if int_value_generic is int

    GenericType *array_value_generic = current_frame->popValueFromOperandStack();
    // TODO: Validate if array_value_generic is array*

    if (array_value_generic->data.array_value == NULL)
    {
        std::cout << "NullPointerException" << std::endl;
    }

    // TODO: Validate other properties and throw associated exceptions

    // Push array element at index referenced by int_value_generic into operand stack
    current_frame->pushValueIntoOperandStack(array_value_generic->data.array_value->data[int_value_generic->data.int_value]);

    current_frame->setPcByOffset(1);
}

void Interpreter::dload_0()
{
    dload_n(0);
}

void Interpreter::dload_1()
{
    dload_n(1);
}

void Interpreter::dload_2()
{
    dload_n(2);
}

void Interpreter::dload_3()
{
    dload_n(3);
}

void Interpreter::dload_n(int index)
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value = current_frame->getLocalVariable(index);

    current_frame->pushValueIntoOperandStack(value);

    current_frame->setPcByOffset(1);
}

void Interpreter::aload_0()
{
    aload_n(0);
}

void Interpreter::aload_1()
{
    aload_n(1);
}

void Interpreter::aload_2()
{
    aload_n(2);
}

void Interpreter::aload_3()
{
    aload_n(3);
}

void Interpreter::aload_n(int index)
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value = current_frame->getLocalVariable(index);

    current_frame->pushValueIntoOperandStack(value);

    current_frame->setPcByOffset(1);
}

void Interpreter::dadd()
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    GenericType *value_generic_1 = current_frame->popValueFromOperandStack();
    GenericType *value_generic_2 = current_frame->popValueFromOperandStack();

    GenericType *result = (GenericType *)malloc(sizeof(GenericType));

    result->data.double_value = value_generic_1->data.double_value + value_generic_2->data.double_value;
    current_frame->pushValueIntoOperandStack(result);

    current_frame->setPcByOffset(1);
}

void Interpreter::dsub()
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    GenericType *value_generic_1 = current_frame->popValueFromOperandStack();
    GenericType *value_generic_2 = current_frame->popValueFromOperandStack();

    GenericType *result = (GenericType *)malloc(sizeof(GenericType));

    result->data.double_value = value_generic_2->data.double_value - value_generic_1->data.double_value;
    current_frame->pushValueIntoOperandStack(result);

    current_frame->setPcByOffset(1);
}

void Interpreter::dmul()
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    GenericType *value_generic_1 = current_frame->popValueFromOperandStack();
    GenericType *value_generic_2 = current_frame->popValueFromOperandStack();

    GenericType *result = (GenericType *)malloc(sizeof(GenericType));

    result->data.double_value = value_generic_1->data.double_value * value_generic_2->data.double_value;
    current_frame->pushValueIntoOperandStack(result);

    current_frame->setPcByOffset(1);
}

void Interpreter::ddiv()
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    GenericType *value_generic_1 = current_frame->popValueFromOperandStack();
    GenericType *value_generic_2 = current_frame->popValueFromOperandStack();

    GenericType *result = (GenericType *)malloc(sizeof(GenericType));

    result->data.double_value = value_generic_2->data.double_value / value_generic_1->data.double_value;
    current_frame->pushValueIntoOperandStack(result);

    current_frame->setPcByOffset(1);
}

void Interpreter::dneg()
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    GenericType *value_generic_1 = current_frame->popValueFromOperandStack();

    GenericType *result = (GenericType *)malloc(sizeof(GenericType));

    result->data.double_value = -value_generic_1->data.double_value;
    current_frame->pushValueIntoOperandStack(result);

    current_frame->setPcByOffset(1);
}

void Interpreter::drem()
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    GenericType *value_generic_1 = current_frame->popValueFromOperandStack();
    GenericType *value_generic_2 = current_frame->popValueFromOperandStack();

    GenericType *result = (GenericType *)malloc(sizeof(GenericType));

    result->data.double_value = value_generic_1->data.double_value - ((u4)value_generic_2->data.double_value / (u4)value_generic_1->data.double_value) * value_generic_2->data.double_value;
    current_frame->pushValueIntoOperandStack(result);

    current_frame->setPcByOffset(1);
}

void Interpreter::getstatic()
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    cp_info **constant_pool = current_frame->getConstantPool();

    u1 index_byte1 = runtime_data_area->fetchInstruction(1);
    u1 index_byte2 = runtime_data_area->fetchInstruction(2);

    u2 index = (index_byte1 << 8) | index_byte2;

    // Index must point to a fieldref in constant pool
    if (constant_pool[index - 1]->tag != CONSTANT_Fieldref)
    {
        std::cout << "getstatic instruction is accessing an invalid entry in constant pool." << std::endl;
        exit(1);
    }

    std::string utf8_data = runtime_data_area->getNameFromConstantPoolEntry(constant_pool[index - 1]);

    std::string class_name = splitByToken(utf8_data, 0);
    std::string field_name = splitByToken(utf8_data, 1);
    std::string field_descriptor = splitByToken(utf8_data, 2);

    // java/io/PrintStream fields won't be loaded into operand stack
    if (class_name == "java/lang/System" and field_descriptor == "Ljava/io/PrintStream;")
    {
        current_frame->setPcByOffset(3);
        return;
    }

    ClassFile *class_file = runtime_data_area->loadClassByName(class_name);

    if (!fetchFieldInSuperClasses(field_name, class_file))
    {
        std::cout << "NoSuchFieldError" << std::endl;
    }

    //TODO: Load field into operand stack
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

void Interpreter::invokevirtual()
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    cp_info **constant_pool = current_frame->getConstantPool();

    u1 index_byte1 = runtime_data_area->fetchInstruction(1);
    u1 index_byte2 = runtime_data_area->fetchInstruction(2);

    u2 method_index = (index_byte1 << 8) | index_byte2;

    if (constant_pool[method_index - 1]->tag != CONSTANT_Methodref)
    {
        std::cout << "Index must be a method reference!" << std::endl;
        exit(1);
    }

    std::string method_info = runtime_data_area->getNameFromConstantPoolEntry(constant_pool[method_index - 1]);

    std::string class_name = splitByToken(method_info, 0);
    std::string method_name = splitByToken(method_info, 1);
    std::string method_descriptor = splitByToken(method_info, 2);

    if (class_name.compare("java/io/PrintStream") == 0)
    {
        if (method_name.compare("print") == 0 or method_name.compare("println") == 0)
        {
            printGenericTypeByDescriptor(method_descriptor);

            if (method_name.compare("println") == 0)
                std::cout << std::endl;
        }
    }

    //TODO: Implement other invokevirtual use cases

    current_frame->setPcByOffset(3);
}

void Interpreter::bipush()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    u1 byte = runtime_data_area->fetchInstruction(1);

    int32_t extended_byte = (int32_t) signed(byte);

    GenericType *int_generic = (GenericType *)malloc(sizeof(GenericType));
    int_generic->data.int_value = extended_byte;

    current_frame->pushValueIntoOperandStack(int_generic);

    current_frame->setPcByOffset(2);
}

void Interpreter::sipush()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    u1 byte1 = runtime_data_area->fetchInstruction(1);
    u1 byte2 = runtime_data_area->fetchInstruction(2);

    u2 short_value = (byte1 << 8) | byte2;

    int32_t extended_short = (int32_t) signed(short_value);

    GenericType *int_generic = (GenericType *)malloc(sizeof(GenericType));
    int_generic->data.int_value = extended_short;

    current_frame->pushValueIntoOperandStack(int_generic);

    current_frame->setPcByOffset(3);
}

void Interpreter::multianewarray()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();
    cp_info **constant_pool = current_frame->getConstantPool();

    u1 index_byte1 = runtime_data_area->fetchInstruction(1);
    u1 index_byte2 = runtime_data_area->fetchInstruction(2);
    u1 dimensions = (u4)runtime_data_area->fetchInstruction(3);

    u2 index = (index_byte1 << 8) | index_byte2;

    if (constant_pool[index - 1]->tag != CONSTANT_Class)
    {
        std::cout << "Index must reference a class in constant pool." << std::endl;
        exit(1);
    }

    std::string utf8_data = runtime_data_area->getNameFromConstantPoolEntry(constant_pool[index - 1]);
    std::string class_name = splitByToken(utf8_data, 0);

    char multianewarrayType = getMultianewarrayTypeByClassName(class_name);

    std::vector<int32_t> dimension_array;

    for (int i = 0; i < dimensions; i++)
    {
        GenericType *value_generic = current_frame->popValueFromOperandStack();
        dimension_array.push_back(value_generic->data.int_value);
    }

    GenericType *value_generic = (GenericType *)malloc(sizeof(GenericType));
    Array *array = buildMultianewarray(dimensions - 1, multianewarrayType, dimension_array);

    value_generic->data.array_value = array;

    current_frame->pushValueIntoOperandStack(value_generic);

    current_frame->setPcByOffset(4);
}

Array *Interpreter::buildMultianewarray(int index, char type, std::vector<int> dimension_array)
{
    Array *array = new Array();
    array->data = std::vector<GenericType *>(dimension_array[index]);

    // End of recursion
    if (index == 0)
    {
        for (int i = 0; i < dimension_array[index]; i++)
        {
            GenericType *int_value_generic = (GenericType *)malloc(sizeof(GenericType));
            int_value_generic->data.int_value = 0;

            // TODO: Validate type
            array->data.at(i) = int_value_generic;
        }

        return array;
    }

    for (int i = 0; i < dimension_array[index]; i++)
    {
        GenericType *array_value_generic = (GenericType *)malloc(sizeof(GenericType));
        array_value_generic->data.array_value = buildMultianewarray(index - 1, type, dimension_array);

        array->data.at(i) = array_value_generic;
    }

    return array;
}

char Interpreter::getMultianewarrayTypeByClassName(std::string class_name)
{
    int i = 0;

    // Skip all '[' in class name
    while (class_name[i] == '[')
        i++;

    char type = class_name[i];

    if (type == 'L' and class_name.find("java/lang/String") == std::string::npos)
    {
        // Remove ']', ')' and ';' from class name,
        runtime_data_area->loadClassByName(class_name.substr(i + 1, class_name.size() - i - 2));
    }

    return type;
}

void Interpreter::printGenericTypeByDescriptor(std::string descriptor)
{
    GenericType *value = runtime_data_area->frame_stack->getTop()->popValueFromOperandStack();

    if (descriptor.compare("(B)V") == 0)
    {
        std::cout << value->data.byte_value;
    }
    else if (descriptor.compare("(C)V") == 0)
    {

        std::cout << value->data.char_value;
    }
    else if (descriptor.compare("(D)V") == 0)
    {
        std::cout.precision(std::numeric_limits<double>::max_digits10);
        std::cout << value->data.double_value;
    }
    else if (descriptor.compare("(F)V") == 0)
    {
        std::cout << value->data.float_value;
    }
    else if (descriptor.compare("(I)V") == 0)
    {
        std::cout << value->data.int_value;
    }

    else if (descriptor.compare("(J)V") == 0)
    {
        std::cout << value->data.long_value;
    }
    else if (descriptor.compare("(Ljava/lang/String;)V") == 0)
    {
        std::cout << *value->data.string_value;
    }
    else if (descriptor.compare("(S)V") == 0)
    {
        std::cout << value->data.short_value;
    }
    else if (descriptor.compare("(Z)V") == 0)
    {
        std::cout << value->data.boolean_value;
    }
    else
    {
        std::cout << "Unsupported type";
    }
}

void Interpreter::returnInstruction()
{
    runtime_data_area->frame_stack->pop();
}

void Interpreter::ireturn()
{
    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value_generic = current_frame->popValueFromOperandStack();

    runtime_data_area->frame_stack->pop();

    Frame *new_current_frame = runtime_data_area->frame_stack->getTop();
    new_current_frame->pushValueIntoOperandStack(value_generic);
}

bool Interpreter::fetchFieldInSuperClasses(std::string field_name, ClassFile *class_file)
{
    bool field_found = false;

    while (class_file->super_class != 0 and !field_found)
    {
        if (!class_file->fieldExists(field_name))
        {
            std::string super_class_name = class_file->getNameFromConstantPoolEntry(class_file->constant_pool[class_file->super_class - 1]);
            super_class_name = splitByToken(super_class_name, 0);

            class_file = runtime_data_area->loadClassByName(super_class_name);
        }
        else
        {
            field_found = true;
        }
    }

    return field_found;
}