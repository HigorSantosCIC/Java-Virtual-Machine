#include <frame.hpp>

Frame::Frame(cp_info **cp)
{
    constant_pool = cp;
    pc = 0;
}

Frame::~Frame()
{
}

u4 Frame::getPc()
{
    return pc;
}