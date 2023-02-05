#include "modoBatch.h"

void parse_queries(Catalog *c, char *path, char *commands) {
	//printf("chaguei\n");

	char buffer[200];

	char directory[1024];
	snprintf(directory, sizeof(directory), "%sinput.txt", commands);

	FILE* commands_file = fopen(directory,"r");
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

		struct timeval start, end;

		switch(id){
			case 1: {
				//printf("chaguei á 1\n");
				char *input=strsep(&buffer_aux, "\n");
				int num;
				if (sscanf(input, "%d", &num) == 1) {
					gettimeofday(&start, NULL);
				    query1(1,num,NULL,c,linha);
				} else {
					gettimeofday(&start, NULL);
				    query1(0,0,input,c,linha);
				}
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				validaQueriesB(linha,path,commands);
				break;
			} 
			case 2: {
				int N = atoi(strsep(&buffer_aux, "\n"));

				gettimeofday(&start, NULL);

				query2(N,c,linha);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				validaQueriesB(linha,path,commands);
				break;
			}
			case 3: {
				int N = atoi(strsep(&buffer_aux, "\n"));

				gettimeofday(&start, NULL);

				query3(N,c,linha);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				validaQueriesB(linha,path,commands);
				break;
			}
			case 4: {
				char *city = (strsep(&buffer_aux, "\n"));
				printf("%s",city);
				
				gettimeofday(&start, NULL);

				query4(city,c,linha);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				validaQueriesB(linha,path,commands);
				break;
			}
			case 5: {
				Date *dateI = dateFromString(strsep(&buffer_aux, " "));
				Date *dateF = dateFromString(strsep(&buffer_aux, "\n"));

				gettimeofday(&start, NULL);

				query5(dateI,dateF,c,linha);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				validaQueriesB(linha,path,commands);
				break;
			}
			case 6: {
				char *city = strsep(&buffer_aux, " ");
				Date *dateI = dateFromString(strsep(&buffer_aux, " "));
				Date *dateF = dateFromString(strsep(&buffer_aux, "\n"));

				gettimeofday(&start, NULL);

				query6(city,dateI,dateF,c,linha);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				validaQueriesB(linha,path,commands);
				break; 
			}
			case 7: {
				int N = atoi(strsep(&buffer_aux, " "));
				char *city = strsep(&buffer_aux, "\n");
				
				gettimeofday(&start, NULL);

				query7(N,city,c,linha);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				validaQueriesB(linha,path,commands);
				break;
			}
			case 8:{
				char gender_wanted = *strsep(&buffer_aux, " ");
				int anos_conta = atoi(strsep(&buffer_aux, "\n"));

				gettimeofday(&start, NULL);

				query8(gender_wanted,anos_conta,c, linha);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				validaQueriesB(linha,path,commands);
				break;
			}
			case 9: {
				Date *dateI = dateFromString(strsep(&buffer_aux, " "));
				Date *dateF = dateFromString(strsep(&buffer_aux, "\n"));

				gettimeofday(&start, NULL);

				query9(dateI,dateF,c,linha);
				
				gettimeofday(&end, NULL);
				long seconds = (end.tv_sec - start.tv_sec);
    			long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    			printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);

				validaQueriesB(linha,path,commands);
				break;
			}
		}

	}

	fclose(commands_file);

}