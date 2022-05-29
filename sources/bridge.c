#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../headers/queue.h"
#include "../headers/thread.h"

void print_status(struct Thread_args thread_args) {

    int A_queue = 0, B_queue = 0, i;

    for(i = 0; i < thread_args.queue->count_cars; i++) {
        if(!strcmp(thread_args.queue->Array_of_cars[i].Town->name, "A")) {
            // Car is waiting on the A town side
            A_queue += 1;
        } else {
            // Car is waiting on the B town side
            B_queue += 1;
        }
    }

    printf("\n");

    if(strcmp(thread_args.car->Town->name, "A")) {
        printf("A-%d %d>>> [<< %d <<", thread_args.A.count_cars, A_queue, thread_args.car->id);
        printf("] <<<%d %d-B", B_queue, thread_args.B.count_cars);
    } else {
        printf("A-%d %d>>> [>> %d >>", thread_args.A.count_cars, A_queue, thread_args.car->id);
        printf("] <<<%d %d-B", B_queue, thread_args.B.count_cars);
    }

    printf("\n");
}

void *bridge(struct Thread_args thread_args) {

    sleep(5);
    dequeue(thread_args.queue);

    print_status(thread_args);
}