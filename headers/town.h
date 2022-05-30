#ifndef TOWN_H_
#define TOWN_H_

#include "../headers/car.h"

typedef struct Town {
    int count_cars;     // Number of cars in town
    char *name;
} Town;

void init_town(Town *town, char *name);

#endif