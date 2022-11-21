#ifndef DATE_H
#define DATE_H
#include <stdlib.h>

typedef struct date Date;

Date *newDate (int day, int month, int year);
Date *dateFromString(char *);
int getDay(Date *d);
int getMonth(Date *d);
int getYear(Date *d);
Date *cloneDate(Date *d);
int dateCompare(Date *d1, Date *d2);

#endif