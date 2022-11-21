#include "catalog.h"


struct catalog{

	GHashTable *users;
	GHashTable *drivers;
	GHashTable *rides;

};

Catalog *newCatalog (GHashTable *users, GHashTable *drivers, GHashTable *rides){

	Catalog *new_Catalog=(Catalog *)malloc(sizeof(Catalog));
	new_Catalog->users=users;
	new_Catalog->drivers=drivers;
	new_Catalog->rides=rides;
	
	return new_Catalog;
}
/*
printCatalog(Catalog *c){
	for(int i = 0; i < sizeArray(c->rides); ++i) {
		Ride *rider = getElement(c->rides, i);
		printRider(rider);
	}

	for(int i = 0; i < sizeArray(c->drivers); ++i) {

	}

	for(int i = 0; i < sizeArray(c->users); ++i) {

	}
} */

void q4_response(char *cidade, Catalog *c, Buffer *buffer){
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, c->rides);
	void *value = NULL;

	double precoB=3.25;
	double precoG=4;
	double precoP=5.20;

	double precoViagem=0;
	int count=0;

	while(g_hash_table_iter_next(&iter, NULL, &value)){
		Ride *ride = (Ride *)value;

		int driver_id = getRideDriver(ride);
		Driver *driver = g_hash_table_lookup(c->drivers, &driver_id);
		if(driver == NULL) {
			//printf("Algum driver nao foi encontrado\n");
			return;
		}

		char *class=getClass(driver);
		double distancia=getDistance(ride);

		//printf("%f\n", distancia);
		
		char *cityRide = getCidade(ride);

		if(strcmp(cityRide,cidade)==0){
			count++;

			if(strcmp(class,"basic")==0){
				precoViagem=precoViagem+precoB+0.62*distancia;
			}

			else if(strcmp(class,"green")==0){
				precoViagem=precoViagem+precoG+0.79*distancia;
			}

			else if(strcmp(class,"premium")==0){
				precoViagem=precoViagem+precoP+0.94*distancia;
			}
		}

	}

	double preco_medio = precoViagem/count;

	char data[1024];
	snprintf(data, sizeof(data), "%.3f\n", preco_medio);
	pushData(buffer, data);

}

void q5_response(Date *inicio, Date *fim,Catalog *c, Buffer *buffer){
	
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, c->rides);
	void *value = NULL;

	double precoB=3.25;
	double precoG=4;
	double precoP=5.20;

	double precoViagem=0;
	int count=0;
	
	while(g_hash_table_iter_next(&iter, NULL, &value)){
		Ride *ride = (Ride *)value;

		Date *dateRide = getDateRide(ride);

		int driver_id = getRideDriver(ride);
		Driver *driver = g_hash_table_lookup(c->drivers, &driver_id);
		if(driver == NULL) {
			//printf("Algum driver nao foi encontrado\n");
			return;
		}

		char *class=getClass(driver);
		double distancia=getDistance(ride);

		if(dateCompare(dateRide,inicio)>=0  &&  dateCompare(fim,dateRide)>=0){
			count++;

			if(strcmp(class,"basic")==0){
				precoViagem=precoViagem+precoB+0.62*distancia;
			}

			else if(strcmp(class,"green")==0){
				precoViagem=precoViagem+precoG+0.79*distancia;
			}

			else if(strcmp(class,"premium")==0){
				precoViagem=precoViagem+precoP+0.94*distancia;
			}
		}

	}

	double preco_medio = precoViagem/count;

	char data[1024];
	snprintf(data, sizeof(data), "%.3f\n", preco_medio);
	pushData(buffer, data);
}

void q6_response(char *cidade,Date *inicio, Date *fim,Catalog *c, Buffer *buffer){
	
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, c->rides);
	void *value = NULL;
	double distancia = 0;
	int count = 0;
	
	while(g_hash_table_iter_next(&iter, NULL, &value)){
		Ride *ride = (Ride *)value;

		Date *dateRide = getDateRide(ride);
		char *cityRide = getCidade(ride);

		if(strcmp(cityRide,cidade)==0){
			if(dateCompare(dateRide,inicio)>=0  &&  dateCompare(fim,dateRide)>=0){
				distancia += getDistance(ride);
				count++; 

			}
		}
	}

	//printf("%f %f\n", distancia, count);
	double distancia_media= distancia/count;

	char data[1024];
	snprintf(data, sizeof(data), "%.3f\n", distancia_media);
	pushData(buffer, data);
}

void q8_response(char gender_wanted,int anos_conta,Catalog *c, Buffer *buffer){

	GHashTableIter iter;
	g_hash_table_iter_init(&iter, c->rides);
	void *value = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &value)) {
		Ride *ride = (Ride *)value;
		char *username = getRideUser(ride);
		int driver_id = getRideDriver(ride);
		//printf("username = %s, driver_id= %d\n", username, driver_id);

		User *user = g_hash_table_lookup(c->users, username);
		if(user == NULL) {
			//printf("Algum user nao foi encontrado\n");
			return;
		}
		Driver *driver = g_hash_table_lookup(c->drivers, &driver_id);
		if(driver == NULL) {
			//printf("Algum driver nao foi encontrado\n");
			return;
		}

		char user_gender = userGender(user);
		char driver_gender = driverGender(driver);
		int user_anos = userAnos(user);
		int driver_anos = driverAnos(driver);

		if(user_gender == gender_wanted && driver_gender == gender_wanted && user_anos >= anos_conta && driver_anos >= anos_conta) {
			char *driver_name = driverName(driver);
			char *user_name = nameUser(user);
			char *name_user = userRealName(user);
			char data[1024];
			snprintf(data, sizeof(data), "%d;%s;%s;%s\n", driver_id, driver_name, user_name, name_user);
			pushData(buffer, data);
			//printf("Tens um resultado");
			free(driver_name);
			free(user_name);
			free(name_user);
		}

		free(username);
	}

}

void q9_response(Date *inicio, Date *fim,Catalog *c, Buffer *buffer){

	GHashTableIter iter;
	g_hash_table_iter_init(&iter, c->rides);
	void *value = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &value)){
		Ride *ride = (Ride *)value;

		Date *dateRide = getDateRide(ride); 

		if(dateCompare(dateRide,inicio)>=0  &&  dateCompare(fim,dateRide)>=0){
			double tipRide=getTip(ride);

			if(tipRide > 0){
				int rideID = getRideID(ride);
				int distance = getDistance(ride);
				char *cidade = getCidade(ride);
				int dateYear= getYear(dateRide);
				int dateMonth= getMonth(dateRide);
				int dateDay= getDay(dateRide);

				char data[1024];
				snprintf(data, sizeof(data), "%d;%d/%d/%d;%d;%s;%.3f\n", rideID,dateDay,dateMonth,dateYear,distance,cidade,tipRide);
				pushData(buffer, data);
				free(cidade);
				
			}


		}

		free(dateRide);
	}
}