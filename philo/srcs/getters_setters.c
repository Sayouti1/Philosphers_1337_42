#include "../include/include.h"


long get_lvalue(pthread_mutex_t *lock, long *val)
{
    long x;

    pthread_mutex_lock(lock);
    x = *val;
    pthread_mutex_unlock(lock);
    return (x);
}

int get_value(pthread_mutex_t *lock, int *val)
{
    int x;

    pthread_mutex_lock(lock);
    x = *val;
    pthread_mutex_unlock(lock);
    return (x);
}

void set_lvalue(pthread_mutex_t *lock, long *var, long val)
{
    pthread_mutex_lock(lock);
    *var = val;
    pthread_mutex_unlock(lock);
}

void set_value(pthread_mutex_t *lock, int *var, int val)
{
    pthread_mutex_lock(lock);
    *var = val;
    pthread_mutex_unlock(lock);
}