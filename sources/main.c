#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int N = 10;

typedef struct Town {
    int count_cars;
    char *name;
} Town;

typedef struct Car {
    struct Town *Town;
    int id;
} Car;

typedef struct Car_Thread {
    struct Car *Car;
} Car_Thread;

void bridge(void *args);
void *town(void *args);
void init_cars(Town *A, Town *B, int N, Car *cars_list);
void init_threads(Town *A, Town *B, int N, Car *cars_list, pthread_t *th);

int main(int argc, char const *argv[]) {
    struct Town A, B;
    A.name = "A";
    B.name = "B";
    Car Cars_list[N];
    init_cars(&A, &B, N, Cars_list);

    printf("Cars:\n");
    int i;
    for(i = 0; i < N; i++) {
        printf("%d %s\n", Cars_list[i].id, Cars_list[i].Town->name);
    }

    pthread_t th[N];

    init_threads(&A, &B, N, Cars_list, th);



    return 0;
}

void *town(void *arg) {
    int id = *(int*)arg;
    printf("Thread created (%d).\n", id);
}

void init_cars(Town *A, Town *B, int N, Car *Cars_list) {
    srand(time(NULL));
    int a = rand() % 10 + 1;

    A->count_cars = a;
    B->count_cars = N - a;

    int i;
    for(i = 0; i < A->count_cars; i++) {
        Cars_list[i].id = i;
        Cars_list[i].Town = A;
    }

    for(i = A->count_cars; i < N; i++) {
        Cars_list[i].id = i;
        Cars_list[i].Town = B;
    }
}

void init_threads(Town *A, Town *B, int N, Car *cars_list, pthread_t *th) {
    int i;
    for(i = 0; i < A->count_cars; i++) {
        if(pthread_create(&th[i], NULL, &town, &i) != 0) { 
            perror("Failed to create thread.\n");
            exit(1);
        }
    }

    for(i = A->count_cars; i < N; i++) {
        if(pthread_create(&th[i], NULL, &town, &i) != 0) { 
            perror("Failed to create thread.\n");
            exit(1);
        }
    }

    for(i = 0; i < N; i++) {
        if(pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread.\n");
            exit(2);
        }
    }

}
