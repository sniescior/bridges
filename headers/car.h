#ifndef CAR_H_
#define CAR_H_

#include <pthread.h>

// Struct representing a car (aka thread)
typedef struct Car {
    struct Town *Town;
    int id;
    pthread_t thread_id;
} Car;

#endif