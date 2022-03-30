#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include <util/limine.h>


void kwrite(const char* str);
void reset_term();
void clear_screen(uint32_t color);
void write_white();

#endif
