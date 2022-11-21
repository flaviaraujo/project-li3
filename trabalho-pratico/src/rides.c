#include "rides.h"



struct ride{

	int id;
	Date *date;
	int driver;
	char *user;
	char *city;
	int distance;
	int score_user;
	int score_driver;
	float tip;

};

Ride *newRide(int id, Date *date, int driver, char *user, char *city, int distance, int score_user, int score_driver, float tip){

	Ride *new_Ride=(Ride *)malloc(sizeof(Ride));
	new_Ride->id=id;
	new_Ride->date=cloneDate(date);
	new_Ride->driver=driver;
	new_Ride->user=strdup(user);
	new_Ride->city=strdup(city);
	new_Ride->distance=distance;
	new_Ride->score_user=score_user;
	new_Ride->score_driver=score_driver;
	new_Ride->tip=tip;

	return new_Ride;
}
/*
void printRider(Ride *r){
	printf("Rider(id = %d, driver= %d, user = %s, city = %s\n", r->id, r->driver, r->user, r->city);
} */

int rideComparator(const void *a, const void *b){ // const pointer para garantir que elementos nao sao alterados
	const Ride *r1=(*(Ride **)a);
	const Ride *r2=(*(Ride **)b);


	return dateCompare(r1->date, r2->date);
}

char *getRideUser(Ride *r){
	return strdup(r->user);
}

int getRideDriver(Ride *r){
	return r->driver;
}

Date *getDateRide(Ride *r){
	return r->date;
}

float getTip(Ride *r){
	return r->tip;
}

int getRideID(Ride *r){
	return r->id;
}

int getDistance(Ride *r){
	return r->distance;
}

char *getCidade(Ride *r){
	return r->city;
}


GHashTable *parse_rides(char *path) {


	char buffer[200];
	char directory[100];
	snprintf(directory, sizeof(directory), "%s/rides.csv", path);

	FILE* rides_file = fopen(directory,"r");

	fgets(buffer, 200, rides_file); // ignora o cabeçalho

	//Array* a=newArray(200,sizeof(Ride));
	GHashTable *rides = g_hash_table_new(g_int_hash, g_int_equal);

	while(fgets(buffer, 200, rides_file)) {

		//printf("%s/n", buffer);

		char *buffer_aux = buffer;

		int id = atoi(strsep(&buffer_aux, ";")); 
		//printf("ola/n");
		Date *date = dateFromString(strsep(&buffer_aux, ";"));
		int driver = atoi(strsep(&buffer_aux, ";")); 
		char *user = (strsep(&buffer_aux, ";"));
		char *city = (strsep(&buffer_aux, ";"));
		int distance = atoi(strsep(&buffer_aux, ";"));
		int score_user = atoi(strsep(&buffer_aux, ";")); 
		int score_driver = atoi(strsep(&buffer_aux, ";")); 
		float tip = atof(strsep(&buffer_aux, ";")); 
		strsep(&buffer_aux, ";");
	

		Ride* u = newRide(id,date,driver,user,city,distance,score_user, score_driver,tip);

		g_hash_table_insert(rides, &(u->id), u);

		//int x=addToArray(a,u);
		//if(x==0){
		//	printf("ERRO");
		//	return 0;
		//}

	}

	fclose(rides_file);

	//printf("%d\n", sizeArray(a));

	//sortArray(, rideComparator);

	return rides;
}