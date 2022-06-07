#ifndef QUEUE_H_
#define QUEUE_H_

struct Queue {
    int *cars_array;    // Array of cars currently waiting in line
    int count_cars;     // Number of cars witing in line for the bridge
};

#endif