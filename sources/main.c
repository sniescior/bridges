#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../headers/car.h"
#include "../headers/town.h"
#include "../headers/thread.h"

int N = 10;
pthread_mutex_t mutex;

struct arg_struct {
    Town *A;
    Town *B;
    Car *car;
} *args;

void init_cars();
void init_town(Town *town, char *name);
void bridge(void *arg);
void init_threads();

void *town(void* arg) {
    int town_tour_time = rand() % 10 + 1;
    sleep(town_tour_time);

    pthread_mutex_lock(&mutex);

    bridge(arg);

    pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[]) {
    pthread_mutex_init(&mutex, NULL);
    pthread_t th[N];

    Town A, B;
    init_town(&A, "A");
    init_town(&B, "B");

    Car *car_list;
    car_list = malloc(N*sizeof(Car));
    init_cars(&A, &B, car_list);

    printf("Initial:\n");
    int i;
    for(i = 0; i < N; i++) {
        printf("%s %d\n", car_list[i].Town->name, car_list[i].id);
    }

    for(i = 0; i < N; i++) {
        args = malloc(sizeof(struct arg_struct));
        args->A = &A;
        args->B = &B;
        args->car = &car_list[i];

        if(pthread_create(&th[i], NULL, &town, args) != 0) { 
            perror("Failed to create thread.\n");
            exit(1);
        }
    }

    for(i = 0; i < N; i++) {
        if(pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread.\n");
            return 2;
        }
    }

    printf("Final:\n");
    for(i = 0; i < N; i++) {
        printf("%s %d\n", car_list[i].Town->name, car_list[i].id);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}

void init_town(Town *town, char *name) {
    town->name = name;
}

void init_cars(Town *A, Town *B, Car *car_list) {
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
}

void bridge(void *arg) {
    struct arg_struct *args = arg;

    sleep(5);

    if(args->car->Town == args->A) {
        args->A->count_cars -= 1;
        printf("A-%d x>>> [>> %d >>] <<<x %d-B\n", args->car->Town->count_cars, args->car->id, args->car->Destination->count_cars);
        args->car->Town = args->B;
        args->car->Destination = args->A;
        args->B->count_cars += 1;
    } else {
        args->B->count_cars -= 1;
        printf("A-%d x>>> [<< %d <<] <<<x %d-B\n", args->car->Destination->count_cars, args->car->id, args->car->Town->count_cars);
        args->car->Town = args->A;
        args->car->Destination = args->B;
        args->A->count_cars += 1;
    }
}

