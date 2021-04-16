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

    /**
     * @brief (0x14): Push long or double from run-time constant pool
     */
    void ldc2_w();
    void dstore_0();
    void dstore_1();
    void dstore_2();
    void dstore_3();
    void dstore_n(int index);
    void getstatic();

    // ? Where to save splitByToken method? Consider creater a StringUtils namespace.
    std::string splitByToken(std::string str, int position);
};

#endif
