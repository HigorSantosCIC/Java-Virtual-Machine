#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <stdio.h>
#include <runtime_data_area.hpp>
#include <generic_type.hpp>
#include <math.h>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

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

    void tableswitch();

    void iload_n(int value);
    void iload_0();
    void iload_1();
    void iload_2();
    void iload_3();

    void iconst_n(int value);
    void iconst_m1();
    void iconst_0();
    void iconst_1();
    void iconst_2();
    void iconst_3();
    void iconst_4();
    void iconst_5();

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
    /**
     * @brief (0x67): Subtract two doubles from operand stack.
     */
    void dsub();
    /**
     * @brief (0x6b): Multiply two doubles from operand stack.
     */
    void dmul();
    /**
     * @brief (0x6f): Divide two doubles from operand stack.
     */
    void ddiv();
    /**
     * @brief (0x73): Negate double from operand stack.
     */
    void dneg();
    /**
     * @brief (0x73): Remainder between two doubles division.
     */
    void drem();

    void getstatic();

    void invokevirtual();
    void invokestatic();

    void returnInstruction();
    void ireturn();

    void printGenericTypeByDescriptor(std::string method_descriptor);

    /**
     * @brief Count the number of arguments in a method descriptor.
     * 
     * Credits: https://github.com/ArthurEmidio/jvm
     * 
     * @param method_descriptor String containing the method descriptor to be analyzed.
     * @return (int) number of arguments in method descriptor.
     */
    int getNumberOfArgumentsByDescriptor(std::string method_descriptor);

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
