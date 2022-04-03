#ifndef SPINLOCK_H
#define SPINLOCK_H

/*
 * mutex_lock() prevent multiple threads
 * from accesssing the same resource at
 * the same time until mutex_unlock() is
 * called. Once mutex_lock() is called
 * and lets say another thread tries to 
 * call for example do_stuff(), it will
 * have to wait until mutex_unlock() is 
 * called.
 */


void mutex_lock(void* lock);
void mutex_unlock(void* lock);


#endif // !SPINLOCK_H
