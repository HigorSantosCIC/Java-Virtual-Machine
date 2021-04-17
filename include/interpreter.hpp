#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <stdio.h>
#include <runtime_data_area.hpp>
#include <generic_type.hpp>
#include <math.h>
#include <sstream>
#include <string>

class Interpreter
{
public:
    Interpreter(RuntimeDataArea *p_runtime_data_area);
    ~Interpreter();

    void run();

private:
    RuntimeDataArea *runtime_data_area;

    // Indicates if the next instruction to be executed is wide. This affects the execution flow of the instruction.
    bool isInstructionWide;

    /**
     * @brief (0x14): Push long or double from run-time constant pool.
     */
    void ldc2_w();

    void dstore_0();
    void dstore_1();
    void dstore_2();
    void dstore_3();
    void dstore_n(int index);

    void dload_0();
    void dload_1();
    void dload_2();
    void dload_3();
    void dload_n(int index);

    /**
     * @brief (0x63): Add two doubles from operand stack.
     */
    void dadd();

    void getstatic();

    // ? Where to save splitByToken method? Consider creater a StringUtils namespace.
    std::string splitByToken(std::string str, int position);

    // ! Review and test
    /**
     * @brief Search field_name in super classes of class_file. 
     * The method is executed until the current super class has no parent (class_file->super_class = 0).
     * As collateral effect, all super classes are loaded into method area until field is found.
     * 
     * @param field_name Name of field to be fetched
     * @param class_file Base class file, from which the super classes will be searched.
     * @return (true) if field is found
     * @return (false) if field is not found
     */
    bool fetchFieldInSuperClasses(std::string field_name, ClassFile *class_file);
};

#endif
