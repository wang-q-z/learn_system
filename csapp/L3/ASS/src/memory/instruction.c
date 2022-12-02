#include"memory/instruction.h"

uint64_t decode_od(od_t od)
{
    if(od.type == IMM)
    {
        return od.imm;
    }
    else if(od.type == REG)
    {
        /*
        reg.rsp pmm[]
        */
        return (uint64_t)od.reg1;

    }
    else
    {
        
    }
}