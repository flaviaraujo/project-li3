#ifndef MODOINTERATIVO_H
#define MODOINTERATIVO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>   // for gettimeofday()
#include <unistd.h>     // for sleep()
#include "catalog.h"
#include "date.h"
#include "buffer.h"
#include "pages.h"
#include "queries.h"
#include <glib.h>

void menu_queries(Catalog *c,char *path);

#endif