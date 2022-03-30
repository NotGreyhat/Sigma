#include <util/limine.h>
#include <util/string.h>
#include <interrupts/IDT.h>
#include <interrupts/exceptions.h>


#define HANG \
    while (1) { \
        __asm__ __volatile__("hlt"); \
    }


static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};


static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};


void kwrite(const char* str) {
    terminal_request.response->write(str, strlen(str));
}


static void init_subsystems() {
    kwrite("Setting IDT vectors..\n");
    idt_set_vector(0x0, div0_handler);
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
    __asm__ __volatile__("int $0x0");
    HANG;
}
