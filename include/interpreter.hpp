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

    /* TODO:

    19 (0x13) ldc_w
    22 (0x16) lload
    23 (0x17) fload
    24 (0x18) dload
    55 (0x37) lstore
    56 (0x38) fstore
    57 (0x39) dstore
    168 (0xa8) jsr
    169 (0xa9) ret
    171 (0xab) lookupswitch
    179 (0xb3) putstatic
    180 (0xb4) getfield
    181 (0xb5) putfield
    183 (0xb7) invokespecial
    185 (0xb9) invokeinterface
    186 (0xba) invokedynamic
    187 (0xbb) new
    189 (0xbd) anewarray
    191 (0xbf) athrow
    192 (0xc0) checkcast
    193 (0xc1) instanceof
    194 (0xc2) monitorenter
    195 (0xc3) monitorexit
    196 (0xc4) wide
    201 (0xc9) jsr_w
*/

    void goto_w();

    /**
     * @brief (0x00): Do nothing.
     */
    void nop();

    /**
     * @brief (0x01): Push the null object reference onto the operand stack.
     */
    void aconst_null();

    /**
     * @brief (iconst_<n>): Push the int constant <n> (-1, 0, 1, 2, 3, 4 or 5) onto the operand stack.
     */
    void iconst_n(int32_t value);

    /**
     * @brief (0x02): Push the int constant -1 onto the operand stack.
     */
    void iconst_m1();

    /**
     * @brief (0x03): Push the int constant 0 onto the operand stack.
     */
    void iconst_0();

    /**
     * @brief (0x04): Push the int constant 1 onto the operand stack.
     */
    void iconst_1();

    /**
     * @brief (0x05): Push the int constant 2 onto the operand stack.
     */
    void iconst_2();

    /**
     * @brief (0x06): Push the int constant 3 onto the operand stack.
     */
    void iconst_3();

    /**
     * @brief (0x07): Push the int constant 4 onto the operand stack.
     */
    void iconst_4();

    /**
     * @brief (0x08): Push the int constant 5 onto the operand stack.
     */
    void iconst_5();

    /**
     * @brief (lconst_<n>): Push the long constant <n> (0 or 1) onto the operand stack.
     */
    void lconst_n(int64_t value);

    /**
     * @brief (0x09): Push the long constant 0 onto the operand stack.
     */
    void lconst_0();

    /**
     * @brief (0x0a): Push the long constant 1 onto the operand stack.
     */
    void lconst_1();

    /**
     * @brief (fconst_<n>): Push the float constant <n> (0.0, 1.0, or 2.0) onto the operand stack.
     */
    void fconst_n(float value);

    /**
     * @brief (0x0b): Push the float constant 0.0 onto the operand stack.
     */
    void fconst_0();

    /**
     * @brief (0x0c): Push the float constant 1.0 onto the operand stack.
     */
    void fconst_1();

    /**
     * @brief (0x0d): Push the float constant 2.0 onto the operand stack.
     */
    void fconst_2();

    /**
     * @brief (dconst_<n>): Push the double constant <n> (0.0 or 1.0) onto the operand stack.
     */
    void dconst_n(double value);

    /**
     * @brief (0x0e): Push the double constant 0.0 onto the operand stack.
     */
    void dconst_0();

    /**
     * @brief (0x0f): Push the double constant 1.0 onto the operand stack.
     */
    void dconst_1();

    /**
     * @brief (0x10): Push byte onto the operand stack.
     */
    void bipush();

    /**
     * @brief (0x11): Push short onto the operand stack.
     */
    void sipush();

    /**
     * @brief (0x12): Push item from run-time constant pool.
     */
    void ldc();

    /**
     * @brief (0x13): Push item from run-time constant pool.
     */
    //void ldc_w();

    /**
     * @brief (0x14): Push long or double from run-time constant pool (wide index).
     */
    void ldc2_w();

    /**
     * @brief (0x15): Load int from local variable.
     */
    void iload();

    /**
     * @brief (0x16): Load long from local variable.
     */
    //void lload();

    /**
     * @brief (0x17): Load float from local variable.
     */
    //void fload();

    /**
     * @brief (0x18): Load double from local variable.
     */
    //void dload();

    /**
     * @brief (0x19): Load reference from local variable.
     */
    void aload();

    /**
     * @brief (iload_<n>): Load int from local variable, where <n> must be an index 
     * into the local variable array of the current frame.
     */
    void iload_n(int value);

    /**
     * @brief (0x1a): Load int from local variable where <n> equals 0.
     */
    void iload_0();

    /**
     * @brief (0x1b): Load int from local variable where <n> equals 1.
     */
    void iload_1();

    /**
     * @brief (0x1c): Load int from local variable where <n> equals 2.
     */
    void iload_2();

    /**
     * @brief (0x1d): Load int from local variable where <n> equals 3.
     */
    void iload_3();

    /**
     * @brief (lload_<n>): Load long from local variable, where both <n> and <n+1> must be indices
     * into the local variable array of the current frame.
     */
    void lload_n(int value);

    /**
     * @brief (0x1e): Load long from local variable where <n> equals 0.
     */
    void lload_0();

    /**
     * @brief (0x1f): Load long from local variable where <n> equals 1.
     */
    void lload_1();

    /**
     * @brief (0x20): Load long from local variable where <n> equals 2.
     */
    void lload_2();

    /**
     * @brief (0x21): Load long from local variable where <n> equals 3.
     */
    void lload_3();

    /**
     * @brief (fload_<n>): Load float from local variable where <n> must be an index
     * into the local variable array of the current frame.
     */
    void fload_n(int value);

    /**
     * @brief (0x22): Load float from local variable where <n> equals 0.
     */
    void fload_0();

    /**
     * @brief (0x23): Load float from local variable where <n> equals 1.
     */
    void fload_1();

    /**
     * @brief (0x24): Load float from local variable where <n> equals 2.
     */
    void fload_2();

    /**
     * @brief (0x25): Load float from local variable where <n> equals 3.
     */
    void fload_3();

    /**
     * @brief (dload_<n>): Load double from local variable, where both <n> and <n+1> must be indices
     * into the local variable array of the current frame.
     */
    void dload_n(int index);

    /**
     * @brief (0x26): Load double from local variable where <n> equals 0.
     */
    void dload_0();

    /**
     * @brief (0x27): Load double from local variable where <n> equals 1.
     */
    void dload_1();

    /**
     * @brief (0x28): Load double from local variable where <n> equals 2.
     */
    void dload_2();

    /**
     * @brief (0x29): Load double from local variable where <n> equals 3.
     */
    void dload_3();

    /**
     * @brief (aload_<n>): Load reference from local variable, where <n> must be a index
     * into the local variable array of the current frame.
     */
    void aload_n(int index);

    /**
     * @brief (0x2a): Load reference from local variable where <n> equals 0.
     */
    void aload_0();

    /**
     * @brief (0x2b): Load reference from local variable where <n> equals 1.
     */
    void aload_1();

    /**
     * @brief (0x2c): Load reference from local variable where <n> equals 2.
     */
    void aload_2();

    /**
     * @brief (0x2d): Load reference from local variable where <n> equals 3.
     */
    void aload_3();

    /**
     * @brief (type_aload): Common code for instructions (aaload, baload, caload...)
     */
    void type_aload();

    /**
     * @brief (0x2e): Load int from array.
     */
    void iaload();

    /**
     * @brief (0x2f): Load long from array.
     */
    void laload();

    /**
     * @brief (0x30): Load float from array.
     */
    void faload();

    /**
     * @brief (0x31): Load double from array.
     */
    void daload();

    /**
     * @brief (032): Load reference from array.
     */
    void aaload();

    /**
     * @brief (0x33): Load byte or boolean from array.
     */
    void baload();

    /**
     * @brief (0x34): Load char from array.
     */
    void caload();

    /**
     * @brief (0x35): Load short from array.
     */
    void saload();

    /**
     * @brief (0x36): Store int into local variable.
     */
    void istore();

    /**
     * @brief (0x37): Store long into local variable.
     */
    //void lstore();

    /**
     * @brief (0x38): Store float into local variable.
     */
    //void fstore();

    /**
     * @brief (0x39): Store double into local variable.
     */
    //void dstore();

    /**
     * @brief (0x3a): Store reference into local variable.
     */
    void astore();

    /**
     * @brief (istore_<n>): Store int into local variable, where <n> must be a index
     * into the local variable array of the current frame.
     */

    //não usar no switch
    void istore_n(int index);

    /**
     * @brief (0x3b): Store int into local variable (n=0).
     */
    void istore_0();

    /**
     * @brief (0x3c): Store int into local variable (n=1).
     */
    void istore_1();

    /**
     * @brief (0x3d): Store int into local variable (n=2).
     */
    void istore_2();

    /**
     * @brief (0x3e): Store int into local variable (n=3).
     */
    void istore_3();

    /**
     * @brief (lstore_<n>): Store long into local variable, where <n> and <n>+1 must be indices
     * into the local variable array of the current frame.
     */

    //não usar no switch
    void lstore_n(int index);

    /**
     * @brief (0x3f): Store long into local variable (n=0).
     */
    void lstore_0();

    /**
     * @brief (0x40): Store long into local variable (n=1).
     */
    void lstore_1();

    /**
     * @brief (0x41): Store long into local variable (n=2).
     */
    void lstore_2();

    /**
     * @brief (0x42): Store long into local variable (n=3).
     */
    void lstore_3();

    /**
     * @brief (fstore_<n>): Store float into local variable, where <n> must be a index
     * into the local variable array of the current frame.
     */

    //não usar no switch
    void fstore_n(int index);

    /**
     * @brief (0x43): Store float into local variable (n=0).
     */
    void fstore_0();

    /**
     * @brief (0x44): Store float into local variable (n=1).
     */
    void fstore_1();

    /**
     * @brief (0x45): Store float into local variable (n=2).
     */
    void fstore_2();

    /**
     * @brief (0x46): Store float inuto local variable (n=3).u
     */
    void fstore_3();

    /**
     * @brief (dstore_<n>): Store double into local variable, where <n> and <n>+1 must be indices
     * into the local variable array of the current frame.
     */
    void dstore_n(int index);

    /**
     * @brief (0x47): Store double into local variable where <n> equals 0.
     */
    void dstore_0();

    /**
     * @brief (0x48): Store double into local variable where <n> equals 1.
     */
    void dstore_1();

    /**
     * @brief (0x49): Store double into local variable where <n> equals 2.
     */
    void dstore_2();

    /**
     * @brief (0x4a): Store double into local variable where <n> equals 3.
     */
    void dstore_3();

    /**
     * @brief (astore_<n>): Store reference into local variable, where <n> must be a index
     * into the local variable array of the current frame.
     */
    void astore_n(int index);

    /**
     * @brief (0x4b): Store reference into local variable where <n> equals 0.
     */
    void astore_0();

    /**
     * @brief (0x4c): Store reference into local variable where <n> equals 1.
     */
    void astore_1();

    /**
     * @brief (0x4d): Store reference into local variable where <n> equals 2.
     */
    void astore_2();

    /**
     * @brief (0x4e): Store reference into local variable where <n> equals 3.
     */
    void astore_3();

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
     * @brief (0x57): Pop the top value from the operand stack.
     */
    void pop();

    /**
     * @brief (0x58): Pop the top one or two operand stack values.
     */
    void pop2();

    /**
     * @brief (0x59): Duplicate the top value on the operand stack and 
     * push the duplicated value onto the operand stack.
     */
    void dup();

    /**
     * @brief (0x5a): Duplicate the top value on the operand stack and 
     * insert the duplicated value two values down in the operand stack.
     */
    void dup_x1();

    /**
     * @brief (0x5b): Duplicate the top value on the operand stack and 
     * insert the duplicated value two or three values down in the operand stack.
     */
    void dup_x2();

    /**
     * @brief (0x5c): Duplicate the top one or two values on the operand stack and 
     * push the duplicated value or values back onto the operand stack in the original order.
     */
    void dup2();

    /**
     * @brief (0x5d): Duplicate the top one or two values on the operand stack and 
     * insert the duplicated values, in the original order, 
     * one value beneath the original value or values in the operand stack.
     */
    void dup2_x1();

    /**
     * @brief (0x5e): Duplicate the top one or two values on the operand stack and 
     * insert the duplicated values, in the original order, into the operand stack.
     */
    void dup2_x2();

    /**
     * @brief (0x5f): Swap the top two values on the operand stack.
     */
    void swap();

    /**
     * @brief (0x60): Add two integer values from operand stack.
     */
    void iadd();

    /**
     * @brief (0x61): Add two long values from operand stack.
     */
    void ladd();

    /**
     * @brief (0x62): Add two float values from operand stack.
     */
    void fadd();

    /**
     * @brief (0x63): Add two doubles values from operand stack.
     */
    void dadd();

    /**
     * @brief (0x64): Subtract two integer values from operand stack.
     */
    void isub();

    /**
     * @brief (0x65): Subtract two long values from operand stack.
     */
    void lsub();

    /**
     * @brief (0x66): Subtract two float values from operand stack.
     */
    void fsub();

    /**
     * @brief (0x67): Subtract two double values from operand stack.
     */
    void dsub();

    /**
     * @brief (0x68): Multiply two integer values from operand stack.
     */
    void imul();

    /**
     * @brief (0x69): Multiply two long values from operand stack.
     */
    void lmul();

    /**
     * @brief (0x6a): Multiply two float values from operand stack.
     */
    void fmul();

    /**
     * @brief (0x6b): Multiply two doubles from operand stack.
     */
    void dmul();

    /**
     * @brief (0x6c): Divide two integer values from operand stack.
     */
    void idiv();

    /**
     * @brief (0x6d): Divide two long values from operand stack.
     */
    void ldiv();

    /**
     * @brief (0x6e): Divide two float values from operand stack.
     */
    void fdiv();

    /**
     * @brief (0x6f): Divide two double values from operand stack.
     */
    void ddiv();

    /**
     * @brief (0x70): Remainder between two integer values division.
     */
    void irem();

    /**
     * @brief (0x71): Remainder between two long values division.
     */
    void lrem();

    /**
     * @brief (0x72): Remainder between two float values division.
     */
    void frem();

    /**
     * @brief (0x73): Remainder between two double values division.
     */
    void drem();

    /**
     * @brief (0x74): Negate integer value from operand stack.
     */
    void ineg();

    /**
     * @brief (0x75): Negate long value from operand stack.
     */
    void lneg();

    /**
     * @brief (0x76): Negate float value from operand stack.
     */
    void fneg();

    /**
     * @brief (0x77): Negate double value from operand stack.
     */
    void dneg();

    /**
     * @brief (0x78): Shift left integer value.
     */
    void ishl();

    /**
     * @brief (0x79): Shift left long value.
     */
    void lshl();

    /**
     * @brief (0x7a): Arithmetic shift right integer value.
     */
    void ishr();

    /**
     * @brief (0x7b): Arithmetic shift right long value.
     */
    void lshr();

    /**
     * @brief (0x7c): Logical shift right int value.
     */
    void iushr();

    /**
     * @brief (0x7d): Logical shift right long value.
     */
    void lushr();

    /**
     * @brief (0x7e): Boolean operation AND on integer values.
     */
    void iand();

    /**
     * @brief (0x7f): Boolean operation AND on long values.
     */
    void land();

    /**
     * @brief (0x80): Boolean operation OR on integer values.
     */
    void ior();

    /**
     * @brief (0x81): Boolean operation OR on long values.
     */
    void lor();

    /**
     * @brief (0x82): Boolean operation XOR on integer values.
     */
    void ixor();

    /**
     * @brief (0x83): Boolean operation XOR on long values.
     */
    void lxor();

    /**
     * @brief (0x84): Increment local variable by constant value.
     */
    void iinc();

    /**
     * @brief (0x85): Convert integer to long.
     */
    void i2l();

    /**
     * @brief (0x86): Convert integer to float.
     */
    void i2f();

    /**
     * @brief (0x87): Convert integer to double.
     */
    void i2d();

    /**
     * @brief (0x88): Convert long to integer.
     */
    void l2i();

    /**
     * @brief (0x89): Convert long to float.
     */
    void l2f();

    /**
     * @brief (0x8a): Convert long to double.
     */
    void l2d();

    /**
     * @brief (0x8b): Convert float to integer.
     */
    void f2i();

    /**
     * @brief (0x8c): Convert float to long.
     */
    void f2l();

    /**
     * @brief (0x8d): Convert float to double.
     */
    void f2d();

    /**
     * @brief (0x8e): Convert double to integer.
     */
    void d2i();

    /**
     * @brief (0x8f): Convert double to long.
     */
    void d2l();

    /**
     * @brief (0x90): Convert double to float.
     */
    void d2f();

    /**
     * @brief (0x91): Convert integer to byte.
     */
    void i2b();

    /**
     * @brief (0x92): Convert integer to char.
     */
    void i2c();

    /**
     * @brief (0x93): Convert integer to short.
     */
    void i2s();

    /**
     * @brief (0x94): Compare long values and push respective integer onto the operand stack.
     */
    void lcmp();

    /**
     * @brief (0x95): Compare float values and push respective integer onto the operand stack.
     */
    void fcmpl();

    /**
     * @brief (0x96): Compare float values and push respective integer onto the operand stack.
     */
    void fcmpg();

    /**
     * @brief (0x97): Compare double values and push respective integer onto the operand stack.
     */
    void dcmpl();

    /**
     * @brief (0x98): Compare double values and push respective integer onto the operand stack.
     */
    void dcmpg();

    /**
     * @brief (0x99): Branch if int comparison with zero succeeds (value = zero).
     */
    void ifeq();

    /**
     * @brief (0x9a): Branch if int comparison with zero succeeds (value != zero).
     */
    void ifne();

    /**
     * @brief (0x9b): Branch if int comparison with zero succeeds (value < zero).
     */
    void iflt();

    /**
     * @brief (0x9c): Branch if int comparison with zero succeeds (value >= zero).
     */
    void ifge();

    /**
     * @brief (0x9d): Branch if int comparison with zero succeeds (value > zero).
     */
    void ifgt();

    /**
     * @brief (0x9e): Branch if int comparison with zero succeeds (value <= zero).
     */
    void ifle();

    /**
     * @brief (0x9f): Branch if int comparison succeeds (value1 = value2).
     */
    void if_icmpeq();

    /**
     * @brief (0xa0): Branch if int comparison succeeds (value1 != value2).
     */
    void if_icmpne();

    /**
     * @brief (0xa1): Branch if int comparison succeeds (value1 < value2).
     */
    void if_icmplt();

    /**
     * @brief (0xa2): Branch if int comparison succeeds (value1 >= value2).
     */
    void if_icmpge();

    /**
     * @brief (0xa3): Branch if int comparison succeeds (value1 > value2).
     */
    void if_icmpgt();

    /**
     * @brief (0xa4): Branch if int comparison succeeds (value1 <= value2).
     */
    void if_icmple();

    /**
     * @brief (0xa5): Branch if reference comparison succeeds (value1 = value2).
     */
    void if_acmpeq();

    /**
     * @brief (0xa6): Branch if reference comparison succeeds (value1 != value2).
     */
    void if_acmpne();

    /**
     * @brief (0xa7): Branch always (execution proceeds at that offset from the 
     * address of the opcode of this goto instruction).
     */
    void gotoInstruction();

    /**
     * @brief (0xa8): Jump subroutine.
     */
    //void jsr();

    /**
     * @brief (0xa9): Return from subroutine.
     */
    //void ret();

    /**
     * @brief (0xaa): Access jump table by index and jump.
     */
    void tableswitch();

    /**
     * @brief (0xab): Access jump table by key match and jump.
     */
    //void lookupswitch();

    /**
     * @brief (0xac): Return integer value from method.
     */
    void ireturn();

    /**
     * @brief (0xad): Return long value from method.
     */
    void lreturn();

    /**
     * @brief (0xae): Return float value from method.
     */
    void freturn();

    /**
     * @brief (0xaf): Return double value from method.
     */
    void dreturn();

    /**
     * @brief (0xb0): Return reference value from method.
     */
    void areturn();

    /**
     * @brief (0xb1): Return void from method.
     */
    void returnInstruction();

    /**
     * @brief (0xb2): Get static field from class.
     */
    void getstatic();

    /**
     * @brief (0xb3): Set static field in class.
     */
    //void putstatic();

    /**
     * @brief (0xb4): Fetch field from object.
     */
    //void getfield();

    /**
     * @brief (0xb5): Set field in object.
     */
    //void putfield();

    /**
     * @brief (0xb6): Invoke instance method (dispatch based on class).
     */
    void invokevirtual();

    /**
     * @brief (0xb7): Invoke instance method (special handling for 
     * superclass, private, and instance initialization method invocations).
     */
    //void invokespecial();

    /**
     * @brief (0xb8): Invoke a class (static) method.
     */
    void invokestatic();

    /**
     * @brief (0xb9): Invoke interface method.
     */
    //void invokeinterface();

    /**
     * @brief (0xba): Invoke dynamic method.
     */
    //void invokedynamic();

    /**
     * @brief (0xbb): Create new object.
     */
    //void new();

    /**
     * @brief (0xbc): Create new array.
     */
    void newarray();

    /**
     * @brief (0xbd): Create new array of reference.
     */
    //void anewarray();

    /**
     * @brief (0xbe): Get length of array.
     */
    void arraylength();

    /**
     * @brief (0xbf): Throw exception or error.
     */
    //void athrow();

    /**
     * @brief (0xc0): Check whether object is of given type.
     */
    //void checkcast();

    /**
     * @brief (0xc1): Determine if object is of given type.
     */
    //void instanceof();

    /**
     * @brief (0xc2): Enter monitor for object.
     */
    //void monitorenter();

    /**
     * @brief (0xc3): Exit monitor for object.
     */
    //void monitorexit();

    /**
     * @brief (0xc4): Extend local variable index by additional bytes.
     */
    //void wide();

    /**
     * @brief (0xc5): Create new multidimensional array.
     */
    void multianewarray();

    /**
     * @brief (0xc6): Branch if reference is null.
     */
    void ifnull();

    /**
     * @brief (0xc7): Branch if reference not null.
     */
    void ifnonnull();

    /**
     * @brief (0xc8): Branch always (wide index).
     */
    //void goto_w();

    /**
     * @brief (0xc9): Jump subroutine (wide index).
     */
    //void jsr_w();

    /**
     * @brief TODO.
     */

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
