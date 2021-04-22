#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <stdio.h>
#include <runtime_data_area.hpp>
#include <generic_type.hpp>
#include "array.hpp"
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

    void ldc();

    /**
     * @brief (0x14): Push long or double from run-time constant pool.
     */
    void ldc2_w();

    void tableswitch();

    void aload();

    /**
     * @brief Common code for instructions (aaload, baload, caload...)
     */
    void type_aload();
    void aaload();
    void baload();
    void caload();
    void daload();
    void faload();
    void iaload();
    void laload();
    void saload();

    void iload();
    void iload_n(int value);
    void iload_0();
    void iload_1();
    void iload_2();
    void iload_3();

    void istore();

    void iconst_n(int value);
    void iconst_m1();
    void iconst_0();
    void iconst_1();
    void iconst_2();
    void iconst_3();
    void iconst_4();
    void iconst_5();

    void fconst_0();
    void fconst_1();
    void fconst_2();
    void fconst_n(int value);

    void astore();
    void astore_0();
    void astore_1();
    void astore_2();
    void astore_3();
    void astore_n(int index);

    void aload_0();
    void aload_1();
    void aload_2();
    void aload_3();
    void aload_n(int index);

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

    void dup();
    void dup2();

    void iinc();

    /**
     * @brief (0x4f): Store into integer array.
     */
    void iastore();
    /**
     * @brief (0x50): Store into long array.
     */
    void lastore();
    /**
     * @brief (0x51): Store into float array.
     */
    void fastore();
    /**
     * @brief (0x52): Store into double array.
     */
    void dastore();
    /**
     * @brief (0x53): Store into array of arrays.
     */
    void aastore();
    /**
     * @brief (0x54): Store into byte array.
     */
    void bastore();
    /**
     * @brief (0x55): Store into char array.
     */
    void castore();
    /**
     * @brief (0x56): Store into short array.
     */
    void sastore();
    /**
     * @brief (0x60): Add two integers from operand stack.
     */
    void iadd();

    void bipush();

    void sipush();

    void getstatic();

    void newarray();

    void arraylength();

    void multianewarray();

    void if_icmpge();

    void gotoInstruction();

    void invokevirtual();
    void invokestatic();

    void returnInstruction();
    void ireturn();

    void printGenericTypeByDescriptor(std::string method_descriptor);

    /**
     * @brief (0xc5): Recursively build a multianewarray.
     * 
     * If index > 0, all Array elements will be a reference to a subarray.
     * 
     * If index = 0, all Array elements will be initialized with value 0.
     
     * @param dimension_array A vector that counts dimensions of each multianewarray level.
     * @param index Index that references a position in dimension_array, indicating dimension count of current Array
     * @param type type of data of the final Array.
     */
    Array *buildMultianewarray(int index, char type, std::vector<int> dimension_array);

    char getMultianewarrayTypeByClassName(std::string class_name);
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
