#include <video/Framebuffer.h>

void reset_term() {
    kwrite("\033[H\033[2J\033[3J");
}


void clear_screen(uint32_t color) {
    extern volatile struct limine_framebuffer_request framebuffer_request;
    struct limine_framebuffer* framebuffer = *framebuffer_request.response->framebuffers;

    for (int vsl = 0; vsl < framebuffer->height; ++vsl) {
        uint64_t pixPtrBase = (uint64_t)framebuffer->address + (9000 * vsl);

        for (uint32_t* pixptr = (uint32_t*)pixPtrBase; pixptr < (uint32_t*)(pixPtrBase + 9000); ++pixptr) {
            *pixptr = color;
        }
    }
}
