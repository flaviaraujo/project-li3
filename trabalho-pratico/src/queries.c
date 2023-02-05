#include "queries.h"

void query1(int r, int id, char *username, Catalog *c, int linha){
	
	char comando[100];
	int maxlen = sizeof comando;


	snprintf(comando,maxlen, "Resultados/command%d_output.txt", linha);

	Buffer *buffer = newBuffer(1024, comando);

	if(r==0){
		q1u_response(username,c,buffer);
	} else q1d_response(id,c,buffer);

	writeData(buffer);
	freeBuffer(buffer);

}

void query2(int N, Catalog *c, int linha){

	char comando[100];
	int maxlen = sizeof comando;


	snprintf(comando,maxlen, "Resultados/command%d_output.txt", linha);

	Buffer *buffer = newBuffer(1024, comando);

	avaliacaoDrivers(N,c, buffer);

	writeData(buffer);
	freeBuffer(buffer);
}

void query3(int N, Catalog *c, int linha){
	char comando[100];
	int maxlen = sizeof comando;


	snprintf(comando,maxlen, "Resultados/command%d_output.txt", linha);

	Buffer *buffer = newBuffer(1024, comando);

	q3_response(N,c,buffer);

	writeData(buffer);
	freeBuffer(buffer);
}

void query4(char *cidade,Catalog *c, int linha){

	char comando[100];
	int maxlen = sizeof comando;


	snprintf(comando,maxlen, "Resultados/command%d_output.txt", linha);

	Buffer *buffer = newBuffer(1024, comando);

	q4_response(cidade,c, buffer);

	writeData(buffer);
	freeBuffer(buffer);
}

void query5(Date *inicio,Date *fim, Catalog *c, int linha){
	
	char comando[100];
	int maxlen = sizeof comando;


	snprintf(comando,maxlen, "Resultados/command%d_output.txt", linha);

	Buffer *buffer = newBuffer(1024, comando);

	q5_response(inicio,fim,c, buffer);

	//fprintf(query8File,"%s",response);
	writeData(buffer);
	freeBuffer(buffer);
	
}

void query6(char *cidade,Date *inicio,Date *fim, Catalog *c, int linha){
	
	char comando[100];
	int maxlen = sizeof comando;


	snprintf(comando,maxlen, "Resultados/command%d_output.txt", linha);

	Buffer *buffer = newBuffer(1024, comando);

	q6_response(cidade,inicio,fim,c, buffer);

	//fprintf(query8File,"%s",response);
	writeData(buffer);
	freeBuffer(buffer);
}	

void query7(int N, char *cidade,Catalog *c,int linha){
	char comando[100];
	int maxlen = sizeof comando;

	snprintf(comando,maxlen, "Resultados/command%d_output.txt", linha);

	Buffer *buffer = newBuffer(1024, comando);

	q7_response(N,cidade,c, buffer);

	writeData(buffer);
	freeBuffer(buffer);
}

void query8(char gender_wanted,int anos_conta,Catalog *c, int linha){
	
	char comando[100];
	int maxlen = sizeof comando;


	snprintf(comando,maxlen, "Resultados/command%d_output.txt", linha);

	Buffer *buffer = newBuffer(1024, comando);

	q8_response(gender_wanted,anos_conta,c, buffer);

	//printf("fiz\n");

	//FILE* query8File = fopen("command8_output.txt","w");

	//fprintf(query8File,"%s",response);
	writeData(buffer);
	freeBuffer(buffer);

	//fclose(query8File);
}

void query9(Date *inicio,Date *fim, Catalog *c, int linha){
	
	char comando[100];
	int maxlen = sizeof comando;

	snprintf(comando,maxlen, "Resultados/command%d_output.txt", linha);

	Buffer *buffer = newBuffer(1024, comando);

	q9_response(inicio,fim,c, buffer);

	writeData(buffer);
	freeBuffer(buffer);
	
}
