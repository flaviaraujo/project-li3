#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct arrayList Array;

Array *newArray(int capacidade,int elem_size);
int addToArray(Array *a, void* data);
int resizeArray(Array *a, int valor);
int sizeArray(Array *a);
Array *cloneArray(Array *a);
void sortArray(Array *a, int (*comparator)(const void *, const void *));
void *getElement(Array *a, int index);
void *bSearch(Array *a,const void *key,int (*comparator)(const void *, const void *));

#endif