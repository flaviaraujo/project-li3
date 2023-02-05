#ifndef QUERIES_H
#define QUERIES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "catalog.h"
#include "date.h"
#include "buffer.h"
#include <glib.h>

void query1(int r, int id, char *username, Catalog *c, int linha);
void query2(int N, Catalog *c, int linha);
void query3(int N, Catalog *c, int linha);
void query4(char *cidade,Catalog *c, int linha);
void query5(Date *inicio,Date *fim, Catalog *c, int linha);
void query6(char *cidade,Date *inicio,Date *fim, Catalog *c, int linha);
void query7(int N, char *cidade,Catalog *c,int linha);
void query8(char gender_wanted,int anos_conta,Catalog *c, int linha);
void query9(Date *inicio,Date *fim, Catalog *c,int linha);

#endif