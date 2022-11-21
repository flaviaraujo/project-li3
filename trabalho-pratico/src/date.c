#include "date.h"
#include <string.h>

struct date {
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

Date *newDate (int day, int month, int year){
	Date *date = (Date *)malloc(sizeof (Date));
	date->day=day;
	date->month=month;
	date->year=year;

	return date;
}

Date *dateFromString(char *s){
	Date *date = (Date *)malloc(sizeof(Date));
	date->day=atoi(strsep(&s, "/"));
	date->month=atoi(strsep(&s, "/"));
	date->year=atoi(strsep(&s, "/"));

	return date;
}

int getDay(Date *d){
	return d->day;
}

int getMonth(Date *d){
	return d->month;
}

int getYear(Date *d){
	return d->year;
}

Date *cloneDate(Date *d){
	Date *date = (Date *)malloc(sizeof(Date));
	memcpy(date,d,sizeof(Date));

	return date;
}

int dateCompare(Date *d1, Date *d2){
	if(d1->year > d2->year) return 1;
	else if(d1->year < d2->year) return -1;

	else if(d1->month > d2->month) return 1;
	else if(d1->month < d2->month) return-1;
	
	else if(d1->day > d2->day) return 1;
	else if(d1->day < d2->day) return -1;	
	
	return 0;

}
