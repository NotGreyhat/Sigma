#ifndef IDT_H
#define IDT_H

#include <stdint.h>


/*
 *  The CPU needs to know how to response to an interrupt.
 *  When an interrupt happens it gives an index to the CPU
 *  and the CPU will use it to index a vector in the IDT for
 *  the interrupt service routine.
 */


typedef struct {
    uint16_t isr_low;       // Low 16 bytes of ISR address/
    uint16_t cs;            // Code segment ISR is in.
    uint8_t ist : 3;
    uint8_t reserved : 5;
    uint8_t attr : 4;
    uint8_t reserved1 : 1;
    uint8_t dpl : 2;        // Descriptor privilege level.
    uint8_t p : 1;          // Present.
    uint16_t isr_middle;    // Middle 16 bits of ISR.
    uint32_t isr_high;      // High 32 bits of ISR.
    uint32_t reserved2; 
} __attribute__((packed)) idt_vector_t;


typedef struct {
    uint16_t size;
    uint64_t base;
} __attribute__((packed)) idtr_t;


typedef struct {
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} __attribute__((packed)) int_frame_t;


void idt_set_vector(uint8_t vector, void* isr);
void idt_install();

#endif
