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

//21.10.2002 3.2.2023    2023-2002=21   10>2 = 20 
//5.2.2002  3.2.2023     2023-2002=21   2==2 = 21   
//13.6.2000  14.6.2020   2000-2020=20   6==6 = 20  13 

//29/12/1988  3.2.2023   2023-1988=35  12>2 = 34       
int findAge(Date *d1, Date *d2){
	int age=0;

	age = (d2->year)-(d1->year);
	
	if(d1->month > d2->month) age--;
	else if (d1->month == d2->month){
		if(d1->day > d2->day) age--;
	}
	//else if (d1->month < d2->month) age--;

	return age;
}

int findOldest(Date *d1, Date *d2){
	int days=0;

	days += 31-d1->day;
	days += (12 - d1->month) * 31;
	days += 365 * (d2->year-1-d1->year);
	days += d2->day + 31 * (d2->month - 1);

	return days;
}
