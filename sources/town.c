#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../headers/town.h"
#include "../headers/car.h"

void init_town(Town *town, char *name) {
    town->name = name;
}