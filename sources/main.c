#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int N = 10;

typedef struct Town {
    int count_cars;
    char *name;
} Town;

typedef struct Car {
    struct Town *town;
    int id;
} Car;

void bridge(void *args);
void init_cars(Town *A, Town *B, int N, Car *cars_list);
void init_threads(Town *A, Town *B, int N, Car *cars_list);

int main(int argc, char const *argv[]) {

    struct Town A, B;
    A.name = "A";
    B.name = "B";
    Car Cars_list[N];
    init_cars(&A, &B, N, Cars_list);

    printf("Cars:\n");
    int i;
    for(i = 0; i < N; i++) {
        printf("%d %s\n", Cars_list[i].id, Cars_list[i].town->name);
    }
    
    return 0;
}

void init_cars(Town *A, Town *B, int N, Car *cars_list) {
    srand(time(NULL));
    int a = rand() % 10 + 1;

    A->count_cars = a;
    B->count_cars = N - a;

    int i;
    for(i = 0; i < A->count_cars; i++) {
        cars_list[i].id = i;
        cars_list[i].town = A;
    }

    for(i = A->count_cars; i < N; i++) {
        cars_list[i].id = i;
        cars_list[i].town = B;
    }
}
