#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../headers/queue.h"
#include "../headers/car.h"
#include "../headers/town.h"
#include "../headers/thread.h"

void init_cars(Town *A, Town *B, int N, Car *Cars_list, pthread_t *th) {

    srand(time(NULL));
    int a = rand() % 10 + 1;

    A->count_cars = a;
    B->count_cars = N - a;

    int i;
    for(i = 0; i < A->count_cars; i++) {
        Cars_list[i].id = i;
        Cars_list[i].Town = A;
        init_thread(A, Cars_list[i], th);
    }

    printf("\n");

    for(i = A->count_cars; i < N; i++) {
        Cars_list[i].id = i;
        Cars_list[i].Town = B;
        init_thread(B, Cars_list[i], th);
    }
}

void init_thread(Town *town, Car car, pthread_t *th) {
    printf("Thread initialization (%d %s).\n", car.id, car.Town->name);
}