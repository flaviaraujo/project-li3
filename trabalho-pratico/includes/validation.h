#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void compareFiles(FILE *fp1, FILE *fp2);
int validaQueriesB(int linha,char *path,char *commands);

#endif