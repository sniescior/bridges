#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../headers/queue.h"
#include "../headers/thread.h"

void print_status(Town *A, Town *B, struct Queue *queue, Car car) {

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

    if(strcmp(car.Town->name, "A")) {
        printf("A-%d %d>>> [<< %d <<", A->count_cars, A_queue, car.id);
        printf("] <<<%d %d-B", B_queue, B->count_cars);
    } else {
        printf("A-%d %d>>> [>> %d >>", A->count_cars, A_queue, car.id);
        printf("] <<<%d %d-B", B_queue, B->count_cars);
    }

    printf("\n");
}

void *bridge(struct Thread_args thread_args) {

    dequeue(thread_args.queue);

    sleep(5);
    print_status(&(thread_args.A), &(thread_args.B), thread_args.queue, *thread_args.car);
}