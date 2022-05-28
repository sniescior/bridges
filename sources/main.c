#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../headers/queue.h"
#include "../headers/car.h"
#include "../headers/town.h"

int N = 10;

typedef struct Thread_args {
    Car *car;
    struct Queue *queue;
} Thread_args;

void bridge(Thread_args thread_args);
void *town(void *args);
void init_cars(Town *A, Town *B, int N, Car *cars_list, pthread_t *th);
void init_thread(Town *town, Car car, pthread_t *th);
void print_status(Town *A, Town *B, Car *Cars_list, struct Queue *queue);

int main(int argc, char const *argv[]) {

    struct Town A, B;
    A.name = "A";
    B.name = "B";
    pthread_t th[N];
    Car Cars_list[N];
    init_cars(&A, &B, N, Cars_list, th);

    struct Queue *Bridge_queue = createQueue(N);

    int i;
    for(i = 0; i < N; i++) {
        enqueue(Bridge_queue, Cars_list+i);
    }

    print_status(&A, &B, Cars_list, Bridge_queue);

    return 0;
}

void *town(void *arg) {

    Thread_args thread_args = *(Thread_args*)arg;
    int random = rand() % 10 + 1;
    printf("Car %d waiting in town (%d sekonds).\n", thread_args.car->id, random);

    sleep(random);

    bridge(thread_args);
}

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

void print_status(Town *A, Town *B, Car *Cars_list, struct Queue *queue) {

    // Count cars on the A/B town side of the bridge
    int A_queue = 0, B_queue = 0, i;
    for(i = 0; i < queue->count_cars; i++) {
        if(!strcmp(queue->Array_of_cars[i].Town->name, "A")) {
            // Car is waiting on the A town side
            A_queue += 1;
        } else {
            // Car is waiting on the B town side
            B_queue += 1;
        }
    }

    printf("A-%d %d>>> [", A->count_cars, A_queue);

    printf("] <<<%d %d-B\n", B_queue, B->count_cars);
}

void bridge(Thread_args thread_args) {
    printf("Car %d is passing the bridge.\n", thread_args.car->id);
    enqueue(thread_args.queue, thread_args.car);
}


