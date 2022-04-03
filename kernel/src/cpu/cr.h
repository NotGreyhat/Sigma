#ifndef CR_H
#define CR_H


#define CPU_GEN_CR_INTERFACE(CR)        \
    uint64_t read_cr##CR();             \
    void write_cr##CR(uint64_t data);


CPU_GEN_CR_INTERFACE(0);
CPU_GEN_CR_INTERFACE(1);
CPU_GEN_CR_INTERFACE(2);
CPU_GEN_CR_INTERFACE(3);

#endif
