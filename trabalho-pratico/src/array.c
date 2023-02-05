#include "array.h"

struct arrayList{
	void **data;
	int capacidade;
	int n_elem;
	int elem_size;

};

Array *newArray(int capacidade,int elem_size){
	Array *new_Array=malloc(sizeof(Array));
	new_Array->data=malloc(sizeof(void *) * capacidade);
	new_Array->capacidade=capacidade;
	new_Array->n_elem=0;
	new_Array->elem_size=elem_size;

	return new_Array;

}

void sortArray(Array *a, int (*comparator)(const void *, const void *)){ 
	qsort(a->data, a->n_elem,sizeof(void *),comparator);
}


int addToArray(Array *a, void* data){
	if(a->n_elem == a->capacidade){
		if(resizeArray(a, a->capacidade*2)==0){
			return 0;
		}	

	}

	int i= a->n_elem;
	a->data[i]=data;
	a->n_elem++;

	return 1;
}

void *getElement(Array *a, int index) {
	if(index >= a->n_elem) {
		return NULL;
	}
	return a->data[index];
}


int resizeArray(Array *a, int valor){
	void **new_Data=(void **)malloc(sizeof(void *)*valor);

	if(new_Data==NULL) return 0;

	a->capacidade=valor;

	for(int i=0; i<a->n_elem;++i){
		new_Data[i]=a->data[i];
	}

	free(a->data);

	a->data=new_Data;

	return 1;
}

int sizeArray(Array *a){
	return a->n_elem;
}

Array *cloneArray(Array *a){
	Array *new=malloc(sizeof(Array));
	new->data=malloc(sizeof(void *) * a->capacidade);

	for(int i=0;i<a->n_elem;i++){
		new->data[i]=(void *)malloc(a->elem_size);
		memcpy(new->data[i],a->data[i],a->elem_size);
	}

	new->capacidade=a->capacidade;
	new->n_elem=a->n_elem;
	new->elem_size=a->elem_size;

	return new;

}

/*
void *bSearch(Array *a,const void *key,int (*comparator)(const void *, const void *)){
	//printf("chega aqui\n");
	return bsearch(key,a->data,a->n_elem,a->elem_size,comparator);
}*/