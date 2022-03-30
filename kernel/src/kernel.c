#include <util/limine.h>
#include <util/string.h>
#include <interrupts/IDT.h>
#include <interrupts/exceptions.h>
#include <video/Framebuffer.h>


#define HANG \
    while (1) { \
        __asm__ __volatile__("hlt"); \
    }


static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};


volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};


void kwrite(const char* str) {
    terminal_request.response->write(str, strlen(str));
}


static void init_subsystems() {
    kwrite("Setting IDT vectors..\n");
    idt_set_vector(0x0, div0_handler);
    idt_set_vector(0x1, debug_exception);
    idt_set_vector(0x4, overflow_exception);
    idt_set_vector(0x5, bre_exception);
    idt_set_vector(0x6, invalid_opcode_exception);
    idt_set_vector(0x7, dev_not_avail_exception);
    idt_set_vector(0x8, double_fault);
    idt_set_vector(0xA, invalid_tss_exception);
    idt_set_vector(0xB, snp_exception);
    idt_set_vector(0xC, stackseg_fault);
    idt_set_vector(0xD, gpf);
    idt_set_vector(0xE, page_fault);
    kwrite("Installing IDT..\n");
    idt_install();
    kwrite("Done!\n");
}


void _start() {
    if (!(terminal_request.response) || !(framebuffer_request.response)) {
        HANG;
    }

    kwrite("Welcome to SigmaOS!\n");
    init_subsystems(); 
    HANG;
}
