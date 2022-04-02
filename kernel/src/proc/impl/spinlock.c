#include <proc/spinlock.h>


void spinlock(void* lock) {
    while (__atomic_test_and_set(lock, __ATOMIC_ACQUIRE));
}


void spinrelease(void* lock) {
    __atomic_clear(lock, __ATOMIC_RELEASE);
}
