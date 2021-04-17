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
    while (!runtime_data_area->frame_stack->isEmpty())
    {
        u1 instruction = runtime_data_area->fetchInstruction(0);

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
        case 0x14:
            ldc2_w();
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
        default:
            return;
            break;
        }
    }
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

void Interpreter::dload_n(int index)
{

    Frame *current_frame = runtime_data_area->frame_stack->getTop();

    GenericType *value = current_frame->getLocalVariable(index);

    current_frame->pushValueIntoOperandStack(value);

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
        std::cout << value->data.string_value;
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
