#include "cachelab.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define OP_LENGTH 128

//一行
typedef struct block{
    int is_valid;
    int tag;
    int time_stamp;
}block;

//多行构成一个set
typedef block* set_t;

/*
 * 定义cache
 *
 */
typedef struct cache{
    int nline;//一个set多少行 保存int
    int nset;//一共多少set    保存 int
    int ndata;//一行多少数据   bit
    set_t* set_head;//set集合
}cache;

//解析trace
typedef struct operation{
    char type; //I L M S
    int size;//读取的字节数
    unsigned long address;//64位的地址
}operation;

/*
 * s number of set index bits
 * b number of block bits
 * e number of lines per set
 */
cache init_cache(int s, int b, int e){
    int n_sets = 1 << s;
    set_t* sets = (set_t*)malloc(n_sets * sizeof(set_t));
    for(int i = 0; i < n_sets; i++){
        sets[i] = (block*)malloc(e * sizeof(block));
    }
    cache c;
    c.nline = e;
    c.nset = n_sets;
    c.ndata = b;
    c.set_head = sets;
    return c;
}

void free_cache(cache *c){
    for(int i = 0; i < c->nset; i++)
    {
        free(c->set_head[i]);
        c->set_head[i] = NULL;
    }
    free(c->set_head);
    c->set_head = NULL;
}

operation parse_op(FILE * trace){
    char s_trace[OP_LENGTH];
    operation op = { 0, 0, 0 };
    if(!fgets(s_trace, OP_LENGTH, trace)){
        return op;
    }
    sscanf(s_trace,"\n%c %lx,%d",&op.type, &op.address, &op.size);
    return op;
}


int main()
{
    //printSummary(0, 0, 0);
    FILE *trace = fopen("traces/yi.trace","r");
    operation op = parse_op(trace);
    //printf("%c,%lx,%d",op.type,op.address,op.size);
    return 0;
}
