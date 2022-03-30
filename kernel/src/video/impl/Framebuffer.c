#include <video/Framebuffer.h>

void reset_term() {
    kwrite("\033[H\033[2J\033[3J");
}
