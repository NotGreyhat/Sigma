#include <interrupts/IDT.h>

static idt_vector_t idt[256];
static idtr_t idtr;


void idt_set_vector(uint8_t vector, void* isr) { 
    uint64_t addr = (uint64_t)isr;
    idt[vector].isr_low = addr & 0xFFFF;
    idt[vector].cs = 0x28;
    idt[vector].ist = 0x0;
    idt[vector].reserved = 0x0;
    idt[vector].attr = 0xF;
    idt[vector].reserved1 = 0x0;
    idt[vector].dpl = 0;
    idt[vector].p = 1;
    idt[vector].isr_middle = (addr >> 16) & 0xFFFF;
    idt[vector].isr_high = (addr >> 32) & 0xFFFFFFFF;
    idt[vector].reserved2 = 0x0;
}


void idt_install() {
    idtr.size = sizeof(idt_vector_t) * 256 - 1;
    idtr.base = (uint64_t)&idt;
    __asm__ __volatile__("lidt %0" : : "memory" (idtr));
}
