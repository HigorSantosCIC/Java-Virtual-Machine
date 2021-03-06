#ifndef RUNTIME_DATA_AREA_HPP
#define RUNTIME_DATA_AREA_HPP

#include <stdlib.h>
#include <frame_stack.hpp>
#include <method_area.hpp>
class RuntimeDataArea
{
public:
    RuntimeDataArea();
    ~RuntimeDataArea();

    void initializeFrameStack();

    /**
     * @brief Fetch instruction in code attribute of current frame's class file.
     * @param pc_offset Offset from current PC value to be searched. 
     * Commonly, instructions with two code params have pc_offset of 1 and 2, respectively.
     * 
    */
    u1 fetchInstruction(u2 pc_offset);

    // ? Should getNameFromConstantPoolEntry be moved to cp_info
    std::string getNameFromConstantPoolEntry(cp_info *constant_pool_entry);

    /**
     * @brief Load class file and add it to method area. If class file has init method, add it to frame.
     * @param class_name Name of the class to be loaded. Also acts as key in classes map.
     */
    ClassFile *loadClassByName(std::string class_name);

    FrameStack *frame_stack;
    MethodArea *method_area;
};

#endif