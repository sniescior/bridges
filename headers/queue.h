#ifndef QUEUE_H_
#define QUEUE_H_

struct Queue {
    int *cars_array;    // Array of cars currently waiting in line
    int count_cars;     // Number of cars witing in line for the bridge
    int front;
    int rear;
};

void init_queue(struct Queue *queue, int N);
void print_queue(struct Queue *queue);
void dequeue(struct Queue *queue);
void enqueue(struct Queue *queue, int id);

#endif