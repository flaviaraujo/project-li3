#ifndef MODOBATCH_H
#define MODOBATCH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>   // for gettimeofday()
#include <unistd.h>     // for sleep()
#include "catalog.h"
#include "date.h"
#include "buffer.h"
#include "queries.h"
#include "validation.h"
#include <glib.h>

void parse_queries(Catalog *c,char *path,char *commands);

#endif