#include "drivers.h"


struct driver{

	int id;
	char *name;
	Date *birth_date;
	char gender;
	char *car_class;
	Date *account_creation;
	char *account_status;
	int anos_driver;

};

Driver *newDriver(int id, char *name, Date *birth_date, char gender, char *car_class, Date *account_creation, char *account_status, int anos_driver){

	Driver *new_Driver=(Driver *)malloc(sizeof(Driver));
	new_Driver->id=id;
	new_Driver->name=strdup(name);
	new_Driver->birth_date=cloneDate(birth_date);
	new_Driver->gender=gender;
	new_Driver->car_class=strdup(car_class);
	new_Driver->account_creation=cloneDate(account_creation);
	new_Driver->account_status=strdup(account_status);
	new_Driver->anos_driver=anos_driver;

	return new_Driver;
}

int driverComparator(const void *a, const void *b){ // const pointer para garantir que elementos nao sao alterados
	const Driver *d1=(*(Driver **)a);
	const Driver *d2=(*(Driver **)b);

	return d1->id - d2->id;
}

int driverIDComparator(const void *a, const void *b){
	const int *d1=a;
	const Driver *d2=(*(Driver **)b);

	return *d1 - d2->id;
}

/*void *bSearchD(Array *a,const int key,int (*comparator)(const void *, const void *)){
	//printf("chega aqui\n");
	//return bsearch(key,a->data,a->n_elem,a->elem_size,comparator);

	for(int i=0;i<sizeArray(a);i++){
		Driver *d=getElement(a,i);
		if(driverID(d)==key) return d;
	}

	return NULL;

}*/

char driverGender(Driver *d){
	return d->gender;
}

int driverAnos(Driver *d){
	return d->anos_driver;
}

int driverID(Driver *d){
	return d->id;
}

char *driverName(Driver *d){
	return strdup(d->name);
}

char *getClass(Driver *d){
	return d->car_class;
}

GHashTable *parse_drivers(char* path) {

	time_t seconds = time(NULL);
	struct tm* current_time = localtime(&seconds);



	char buffer[200];

	char directory[100];
	snprintf(directory, sizeof(directory), "%s/drivers.csv", path);


	FILE* drivers = fopen(directory,"r");
	if(drivers == NULL) return 0;


	fgets(buffer, 200, drivers); // ignora o cabeçalho

	//GHashTable* a=newArray(200,sizeof(Driver));
	GHashTable *hash = g_hash_table_new(g_int_hash, g_int_equal);
	while(fgets(buffer, 200, drivers)) {

		//printf("%s/n", buffer);

		char *buffer_aux = buffer;

		int id = atoi(strsep(&buffer_aux, ";")); 
		//printf("ola/n");
		// strsep - vai dar o que ĺê até ao primeiro ;  
		char *name = (strsep(&buffer_aux, ";"));
		Date *birth_date = dateFromString(strsep(&buffer_aux, ";"));
		char gender = *strsep(&buffer_aux, ";");
		char *car_class = (strsep(&buffer_aux, ";"));
		strsep(&buffer_aux, ";");
		strsep(&buffer_aux, ";");
		Date *account_creation = dateFromString(strsep(&buffer_aux, ";"));
		char *account_status = (strsep(&buffer_aux, ";"));

		int anos_driver=(current_time->tm_year + 1900)-(getYear(account_creation));
		

		Driver* u = newDriver(id,name,birth_date,gender,car_class,account_creation,account_status,anos_driver);

		g_hash_table_insert(hash, &(u->id), u);
		/*int x=addToArray(a,u);
		if(x==0){
			printf("ERRO");
			return 0;
		}
		*/

	}

	fclose(drivers);

	//printf("%d\n", sizeArray(a));

	//sortArray(a, driverComparator);

	return hash;
}