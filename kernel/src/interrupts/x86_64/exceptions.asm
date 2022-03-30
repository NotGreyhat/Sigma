bits 64

global div0_handler
global debug_exception
global overflow_exception
global bre_exception
global invalid_opcode_exception
global dev_not_avail_exception
global double_fault
global invalid_tss_exception
global snp_exception
global stackseg_fault
global gpf
global page_fault

extern kwrite
extern hex2str
extern reset_term

%macro panic 1
    call reset_term
    mov rdi, panicmsg1
    call kwrite
    cli
    hlt
%endmacro


div0_handler:
    panic 1


panicmsg1: db "** KERNEL PANIC **", 0xA, 0x0
