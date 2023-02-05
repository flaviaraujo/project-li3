#ifndef VALID_H
#define VALID_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "date.h"
#include "array.h"
#include <glib.h>


int valida_restante(char *campo);
int valida_genero(char campo);
int valida_classe(char *classe);
int valida_status(char *status);
int valida_data(char *data);
int valida_intpos(char *campos);
int valida_tip(char *campo);


#endif