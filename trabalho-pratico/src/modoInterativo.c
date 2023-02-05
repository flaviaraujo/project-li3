#include "modoInterativo.h"

void menu_queries(Catalog *c,char *path){

	char comando[1024];
   	int maxlen = sizeof comando;
   	snprintf(comando,maxlen, "%sResultados/command0_output.txt",path);
   

	while(1){
		printf("---------------- MENU ----------------\n");
		printf("Bem-vindo ao modo iterativo!\n");
		printf("Temos as seguintes queries disponíveis:\n");
		printf("0. Exit.\n");
		printf("1. Listar o resumo de um perfil registado no serviço através do seu identificador.\n");
		printf("2. Listar os N condutores com maior avaliação média.\n");
		printf("3. Listar os N utilizadores com maior distância viajada.\n");
		printf("4. Preço médio das viagens numa determinada cidade.\n");
		printf("5. Preço médio das viagens num dado intervalo de tempo.\n");
		printf("6. Distância média percorrida, numa determinada cidade, num dado intervalo de tempo.\n");
		printf("7. Top N condutores numa determinada cidade.\n");
		printf("8. Listar todas as viagens nas quais o utilizador e o condutor são do género passado como parâmetro e têm perfis com X ou mais anos.\n");
		printf("9. Listar as viagens nas quais o passageiro deu gorjeta, num certo intervalo de tempo.\n");
		printf("Que query pretende realizar? ");
		int res;
		scanf(" %d",&res); 
		printf("\n");
		//printf("%d\n", res);

		//remove(comando);
		struct timeval start, end;
		
		switch(res){
			case 0:{
				printf("----------------- FIM ----------------\n");
				exit(0);
			}
			case 1: {
				printf("Pretende obter a informação de um user[0] ou driver[1]? ");
				int r;
				scanf(" %d",&r);

				if(r==1){
					printf("Indique o ID: ");
					int id;
					scanf(" %d",&id);

					gettimeofday(&start, NULL);
					query1(r,id,NULL,c,0);
				} else {
					printf("Indique o username: ");
					char username[1024];
					scanf(" %s",username);

					gettimeofday(&start, NULL);
					query1(r,0,username,c,0);
				}
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
				
				//sleep(3);
				paginas();
				remove(comando);
				break;
			}
			case 2: {
				printf("Indique os Top N que quer: ");
				int N;
				scanf(" %d",&N);

				gettimeofday(&start, NULL);
				
				query2(N,c,0);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
				
				//sleep(3);
				paginas();
				remove(comando);
				break;
			}
			case 3:{
				printf("Indique os Top N que quer: ");
				int N;
				scanf(" %d",&N);
				
				gettimeofday(&start,NULL);
				
				query3(N,c,0);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				paginas();
				remove(comando);
				break;
			}
			case 4: {
				printf("Indique a cidade: ");
				char cidade[1024];
				scanf(" %s",cidade);

				gettimeofday(&start,NULL);
				
				query4(cidade,c, 0);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
				
				//sleep(3);
				paginas();
				remove(comando);
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
				
				gettimeofday(&start,NULL);
				
				query5(inicio,fim,c,0);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
				
				//sleep(3);
				paginas();
				remove(comando);
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
				
				gettimeofday(&start,NULL);
				
				query6(cidade,inicio,fim,c,0);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
				
				//sleep(3);
				paginas();
				remove(comando);
				break;
			}
			case 7: {
				printf("Indique os Top N que quer: ");
				int N;
				scanf(" %d",&N);
				printf("Indique a cidade: ");
				char cidade[1024];
				scanf(" %s",cidade);
				
				gettimeofday(&start,NULL);
				
				query7(N,cidade,c,0);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				//sleep(3);
				paginas();
				remove(comando);
				break;
			}
			case 8:{
				printf("Indique o género: ");
				char gender_wanted;
				scanf(" %c",&gender_wanted);
			
				//printf("\n");
				printf("Indique os anos: ");
				int anos_conta;
				scanf(" %d",&anos_conta);
				//printf("antes de\n");
				
				gettimeofday(&start,NULL);
				
				query8(gender_wanted,anos_conta,c,0);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
				//printf("mim");
				
				//sleep(3);
				paginas();
				remove(comando);
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
				
				gettimeofday(&start,NULL);
				
				query9(inicio,fim,c,0);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				//sleep(3);
				paginas();
				remove(comando);
				break;
			}
		}
	}

}