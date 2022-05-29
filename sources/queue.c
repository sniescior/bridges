#include <stdlib.h>
#include <stdio.h>
#include "../headers/queue.h"

struct Queue *createQueue(int N) {

    struct Queue *queue = (struct Queue*)malloc(
        sizeof(struct Queue)
    );

    queue->capacity = N;
    queue->front = queue->count_cars = 0;

    queue->rear = N - 1;
    queue->Array_of_cars = (Car*)malloc(
        queue->capacity * sizeof(Car)
    );

    return queue;
}

// Add an item to the queue
void enqueue(struct Queue *queue, Car *car) {

    queue->rear = (queue->rear + 1)%queue->capacity;
    queue->Array_of_cars[queue->rear] = *car;
    queue->count_cars += 1;

    printf("\tCar (%d) wants to pass the bridge (was added to the queue).\n", car->id);
}

// Remove from the queue (the car has passed the bridge successfully - let's hope)
int dequeue(struct Queue *queue) {

    queue->front = (queue->front + 1) % queue->capacity;
    queue->count_cars -= 1;
}