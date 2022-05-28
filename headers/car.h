#ifndef CAR_H_
#define CAR_H_

#include <pthread.h>
#include "../headers/town.h"

// Struct representing a car (aka thread)
typedef struct Car {
    struct Town *Town;
    int id;
    pthread_t thread_id;
} Car;

void init_cars(Town *A, Town *B, int N, Car *cars_list, pthread_t *th);
void init_thread(Town *A, Town *B, int N, Car *cars_list, pthread_t *th);

#endif