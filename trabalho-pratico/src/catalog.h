#ifndef CATALOG_H
#define CATALOG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "array.h"
#include "users.h"
#include "rides.h"
#include "drivers.h"
#include "buffer.h"
#include "date.h"
#include <glib.h>

typedef struct catalog Catalog;

Catalog *newCatalog (GHashTable *users, GHashTable *drivers, GHashTable *rides);

void q4_response(char *cidade, Catalog *c, Buffer *buffer);
void q5_response(Date *inicio, Date *fim,Catalog *c, Buffer *buffer);
void q6_response(char *cidade,Date *inicio, Date *fim,Catalog *c, Buffer *buffer);
void q8_response(char gender_wanted,int anos_conta,Catalog *c, Buffer *buffer);
void q9_response(Date *inicio, Date *fim,Catalog *c, Buffer *buffer);

#endif