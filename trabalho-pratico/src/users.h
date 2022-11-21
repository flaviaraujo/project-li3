#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"
#include "array.h"
#include <glib.h>


typedef struct user User;

User *newUser(char *username, char *name, char gender, Date *birth_date, Date *account_creation, char *account_status, int anos_user);
GHashTable *parse_users(char *path);
int userComparator(const void *a, const void *b);
int userNameComparator(const void *a, const void *b);

//void *bSearchU(Array *a,const void *key,int (*comparator)(const void *, const void *));

char userGender(User *u);
int userAnos(User *u);
char *nameUser(User *u);
char *userRealName(User *u);

#endif