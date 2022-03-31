bits 64
global load_gdt

GDT:
    null: equ $ - GDT
        dw 0                         ; Limit (low).
        dw 0                         ; Base (low).
        db 0                         ; Base (middle)
        db 0                         ; Access.
        db 1                         ; Granularity.
        db 0                         ; Base (high).
    code16:
        dw 0xFFFF
        dw 0
        db 0
        db 0b10011010
        db 0b00000000
        db 0
    data16:
        dw 0xFFFF
        dw 0
        db 0
        db 0b10010010
        db 0b00000000
        db 0
    code32:
        dw 0xFFFF
        dw 0
        db 0
        db 0b10011010
        db 0b11001111
        db 0
    data32:
        dw 0xFFFF
        dw 0
        db 0
        db 0b10010010
        db 0b11001111
        db 0
    code64:
        dw 0
        dw 0
        db 0
        db 0b10011010
        db 0b00100000
        db 0
    data64:
        dw 0
        dw 0
        db 0
        db 0b10010010
        db 0b00000000
        db 0
    gdt_ptr:
        dw $ - GDT - 1
        dq GDT


load_gdt:
    cli
    lgdt [gdt_ptr]
    mov rax, 0x30
    mov ds, rax
    mov es, rax
    mov fs, rax
    mov gs, rax
    mov ss, rax
    pop rdi
    mov rax, 0x28
    push rax
    push rdi
    retfq
