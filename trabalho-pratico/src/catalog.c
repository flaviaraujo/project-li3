#include "catalog.h"

struct catalog{
	GHashTable *users;
	GHashTable *drivers;
	GHashTable *rides;
};

struct entradaQ2{
	int id;
	char *name;
	float score;
	int trips;
	Date *lastTrip;
};

struct entradaQ3{
	char *username;
	char *realName;
	int distancia;
	Date *lastTrip;
};

struct entradaQ7{
	int id;
	char *name;
	float score;
	int trips;
};

struct entradaQ8 {
	int id;
	int dId;
    //char uGender;
    //char dGender;
    int uAnos;
    int dAnos;
    char *userName;
    char *dName;
    char *uName;
};

struct entradaQ9{
	Date *data;
	int year;
	int month;
	int day;
	int id;
	int distancia;
	char *city;
	float tip;
};

int compare_entradaQ2_score(const void *a, const void *b) {
  	struct entradaQ2 *ia = *(struct entradaQ2 **)a;
  	struct entradaQ2 *ib = *(struct entradaQ2 **)b;
  	if (ib->score > ia->score)
    	return 1;
  	else if (ib->score < ia->score)
    	return -1;
  	else if (dateCompare(ib->lastTrip, ia->lastTrip)==0){
  		if (ib->id < ia->id) 
  			return -1;
  		else return 1;
  	} 
  	else
    	return dateCompare(ib->lastTrip, ia->lastTrip);
}

int compareQ7_score(const void *a, const void *b) {
  	struct entradaQ7 *ia = *(struct entradaQ7 **)a;
  	struct entradaQ7 *ib = *(struct entradaQ7 **)b;
  	if (ib->score > ia->score)
    	return 1;
  	else if (ib->score < ia->score)
    	return -1;
  	else
    	return ib->id - ia->id;
}

int compareQ8_years(const void *a, const void *b) {
  	struct entradaQ8 *ia = *(struct entradaQ8 **)a;
  	struct entradaQ8 *ib = *(struct entradaQ8 **)b;
  	if (ib->dAnos > ia->dAnos)
    	return 1;
  	else if (ib->dAnos < ia->dAnos)
    	return -1;
  	else if(ib->dAnos == ia->dAnos) {
  		if(ib->uAnos > ia->uAnos)
  			return 1;
  		else if (ib->uAnos < ia->uAnos)
  			return -1;
  		else return ia->id - ib->id;
  	}
}

int compare_entradaQ3_distancia(const void *a, const void *b) {
  	struct entradaQ3 *ia = *(struct entradaQ3 **)a;
  	struct entradaQ3 *ib = *(struct entradaQ3 **)b;
  	if (ib->distancia > ia->distancia)
    	return 1;
  	else if (ib->distancia < ia->distancia)
    	return -1;
  	else if (dateCompare(ib->lastTrip,ia->lastTrip)==0){
  		if(strcmp(ia->username,ib->username)>0)
  			return 1;
  		else return -1;
  	}
  	else
    	return dateCompare(ib->lastTrip, ia->lastTrip);
}

int compareQ9(const void *a, const void *b) {
  	struct entradaQ9 *ia = *(struct entradaQ9 **)a;
  	struct entradaQ9 *ib = *(struct entradaQ9 **)b;
  	if (ib->distancia > ia->distancia)
    	return 1;
  	else if (ib->distancia < ia->distancia)
    	return -1;
  	else if (dateCompare(ib->data,ia->data)==0){
  		if(ib->id > ia->id)
  			return 1;
  		else return -1;
  	}
  	else
    	return dateCompare(ib->data, ia->data);
}


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

void q1u_response(char *username,Catalog *c, Buffer *buffer){
	Date *today=newDate(9,10,2022);

	User *user = g_hash_table_lookup(c->users, username);
	if(user == NULL) {
		//printf("Algum driver nao foi encontrado\n");
		return;
	}
	
	char *name_user = userRealName(user);
	char user_gender = userGender(user);
	Date *birth=getBirthDate(user);
	//printf("%d/%d/%d\n",getDay(birth),getMonth(birth),getYear(birth));
	int idade = findAge(birth,today);

	double listScore=0.000;
	int trips=0;
	double precoB=3.25;
	double precoG=4;
	double precoP=5.20;
	double precoViagem=0;

	GHashTableIter iter;
	g_hash_table_iter_init(&iter, c->rides);
	void *value = NULL;

	while(g_hash_table_iter_next(&iter, NULL, &value)){
		Ride *ride = (Ride *)value;
		char *rideUser=getRideUser(ride);

		if(strcmp(rideUser,username)==0){
			trips++;
			listScore+=getScoreUser(ride);
			
			int driver_id = getRideDriver(ride);
			Driver *driver = g_hash_table_lookup(c->drivers, &driver_id);
			if(driver == NULL) {
				//printf("Algum driver nao foi encontrado\n");
				return;
			}

			char *class=getClass(driver);
			double distancia=getDistance(ride);	
			float tip=getTip(ride);		

			if(strcmp(class,"basic")==0){					
				precoViagem=precoViagem+precoB+0.62*distancia+tip;
			}

			else if(strcmp(class,"green")==0){
				precoViagem=precoViagem+precoG+0.79*distancia+tip;
			}

			else if(strcmp(class,"premium")==0){
				precoViagem=precoViagem+precoP+0.94*distancia+tip;
			}

		}
	}


	double scoreMedia=listScore/trips;
	
	char data[1024];
	snprintf(data, sizeof(data), "%s;%c;%d;%.3f;%d;%.3f\n", name_user,user_gender,idade,scoreMedia,trips,precoViagem);
	pushData(buffer, data);
}

void q1d_response(int id,Catalog *c, Buffer *buffer){
	Date *today=newDate(9,10,2022);

	Driver *driver = g_hash_table_lookup(c->drivers, &id);
	if(driver == NULL) {
		//printf("Algum driver nao foi encontrado\n");
		return;
	}

	char *name_driver = driverName(driver);
	char driver_gender = driverGender(driver);
	int idade = findAge(getBirthDateD(driver),today);

	char *class=getClass(driver);

	double listScore=0.000;
	int trips=0;
	double precoB=3.25;
	double precoG=4;
	double precoP=5.20;
	double precoViagem=0;

	GHashTableIter iter;
	g_hash_table_iter_init(&iter, c->rides);
	void *value = NULL;

	while(g_hash_table_iter_next(&iter, NULL, &value)){
		Ride *ride = (Ride *)value;
		int driverID=getRideDriver(ride);

		if(driverID==id){
			trips++;
			listScore+=getScoreDriver(ride);
			
			double distancia=getDistance(ride);	
			float tip=getTip(ride);		

			if(strcmp(class,"basic")==0){					
				precoViagem=precoViagem+precoB+0.62*distancia+tip;
			}

			else if(strcmp(class,"green")==0){
				precoViagem=precoViagem+precoG+0.79*distancia+tip;
			}

			else if(strcmp(class,"premium")==0){
				precoViagem=precoViagem+precoP+0.94*distancia+tip;
			}

		}
	}


	double scoreMedia=listScore/trips;
	
	char data[1024];
	snprintf(data, sizeof(data), "%s;%c;%d;%.3f;%d;%.3f\n", name_driver,driver_gender,idade,scoreMedia,trips,precoViagem);
	pushData(buffer, data);


}


void avaliacaoDrivers(int N, Catalog *c, Buffer *buffer) {
  	GHashTableIter iter;
  	GHashTable *answer = g_hash_table_new(g_int_hash, g_int_equal);
  	g_hash_table_iter_init(&iter, c->drivers);
  	void *value = NULL;

  	//int size = g_hash_table_size(c->drivers);

  	// struct entradaQ2 array[size];

  	// int i=0;
  	while (g_hash_table_iter_next(&iter, NULL, &value)) {
    	Driver *driver = (Driver *)value;

    	int driver_id = driverID(driver);
    	char *driver_name = driverName(driver);

    	struct entradaQ2 *aux =
        	(struct entradaQ2 *)malloc(sizeof(struct entradaQ2));
	    aux->id = driver_id;
	    aux->name = driver_name;
	    aux->score = 0.000;
	    aux->trips = 0;
	    aux->lastTrip = newDate(0, 0, 0);
	    g_hash_table_insert(answer, &aux->id, aux);

	    /*
	    //array[i] = {driver_id,driver_name,0.000,0,newDate(0,0,0)};
	    array[i].id=driver_id;
	    array[i].name=driver_name;
	    array[i].score=0.000;
	    //array[i].trips=0;
	    array[i].lastTrip=newDate(0,0,0);

	    i++;*/
  	}

  	g_hash_table_iter_init(&iter, c->rides);
  	void *value2 = NULL;

  	while (g_hash_table_iter_next(&iter, NULL, &value2)) {
	    Ride *ride = (Ride *)value2;
	    Date *ride_date = getDateRide(ride);

	    const int driver_id = getRideDriver(ride);

	    struct entradaQ2 *aux = g_hash_table_lookup(answer, &driver_id);
	    if (aux == NULL)
	      continue;
	    aux->trips++;
	    aux->score += getScoreDriver(ride);
	    if (dateCompare(ride_date, aux->lastTrip) == 1) {
	      	aux->lastTrip = ride_date;
		}

    /*
    for(int j=0;j<size;j++){
            if(array[j].id==driver_id){
                    array[j].score+=getScoreDriver(ride);
                    array[j].trips++;

                    if(dateCompare(ride_date,array[j].lastTrip)==1){
                            array[j].lastTrip=ride_date;
                    }

            }
    }
    */
   	}

  /*for(int a=0;a<size;a++){
          array[a].score=array[a].score/array[a].trips;
  }*/

  // struct entradaQ2 aux = {0,NULL,0.000,0,newDate(0,0,0)};
  // struct entradaQ2 *aux2 = (struct entradaQ2 *)malloc(sizeof(struct
  // entradaQ2)); aux2->id = driver_id; aux2->name = driver_name; aux2->score =
  // 0.000;
  // // aux2->trips=0;
  // aux2->lastTrip = newDate(0, 0, 0);
  // g_hash_table_insert(answer, &aux2->id, aux2);

  // g_hash_table_iter_init(&iter, aux);
  // void *value2 = NULL;

  	const unsigned int size_answer = g_hash_table_size(answer);
  	struct entradaQ2 *array[size_answer];

  	g_hash_table_iter_init(&iter, answer);
  	unsigned int index = 0;

  	while (g_hash_table_iter_next(&iter, NULL, &value2)) {
    	struct entradaQ2 *aux = (struct entradaQ2 *)value2;
    	aux->score /= aux->trips;
    	array[index++] = aux;
  	}

  	qsort(array, size_answer, sizeof(struct entradaQ2 *),
  		compare_entradaQ2_score);

  /*
          for(int e = 0; e < size; ++e){
                  for(int f = e + 1; f < size; ++f){
                          if(aux->score < )
                          if(array[e].score < array[f].score){
                                  aux = array[e];
                                  array[e] = array[f];
                                  array[f] = aux;
              }
              else if (array[e].score == array[f].score){
                  if(dateCompare(array[e].lastTrip,array[f].lastTrip)==-1){
                          aux = array[e];
                                          array[e] = array[f];
                                          array[f] = aux;
                  }
                  else if(dateCompare(array[e].lastTrip,array[f].lastTrip)==0){
                          if(array[e].id > array[f].id){
                                  aux = array[e];
                                                  array[e] = array[f];
                                                  array[f] = aux;
                          }
                  }
              }
          }
      }
  */

  	for (int g = 0; g < N; g++) {
    	char data[1024];
    	snprintf(data, sizeof(data), "%d;%s;%.3f\n", array[g]->id, array[g]->name, array[g]->score);
    	pushData(buffer, data);

    	g_hash_table_iter_init(&iter, answer);
    	while (g_hash_table_iter_next(&iter, NULL, &value)) {
        	struct entradaQ2 *aux = (struct entradaQ2 *)value;
    	}
  	}
}

void q3_response(int N, Catalog *c, Buffer *buffer) {
  	GHashTableIter iter;
  	g_hash_table_iter_init(&iter, c->users);
  	void *value = NULL;

  	GHashTable *answer = g_hash_table_new(g_str_hash, g_str_equal);

  	int i = 0;
  	while (g_hash_table_iter_next(&iter, NULL, &value)) {
    	User *user = (User *)value;

    	char *username = nameUser(user);
    	char *user_name = userRealName(user);

    	// array[i] = {username,user_name,0,newDate(0,0,0)};
    	struct entradaQ3 *aux =
        	(struct entradaQ3 *)malloc(sizeof(struct entradaQ3));
    	aux->username = username;
	    aux->realName = user_name;
	    aux->distancia = 0;
	    aux->lastTrip = newDate(0, 0, 0);
	    g_hash_table_insert(answer, aux->username, aux);
	    // array[i].username = username;
	    // array[i].realName = user_name;
	    // array[i].distancia = 0;
	    // array[i].lastTrip = newDate(0, 0, 0);

	    i++;
	}

  	g_hash_table_iter_init(&iter, c->rides);
  	void *value2 = NULL;

  	while (g_hash_table_iter_next(&iter, NULL, &value2)) {
	    Ride *ride = (Ride *)value2;
	    char *rideUsername = getRideUser(ride);
	    Date *ride_date = getDateRide(ride);

	    struct entradaQ3 *aux =
	        (struct entradaQ3 *)g_hash_table_lookup(answer, rideUsername);
	    if (aux != NULL) {
	      aux->distancia += getDistance(ride);
	      if (dateCompare(ride_date, aux->lastTrip) == 1) {
	        aux->lastTrip = ride_date;
	      }
    	}

    // for (int j = 0; j < size; j++) {
    //   if (strcmp(rideUsername, array[j].username) == 0) {
    //     array[j].distancia += getDistance(ride);

    //    if (dateCompare(ride_date, array[j].lastTrip) == 1) {
    //      array[j].lastTrip = ride_date;
    //    }
    //  }
    //}
  	}

  	const size_t size = g_hash_table_size(answer);
  	struct entradaQ3 *array[size];
  	int index = 0;

  	g_hash_table_iter_init(&iter, answer);
  	while (g_hash_table_iter_next(&iter, NULL, &value2)) {
    	struct entradaQ3 *aux = (struct entradaQ3 *)value2;
    	array[index++] = aux;
  	}

  	qsort(array, size, sizeof(struct entradaQ3 *), compare_entradaQ3_distancia);

  // struct entradaQ3 aux = {NULL, NULL, 0, newDate(0, 0, 0)};

  // for (int e = 0; e < size; ++e) {
  //   for (int f = e + 1; f < size; ++f) {
  //     if (array[e].distancia < array[f].distancia) {
  //       aux = array[e];
  //       array[e] = array[f];
  //       array[f] = aux;
  //     } else if (array[e].distancia == array[f].distancia) {
  //       if (dateCompare(array[e].lastTrip, array[f].lastTrip) == -1) {
  //         aux = array[e];
  //         array[e] = array[f];
  //         array[f] = aux;
  //       } else if (dateCompare(array[e].lastTrip, array[f].lastTrip) == 0) {
  //         if (strcmp(array[e].username, array[f].username) > 0) {
  //           aux = array[e];
  //           array[e] = array[f];
  //           array[f] = aux;
  //         }
  //       }
  //     }
  //   }
  // }
  	//printf("\n");
  	for (int g = 0; g < N; g++) {
    	char data[1024];
    	snprintf(data, sizeof(data), "%s;%s;%d\n", array[g]->username,array[g]->realName, array[g]->distancia);
    	//printf("%s",data);
    	pushData(buffer, data);
  	}
  	//printf("\n");
}

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

void q7_response(int N, char *cidade, Catalog *c, Buffer *buffer) {
  	GHashTableIter iter;
  	g_hash_table_iter_init(&iter, c->drivers);
  	void *value = NULL;
  	GHashTable *hash = g_hash_table_new(g_int_hash, g_int_equal);
  	// int size = g_hash_table_size(c->drivers);

  	// int i = 0;
  	while (g_hash_table_iter_next(&iter, NULL, &value)) {
	    Driver *driver = (Driver *)value;

	    int driver_id = driverID(driver);
	    char *driver_name = driverName(driver);

	    struct entradaQ7 *entrada =
	        (struct entradaQ7 *)malloc(sizeof(struct entradaQ7));
	    entrada->id = driver_id;
	    entrada->name = driver_name;
	    entrada->score = 0.000;
	    entrada->trips = 0;
	    g_hash_table_insert(hash, &entrada->id, entrada);
	    // array[i].id = driver_id;
	    // array[i].name = driver_name;
	    // array[i].score = 0.000;
	    // array[i].trips = 0;
  	}

  	g_hash_table_iter_init(&iter, c->rides);
  	void *value2 = NULL;

  	while (g_hash_table_iter_next(&iter, NULL, &value2)) {
	    Ride *ride = (Ride *)value2;
	    char *cityRide = getCidade(ride);
	    int driver_id = getRideDriver(ride);
	    struct entradaQ7 *entrada =
	        (struct entradaQ7 *)g_hash_table_lookup(hash, &driver_id);
	    if (entrada != NULL) {
	      if (strcmp(cityRide, cidade) == 0) {
	        entrada->score += getScoreDriver(ride);
	        entrada->trips++;
	      }
	    }

    // for (int j = 0; j < size; j++) {
    //   if (strcmp(cityRide, cidade) == 0 && array[j].id == driver_id) {
    //     array[j].score += getScoreDriver(ride);
    //     array[j].trips++;
    //   }
    // }
  	}

  // for (int a = 0; a < size; a++) {
  //   array[a].score = array[a].score / array[a].trips;
  // }
  //
  	const size_t size = g_hash_table_size(hash);
  	struct entradaQ7 *array[size];
  	g_hash_table_iter_init(&iter, hash);
  	int index = 0;
  	while (g_hash_table_iter_next(&iter, NULL, &value)) {
    	struct entradaQ7 *entrada = (struct entradaQ7 *)value;
    	entrada->score = entrada->score / entrada->trips;
    	array[index++] = entrada;
  	}

  	qsort(array, size, sizeof(struct entradaQ7 *), compareQ7_score);

  // for (int e = 0; e < size; ++e) {
  //   for (int f = e + 1; f < size; ++f) {
  //     if (array[e].score < array[f].score) {
  //       aux = array[e];
  //       array[e] = array[f];
  //       array[f] = aux;
  //     } else if (array[e].score == array[f].score) {
  //       if (array[e].id > array[f].id) {
  //         aux = array[e];
  //         array[e] = array[f];
  //         array[f] = aux;
  //       }
  //     }
  //   }
  // }
  	//printf("\n");
  	for (int g = 0; g < N; g++) {
    	char data[1024];
    	snprintf(data, sizeof(data), "%d;%s;%.3f\n", array[g]->id, array[g]->name,array[g]->score);
    	//printf("%s",data);
    	pushData(buffer, data);
  	}
  	//printf("\n");
}

void q8_response(char gender_wanted,int anos_conta,Catalog *c, Buffer *buffer){
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, c->rides);
	void *value = NULL;

	GHashTable *hash = g_hash_table_new(g_int_hash, g_int_equal);

	while(g_hash_table_iter_next(&iter, NULL, &value)) {
		Ride *ride = (Ride *)value;
		int id = getRideID(ride);
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
			//char *user_name = nameUser(user);
			char *name_user = userRealName(user);

			struct entradaQ8 *entrada =
		        (struct entradaQ8 *)malloc(sizeof(struct entradaQ8));
		    entrada->id = id;
		    entrada->dId = driver_id;
		    //entrada->uGender = user_gender;
		    //entrada->dGender = driver_gender;
		    entrada->uAnos = user_anos;
		    entrada->dAnos = driver_anos;
		    entrada->userName = username;
		    entrada->dName = driver_name;
		    entrada->uName = name_user;
		    g_hash_table_insert(hash, &entrada->id, entrada);

			/*char data[1024];
			snprintf(data, sizeof(data), "%d;%s;%s;%s\n", driver_id, driver_name, user_name, name_user);
			pushData(buffer, data);
			//printf("Tens um resultado");
			free(driver_name);
			free(user_name);
			free(name_user);*/
		}

		//free(username);
	}

	const size_t size = g_hash_table_size(hash);
  	struct entradaQ8 *array[size];
  	g_hash_table_iter_init(&iter, hash);
  	int index = 0;
  	while (g_hash_table_iter_next(&iter, NULL, &value)) {
    	struct entradaQ8 *entrada = (struct entradaQ8 *)value;
    	array[index++] = entrada;
  	}

  	qsort(array, size, sizeof(struct entradaQ8 *), compareQ8_years);
  	
  	for (int g = 0; g < size; g++) {
    	char data[1024];
    	snprintf(data, sizeof(data), "%d;%s;%s;%s\n", array[g]->dId, array[g]->dName,array[g]->userName,array[g]->uName);
    	//printf("%d driver, %d user, %d trip\n",array[g]->dAnos,array[g]->uAnos,array[g]->id);
    	pushData(buffer, data);
  	}

}

void q9_response(Date *inicio, Date *fim,Catalog *c, Buffer *buffer){
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, c->rides);
	void *value = NULL;

	GHashTable *hash = g_hash_table_new(g_int_hash, g_int_equal);

	while(g_hash_table_iter_next(&iter, NULL, &value)){
		Ride *ride = (Ride *)value;

		Date *dateRide = getDateRide(ride); 

		if(dateCompare(dateRide,inicio)>=0  &&  dateCompare(fim,dateRide)>=0){
			float tipRide=getTip(ride);
			//printf("%.3f\n",tipRide);

			if(tipRide > 0){
				int rideID = getRideID(ride);
				int distance = getDistance(ride);
				char *cidade = getCidade(ride);
				int dateYear= getYear(dateRide);
				int dateMonth= getMonth(dateRide);
				int dateDay= getDay(dateRide);

				struct entradaQ9 *entrada =
		        	(struct entradaQ9 *)malloc(sizeof(struct entradaQ9));
		        entrada->data = dateRide;
			    entrada->id = rideID;
			    entrada->distancia = distance;
			    entrada->city = cidade;
			    entrada->year = dateYear;
			    entrada->month = dateMonth;
			    entrada->day = dateDay;
			    entrada->tip = tipRide;
			    g_hash_table_insert(hash, &entrada->id, entrada);

			    /*
				char data[1024];
				snprintf(data, sizeof(data), "%d;%d/%d/%d;%d;%s;%.3f\n", rideID,dateDay,dateMonth,dateYear,distance,cidade,tipRide);
				pushData(buffer, data);
				free(cidade);
				*/
			}
		}
	}
	const size_t size = g_hash_table_size(hash);
  	struct entradaQ9 *array[size];
	g_hash_table_iter_init(&iter, hash);
	int index = 0;
	while (g_hash_table_iter_next(&iter, NULL, &value)) {
	    struct entradaQ9 *entrada = (struct entradaQ9 *)value;
	    array[index++] = entrada;
	}

	qsort(array, size, sizeof(struct entradaQ9 *), compareQ9);

	for (int g = 0; g < size; g++) {
	    char data[1024];
	    snprintf(data, sizeof(data), "%d;%d/%d/%d;%d;%s;%.3f\n", array[g]->id, array[g]->day,array[g]->month,array[g]->year,array[g]->distancia,array[g]->city,array[g]->tip);
	    //printf("%.3f\n",array[g]->tip);
	    pushData(buffer, data);
	}
	
}
