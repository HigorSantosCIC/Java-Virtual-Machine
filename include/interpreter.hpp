#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <stdio.h>
#include <runtime_data_area.hpp>
#include <generic_type.hpp>
#include <math.h>

class Interpreter
{
public:
    Interpreter(RuntimeDataArea *p_runtime_data_area);
    ~Interpreter();

    void run();

private:
    RuntimeDataArea *runtime_data_area;

    /**
     * @brief (0x14): Push long or double from run-time constant pool
     */
    void ldc2_w();
};

#endif
