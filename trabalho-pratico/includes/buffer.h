#ifndef BUFFER_H
#define BUFFER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct buffer Buffer;

Buffer *newBuffer(int cap, const char *file);
int pushData(Buffer *buffer, char *answer);
void freeBuffer(Buffer *buffer);
void writeData(Buffer *buffer);
void printBuffer(Buffer *buffer);
#endif