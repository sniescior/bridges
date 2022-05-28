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
pthread_mutex_t mutex;

void *town(void *args);
void init_cars(Town *A, Town *B, int N, Car *cars_list, pthread_t *th);
void init_thread(Town *A, Town *B, int N, Car *cars_list, pthread_t *th);

int main(int argc, char const *argv[]) {
    pthread_mutex_init(&mutex, NULL);

    struct Town A, B;
    A.name = "A";
    B.name = "B";
    pthread_t th[N];
    Car Cars_list[N];
    init_cars(&A, &B, N, Cars_list, th);

    struct Queue *Bridge_queue = createQueue(N);

    pthread_mutex_destroy(&mutex);
    return 0;
}

void *town(void *arg) {
    
    Thread_args *thread_args = (Thread_args *)arg;

    int random = rand() % 10 + 1;
    printf("Car %d chilling in town (%d seconds).\n", thread_args->car->id, random);

    sleep(random);

    printf("Car %d wants to pass the bridge now.\n", thread_args->car->id);

    // bridge(*thread_args);
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
        init_thread(A, B, N, &Cars_list[i], th);
    }

    printf("\n");

    for(i = A->count_cars; i < N; i++) {
        Cars_list[i].id = i;
        Cars_list[i].Town = B;
        init_thread(A, B, N, &Cars_list[i], th);
    }

    for(i = 0; i < N; i++) {
        if(pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread.\n");
            exit(2);
        }
    }
}

void init_thread(Town *A, Town *B, int N, Car *cars_list, pthread_t *th) {
    Thread_args *thread_args;
    thread_args = (Thread_args*)malloc(sizeof(Thread_args));
    thread_args->A = *A;
    thread_args->B = *B;
    thread_args->car = cars_list;

    if(pthread_create(&th[cars_list->id], NULL, &town, (void *)thread_args) != 0) { 
        perror("Failed to create thread.\n");
        exit(1);
    }
}

