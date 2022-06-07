#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../headers/car.h"
#include "../headers/town.h"
#include "../headers/thread.h"
#include "../headers/queue.h"

int N = 3;
int d = 0;
pthread_mutex_t mutex;

struct arg_struct {
    Town *A;
    Town *B;
    Car *car;
    struct Queue *queue_a;
    struct Queue *queue_b;
} *args;

void init_cars(Town *A, Town *B, Car *car_list, pthread_t *th, struct Queue *queue_a, struct Queue *queue_b);
void bridge(void *arg);
void init_thread(Town *A, Town *B, Car *car_list, int i, pthread_t *th, struct Queue *queue_a, struct Queue *queue_b);

void *town(void* arg) {
    while(1) {
        struct arg_struct *args = arg;
        int town_tour_time = rand() % 10 + 1;

        if(d) {
            printf("\tCar %d chilling in town %s (%d seconds). (queue_a = %d queue_b = %d)\n", args->car->id, args->car->Town->name, town_tour_time, args->queue_a->count_cars, args->queue_b->count_cars);
        }

        sleep(town_tour_time);

        if(d) {
            printf("\t\tCar %d would want to pass the bridge now.\n", args->car->id);
        }

        if(args->car->Town == args->A) {
            args->queue_a->count_cars += 1;
        } else {
            args->queue_b->count_cars += 1;
        }

        pthread_mutex_lock(&mutex);
        bridge(arg);
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char * const argv[]) {

    int opt;
    while((opt = getopt(argc, argv, "N:n:d")) != -1) {
        switch (opt) {
            case 'N':
                N = atoi(optarg);
                printf("Number of cars initially: %d\n", N);
                break;
            case 'n':
                N = atoi(optarg);
                printf("Number of cars initially: %d\n", N);
                break;
            case 'd':
                d = 1;
                printf("Debug active: \n");
                break;
        }
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_t th[N];

    Town A, B;
    init_town(&A, "A");
    init_town(&B, "B");

    Car *car_list;
    car_list = malloc(N*sizeof(Car));

    struct Queue queue_a;
    struct Queue queue_b;
    queue_a.count_cars = 0;
    queue_b.count_cars = 0;

    init_cars(&A, &B, car_list, th, &queue_a, &queue_b);

    pthread_mutex_destroy(&mutex);

    return 0;
}

void init_cars(Town *A, Town *B, Car *car_list, pthread_t *th, struct Queue *queue_a, struct Queue *queue_b) {
    int i, a, b;
    srand(time(NULL));
    a = rand() % N + 1;
    b = N - a;
    A->count_cars = a;
    B->count_cars = b;

    for(i = 0; i < a; i++) {
        Car car;
        car.id = i;
        car.Town = A;
        car.Destination = B;
        car_list[i] = car;
    }

    for(i = a; i < N; i++) {
        Car car;
        car.id = i;
        car.Town = B;
        car.Destination = A;
        car_list[i] = car;
    }

    for(i = 0; i < N; i++) {
        init_thread(A, B, &car_list[i], i, th, queue_a, queue_b);
    }

    for(i = 0; i < N; i++) {
        if(pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread.\n");
            exit(2);
        }
    }
}

void bridge(void *arg) {
    struct arg_struct *args = arg;

    if(args->car->Town == args->A) {
        args->A->count_cars -= 1;
        args->queue_a->count_cars -= 1;
        printf("A-%d %d>>> [>> %d >>] <<<%d %d-B\n", args->car->Town->count_cars, args->queue_a->count_cars, args->car->id, args->queue_b->count_cars, args->car->Destination->count_cars);
        args->car->Town = args->B;
        args->car->Destination = args->A;
        args->B->count_cars += 1;
    } else {
        args->B->count_cars -= 1;
        args->queue_b->count_cars -= 1;
        printf("A-%d %d>>> [<< %d <<] <<<%d %d-B\n", args->car->Destination->count_cars, args->queue_a->count_cars, args->car->id, args->queue_b->count_cars, args->car->Town->count_cars);
        args->car->Town = args->A;
        args->car->Destination = args->B;
        args->A->count_cars += 1;
    }

    sleep(5);
}

void init_thread(Town *A, Town *B, Car *car, int i, pthread_t *th, struct Queue *queue_a, struct Queue *queue_b) {
    args = malloc(sizeof(struct arg_struct));
    args->A = A;
    args->B = B;
    args->car = car;
    args->queue_a = queue_a;
    args->queue_b = queue_b;

    if(pthread_create(&th[i], NULL, &town, args) != 0) { 
        perror("Failed to create thread.\n");
        exit(1);
    }
}