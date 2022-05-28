#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include "../headers/car.h"
#include "../headers/town.h"
#include "../headers/queue.h"

struct Thread_args {
    Town A;
    Town B;
    Car *car;
    Car *Cars_list;
    
    struct Queue *queue;
} *args;

#endif