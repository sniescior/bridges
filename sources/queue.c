#include <stdio.h>
#include <stdlib.h>
#include "../headers/queue.h"

void init_queue(struct Queue *queue, int N) {
    queue->cars_array = malloc(sizeof(int)*N);
    queue->front = 0;
    queue->rear = -1;
    queue->count_cars = 0;
}

void print_queue(struct Queue *queue) {
    int i;
    for(i = 0; i <= queue->rear; i++) {
        printf("%d ", queue->cars_array[i]);
    }
    printf("\n");
}

void dequeue(struct Queue *queue) {
    int i;
    for(i = 0; i < queue->rear; i++) {
        queue->cars_array[i] = queue->cars_array[i+1];
    }
    queue->rear -= 1;
    queue->count_cars -= 1;
}

void enqueue(struct Queue *queue, int id) {
    int i;
    queue->rear += 1;
    queue->cars_array[queue->rear] = id;
    queue->count_cars += 1;
}
