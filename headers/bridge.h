#ifndef BRIDGE_H_
#define BRIDGE_H_

#include "../headers/car.h"
#include "../headers/town.h"
#include "../headers/queue.h"
#include "../headers/thread.h"

void print_status(Town *A, Town *B, Car *Cars_list, struct Queue *queue, Car car);
void *bridge(struct Thread_args thread_args);

#endif