#ifndef QUEUE_H_
#define QUEUE_H_

#include "../headers/town.h"
#include "../headers/car.h"

// Queue of cars waiting to pass the bridge
struct Queue {
    int count_cars, capacity, front, rear;
    struct Car *Array_of_cars;
};

struct Queue *createQueue(int N);
void enqueue(struct Queue *queue, Car *car);
int dequeue(struct Queue *queue);

#endif