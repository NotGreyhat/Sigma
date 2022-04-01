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
extern clear_screen 
extern write_white


%macro write_reg 0
    pop rdi
    call hex2str
    mov rdi, rax
    call kwrite
    mov rdi, newline
    call kwrite
%endmacro


%macro panic 1
    pop rax     ; Return address that we do not need.

    call reset_term
    mov rdi, 0xFF0000
    call clear_screen
    call write_white
    mov rdi, panicmsg1
    call kwrite

    mov rdi, vectormsg
    call kwrite

    mov rdi, %1
    call hex2str
    mov rdi, rax
    call kwrite

    mov rdi, newline
    call kwrite

    mov rdi, __rip
    call kwrite
    write_reg

    mov rdi, __cs
    call kwrite
    write_reg

    mov rdi, __rflags
    call kwrite
    write_reg

    mov rdi, __rsp
    call kwrite
    write_reg

    mov rdi, __ss
    call kwrite
    write_reg

    cli
    hlt
%endmacro


div0_handler:
    panic 0x0

debug_exception:
    panic 0x1

overflow_exception:
    panic 0x4

bre_exception:
    panic 0x5

invalid_opcode_exception:
    panic 0x6

dev_not_avail_exception:
    panic 0x7

double_fault:
    panic 0x8

invalid_tss_exception:
    panic 0xA

snp_exception:
    panic 0xB

stackseg_fault:
    panic 0xC

gpf:
    panic 0xD

page_fault:
    panic 0xE


panicmsg1: db "** KERNEL PANIC **", 0xA, 0x0
vectormsg: db "VECTOR FIRED: ", 0x0
newline: db 0xA, 0x0

; Register names.
__rip: db "RIP: ", 0x0
__cs: db "CS: ", 0x0
__rflags: db "RFLAGS: ", 0x0
__rsp: db "RSP: ", 0x0
__ss: db "SS: ", 0x0

