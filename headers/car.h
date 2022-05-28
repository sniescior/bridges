#ifndef CAR_H_
#define CAR_H_

#include <pthread.h>
#include "../headers/town.h"

// Struct representing a car (aka thread)
typedef struct Car {
    struct Town *Town;
    int id;
} Car;

#endif