#include<stdlib.h>
#include<stdint.h>

typedef struct CPU_STRUCT
{
    union{
        struct 
        {
            uint8_t al;
            uint8_t ah;
        }; 
        uint16_t ax;
        uint32_t eax;
        uint64_t rax;
    };
    

    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;
    uint64_t rip;
}reg_t;

reg_t reg;

typedef  enum OP{
    MOV,
    PUSH,
    CALL
}  op_t;

typedef enum    od_type 
{
    IMM, REG, MM_IMM, MM_REG, MM_REG1_REG2,
    MM_IMM_REG1_REG2, MM_REG2_S, MM_IMM_REG2_S,
    MM_REG1_REG2_S, MM_IMM_REG1_REG2_S
}od_type_t;

typedef struct OD
{
    od_type_t type;

    int64_t imm;
    uint64_t scal;
    uint64_t *reg1;
    uint64_t *reg2;

    char code[100];
} od_t;

typedef struct INSTRUCT_STRUCT
{
    op_t op;
    od_t src;
    od_t dst;
}inst_t;

#define MM_LEN 1000
uint8_t mm[MM_LEN];

#define INST_LEN 100
inst_t programp[INST_LEN];


uint64_t decode_od(od_t od);