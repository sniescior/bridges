#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../headers/town.h"
#include "../headers/queue.h"
#include "../headers/car.h"
#include "../headers/bridge.h"

void *town(void *arg) {

    int id = *(int*)arg;
    int random = rand() % 10 + 1;
    printf("Car %d chilling in town (%d seconds).\n", id, random);

    sleep(random);

    printf("Car %d wants to pass the bridge now.\n", id);

    // bridge(*thread_args);
}