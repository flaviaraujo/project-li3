#ifndef DRIVERS_H
#define DRIVERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"
#include "array.h"
#include <glib.h>


typedef struct driver Driver;

Driver *newDriver(int id, char *name, Date *birth_date, char gender, char *car_class, Date *account_creation, char *account_status, int anos_driver);
GHashTable *parse_drivers(char *path);
int driverComparator(const void *a, const void *b);
int driverIDComparator(const void *a, const void *b);

//void *bSearchD(Array *a,const int key,int (*comparator)(const void *, const void *));

char driverGender(Driver *d);
int driverAnos(Driver *d);
int driverID(Driver *d);
char *driverName(Driver *d);
char *getClass(Driver *d);

#endif