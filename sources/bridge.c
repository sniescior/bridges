#include <stdio.h>
#include <string.h>
#include "../headers/queue.h"
#include "../headers/thread.h"

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

    print_status(&(thread_args.A), &(thread_args.B), thread_args.Cars_list, thread_args.queue);
}