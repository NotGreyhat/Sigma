bits 64

global read_cr0
global write_cr0
global read_cr1
global write_cr1
global read_cr2
global write_cr2
global read_cr3
global write_cr3


read_cr0:
    mov rax, cr0
    retq

write_cr0:
    mov cr0, rdi
    retq

read_cr1:
    mov rax, cr1
    retq

write_cr1:
    mov cr2, rax
    retq

read_cr2:
    mov rax, cr2
    retq

write_cr2:
    mov cr2, rdi
    retq

read_cr3:
    mov rax, cr3
    retq

write_cr3:
    mov cr3, rdi
    retq
