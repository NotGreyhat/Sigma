#include <proc/spinlock.h>


/*
 *  Prevents other threads from calling some code
 *  until mutex_unlock() is called.
 */

void mutex_lock(void* lock) {
    while (__atomic_test_and_set(lock, __ATOMIC_ACQUIRE));
}


/*
 *  Unlocks a resource for threads to use.
 */

void mutex_unlock(void* lock) {
    __atomic_clear(lock, __ATOMIC_RELEASE);
}
