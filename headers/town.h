#ifndef TOWN_H_
#define TOWN_H_

typedef struct Town {
    int count_cars;
    char *name;
} Town;

void *town(void *args);

#endif