#ifndef CATALOG_H
#define CATALOG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include "array.h"
#include "users.h"
#include "rides.h"
#include "drivers.h"
#include "buffer.h"
#include "date.h"
//#include "dyn_array.h"

typedef struct catalog Catalog;
typedef struct entradaQ2 entradaQ2;
typedef struct entradaQ3 entradaQ3;
typedef struct entradaQ7 entradaQ7;
typedef struct entradaQ8 entradaQ8;
typedef struct entradaQ9 entradaQ9;

int compare_entradaQ2_score(const void *a, const void *b);
int compareQ7_score(const void *a, const void *b);
int compareQ8_years(const void *a, const void *b);
int compare_entradaQ3_distancia(const void *a, const void *b);
int compareQ9(const void *a, const void *b);

Catalog *newCatalog (GHashTable *users, GHashTable *drivers, GHashTable *rides);

void q1u_response(char *username, Catalog *c, Buffer *buffer);
void q1d_response(int id,Catalog *c, Buffer *buffer);
void avaliacaoDrivers(int N, Catalog *c, Buffer *buffer);
void q3_response(int N, Catalog *c, Buffer *buffer);
void q4_response(char *cidade, Catalog *c, Buffer *buffer);
void q5_response(Date *inicio, Date *fim,Catalog *c, Buffer *buffer);
void q6_response(char *cidade,Date *inicio, Date *fim,Catalog *c, Buffer *buffer);
void q7_response(int N, char *cidade, Catalog *c, Buffer *buffer);
void q8_response(char gender_wanted,int anos_conta,Catalog *c, Buffer *buffer);
void q9_response(Date *inicio, Date *fim,Catalog *c, Buffer *buffer);

#endif