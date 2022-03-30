#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <interrupts/IDT.h>


void div0_handler(int_frame_t*);
void debug_exception(int_frame_t*);
void overflow_exception(int_frame_t*);
void bre_exception(int_frame_t*);
void invalid_opcode_exception(int_frame_t*);
void dev_not_avail_exception(int_frame_t*);
void double_fault(int_frame_t*);
void invalid_tss_exception(int_frame_t*);
void snp_exception(int_frame_t*);
void stackseg_fault(int_frame_t*);
void gpf(int_frame_t*);
void page_fault(int_frame_t*);


#endif
