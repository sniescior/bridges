#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include "../headers/town.h"
#include "../headers/car.h"


typedef struct Thread {
    struct Town *A;
    struct Town *B;
    struct Car *car;
} Thread;

#endif