#include"memory/instruction.h"
#include"cpu/mmu.h"
#include"cpu/register.h"

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
        uint64_t vaddr = 0;

        if(od.type == MM_IMM)
        {
            vaddr = *((uint64_t*)&od.imm);
        }
        else if(od.type == MM_REG)
        {
            vaddr = *(od.reg1);
        }
        else if(od.type == MM_IMM_REG)
        {
            vaddr = od.imm + *(od.reg1);
        }
        else if(od.type == MM_REG1_REG2)
        {
            vaddr = *(od.reg1) + *(od.reg2);
        }
        else if(od.type == MM_IMM_REG1_REG2)
        {
            vaddr = od.imm + *(od.reg1) + *(od.reg2);
        }
        else if(od.type == MM_REG2_S)
        {
            vaddr = (*(od.reg2)) * od.scal;
        }
        else if(od.type == MM_IMM_REG2_S)
        {
            vaddr = od.imm + (*(od.reg2)) * od.scal;
        }
        else if(od.type == MM_REG1_REG2_S)
        {
            vaddr = *(od.reg1) + (*(od.reg2)) * od.scal;
        }
        else if(od.type == MM_IMM_REG1_REG2_S)
        {
            vaddr = od.imm + *(od.reg1) + (*(od.reg2)) * od.scal;
        }

        return va2pa(vaddr);
    }
}

void instruction_cycle()
{
    inst_t *instr = (inst_t*)reg.rip;

    uint64_t src = decode_od(instr->src);
    uint64_t dst = decode_od(instr->dst);

    handler_t handle = handler_table[instr->op];
    handle(src,dst);
}

void init_handler_table()
{
    handler_table[mov_reg_reg] = &mov _reg_reg_handler;
    handler_table[add_reg_reg] = &add_reg_reg_handler;
}

void mov_reg_reg_handler(uint64_t src, uint64_t dst)
{
    *(uint64_t*)dst = *(uint64_t*)src;
    reg.rip = reg.rip + sizeof(inst_t);
}

void add_reg_reg_handler(uint64_t src, uint64_t dst)
{
    *(uint64_t*)dst = *(uint64_t*)dst +*(uint64_t*)src;
    reg.rip = reg.rip + sizeof(inst_t);
}