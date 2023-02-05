#include "pages.h"

void paginas(){
	int currentPage = 1;
	int totalPages = (MAX_RESULTS + RESULTS_PER_PAGE - 1) / RESULTS_PER_PAGE;
    int option;

    char *results[MAX_RESULTS];
	FILE* file = fopen("Resultados/command0_output.txt","r");
    if(file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
	
	char buffer[MAX_RESULTS];
    int i = 0;
    while (fgets(buffer, MAX_RESULTS, file) != NULL) {
        results[i] = strdup(buffer);
        i++;
    }

    int exit=0;

    while (!exit) {
    	//system("clear");

        printf("\nMenu de paginação:\n");
        printf("1. Exibir página atual\n");
        printf("2. Próxima página\n");
        printf("3. Página anterior\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf(" %d", &option);

        if (option == 1) {
            int startIndex = (currentPage - 1) * RESULTS_PER_PAGE;
            int endIndex = startIndex + RESULTS_PER_PAGE - 1;
            printf("\nPágina %d de %d\n", currentPage, totalPages);
            printf("Resultados %d a %d:\n", startIndex, endIndex);

            //int end = i;

            for (int i = startIndex; i <= endIndex; i++) {
                if (i < MAX_RESULTS && results[i]!=NULL) {
                    printf("%s ", results[i]);
                }
            }
            printf("\n");
        } else if (option == 2) {
            if (currentPage < totalPages) {
                currentPage++;
            } else {
                printf("Você já está na última página.\n");
            }
        } else if (option == 3) {
            if (currentPage > 1) {
                currentPage--;
            } else {
                printf("Você já está na primeira página.\n");
            }
        } else if (option == 4) {
            printf("Saindo...\n");
            exit=1;
        } else {
            printf("Opção inválida");
        }
	}

    for(int j=0;j<MAX_RESULTS;j++){
        results[j] = NULL;
        buffer[j] = NULL;
    }
}