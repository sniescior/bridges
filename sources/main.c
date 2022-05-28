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

int N = 10;

int main(int argc, char const *argv[]) {

    struct Town A, B;
    A.name = "A";
    B.name = "B";
    pthread_t th[N];
    Car Cars_list[N];
    init_cars(&A, &B, N, Cars_list, th);

    struct Queue *Bridge_queue = createQueue(N);

    return 0;
}
