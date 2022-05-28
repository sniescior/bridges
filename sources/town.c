#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../headers/town.h"
#include "../headers/queue.h"
#include "../headers/car.h"
#include "../headers/bridge.h"

void *town(void *arg) {

    Thread_args thread_args = *(Thread_args*)arg;
    int random = rand() % 10 + 1;
    printf("Car %d waiting in town (%d sekonds).\n", thread_args.car->id, random);

    sleep(random);

    bridge(thread_args);
}