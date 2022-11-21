#include "queries.h"

void query4(char *cidade,Catalog *c, int linha){

	char comando[25];
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

	//fprintf(query8File,"%s",response);
	writeData(buffer);
	freeBuffer(buffer);
	
}

void parse_queries(Catalog *c, char *commands) {
	//printf("chaguei\n");

	char buffer[200];

	FILE* commands_file = fopen(commands,"r");
	//printf("fiz\n");

	//fgets(buffer, 200, rides); // ignora o cabeçalho

	int linha = 0;
	//printf("%d\n",linha);

	while(fgets(buffer, 200, commands_file)) {
		//printf("%s\n", buffer);
		char *buffer_aux = buffer;
		//printf("%s", buffer_aux);

		int id = atoi(strsep(&buffer_aux, " ")); 
		//printf("%d\n",id);
		linha++;
		//printf("linha %d\n", linha);
		
		switch(id){
			case 1: {
				break;
			} 
			case 2: {
				//int N = atoi(strsep(&buffer_aux, "\n"));

				break;
			}
			case 3: {
				//int N = atoi(strsep(&buffer_aux, "\n"));
				
				break;
			}
			case 4: {
				char *city = (strsep(&buffer_aux, "\n"));
				printf("%s",city);
				query4(city,c,linha);
				break;
			}
			case 5: {
				Date *dateI = dateFromString(strsep(&buffer_aux, " "));
				Date *dateF = dateFromString(strsep(&buffer_aux, "\n"));
				query5(dateI,dateF,c,linha);
				break;
			}
			case 6: {
				char *city = strsep(&buffer_aux, " ");
				Date *dateI = dateFromString(strsep(&buffer_aux, " "));
				Date *dateF = dateFromString(strsep(&buffer_aux, "\n"));
				query6(city,dateI,dateF,c,linha);
				break; 
			}
			case 7: {
				//int N = atoi(strsep(&buffer_aux, " "));
				//char *city = strsep(&buffer_aux, "\n");

				break;
			}
			case 8:{
				char gender_wanted = *strsep(&buffer_aux, " ");
				int anos_conta = atoi(strsep(&buffer_aux, "\n"));
				query8(gender_wanted,anos_conta,c, linha);
				break;
			}
			case 9: {
				Date *dateI = dateFromString(strsep(&buffer_aux, " "));
				Date *dateF = dateFromString(strsep(&buffer_aux, "\n"));
				query9(dateI,dateF,c,linha);
				break;
			}
		}

	}

	fclose(commands_file);

}

/*
void menu_queries(Catalog *c){
	
	printf("---------------- MENU ----------------\n");
	printf("Que query pretende realizar? ");
	int res;
	scanf(" %d",&res); 
	printf("\n");

	printf("%d\n", res);

	switch(res){
		case 1: break;

		case 2: break;

		case 3: break;

		case 4: {
			printf("Indique a cidade: ");
			char cidade[1024];
			scanf(" %s",cidade);

			query4(cidade,c, 0);

			break; 
		}

		case 5: {

			printf("Indique a data de início: ");
			char dataI[1024];
			scanf(" %s",dataI);

			Date* inicio=dateFromString(dataI);

			printf("Indique a data de fim: ");
			char dataF[1024];
			scanf(" %s",dataF);

			Date* fim=dateFromString(dataF);

			query5(inicio,fim,c,0);

			break;
		}

		case 6: {
			printf("Indique a cidade: ");
			char cidade[1024];
			scanf(" %s",cidade);

			printf("Indique a data de início: ");
			char dataI[1024];
			scanf(" %s",dataI);

			Date* inicio=dateFromString(dataI);

			printf("Indique a data de fim: ");
			char dataF[1024];
			scanf(" %s",dataF);

			Date* fim=dateFromString(dataF);

			query6(cidade,inicio,fim,c,0);

			break;
		}

		case 7: break;

		case 8:{
			printf("Indique o género: ");
			char gender_wanted;
			scanf(" %c",&gender_wanted);
		
			//printf("\n");

			printf("Indique os anos: ");
			int anos_conta;
			scanf(" %d",&anos_conta);

			//printf("antes de\n");
			
			query8(gender_wanted,anos_conta,c,0);

			//printf("mim");

			break;
		}
		case 9: {
			printf("Indique a data de início: ");
			char dataI[1024];
			scanf(" %s",dataI);

			Date* inicio=dateFromString(dataI);

			printf("Indique a data de fim: ");
			char dataF[1024];
			scanf(" %s",dataF);

			Date* fim=dateFromString(dataF);

			query9(inicio,fim,c,0);

			break;
		}
	}

}
*/