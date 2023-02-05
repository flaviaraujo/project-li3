#ifndef RIDES_H
#define RIDES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "date.h"
#include "array.h"
#include <glib.h>
#include "valid.h"

typedef struct ride Ride;

Ride *newRide(int id, Date *date, int driver, char *user, char *city, int distance, int score_user, int score_driver, float tip);
GHashTable *parse_rides(char *path);
int rideComparator(const void *a, const void *b);

char *getRideUser(Ride *r);
int getRideDriver(Ride *r);
Date *getDateRide(Ride *r);
float getTip(Ride *r);
int getRideID(Ride *r);
int getDistance(Ride *r);
char *getCidade(Ride *r);
int getScoreDriver(Ride *r);
int getScoreUser(Ride *r);

void printRider(Ride *r);

#endif