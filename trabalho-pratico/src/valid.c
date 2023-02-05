#include "valid.h"


// valido = 0
// invalido = 1

int valida_restante(char *campo){

	int tamanho = strlen(campo);
	if (tamanho == 0) {
		return 1;

	}
	return 0;
}

int valida_genero(char campo){

	if (!campo) {
		return 1;
	}
	return 0;
}

int valida_classe(char *classe){

	char *classe_car = classe;
	int i = 0;

	while(classe_car[i] != '\0') {
		classe_car[i] = tolower(classe_car[i]);
		i++;
	}

	if (strcmp(classe_car, "premium")== 0 || strcmp(classe_car, "green") == 0 || strcmp(classe_car, "basic") == 0){
		
		return 0;
	}
	
	return 1;
}

int valida_status(char *status){

	char *status_conta = strdup(status);
	int i = 0;
	
	while(status_conta[i] != '\0') {
		status_conta[i] = tolower(status_conta[i]);
		i++;
	}
	status_conta[i-1] = '\0';
	if (strcmp(status_conta, "active")== 0 || strcmp(status_conta, "inactive") == 0){
		return 0;
	}
	
	return 1;
}


int valida_data(char *data){

	//tipo data nn/nn/nnnn
	char* data_dup = strdup(data);
	char *data_aux = data;

	//printf("entra\n");

	if(data_dup[2] != '/' || data_dup[5] != '/') {
		
		return 1;
	}
	else {
		int dia = atoi(strsep(&data_aux, "/"));
		int mes = atoi(strsep(&data_aux, "/"));
		int ano = atoi(data_aux);
		
		char novo_ano[5];
		sprintf(novo_ano,"%d",ano);

		if( dia>=1 && dia<=31 && mes>=1 && mes<=12 && strlen(data_aux)==strlen(novo_ano)) {
			return 0;
		}
		else{
			return 1;
		}
	}

	return 1;
}

// valida campos onde os valores sao inteiros positivos
// distance, score_users e score_drivers
int valida_intpos(char *campos) {

	char * campo = strdup(campos);

	int i = 0;

	while(campo[i]!='\0'){

		if (isdigit(campo[i]) == 0){
			return 1;
		}
		i++;

	}
	int numero = atoi(campo);
	if (numero != 0) {
		return 0;
	}

	return 1;

}

// tip é um inteiro ou decimal maior ou igual a 0
int valida_tip(char *campo) {

	char *tip = strdup(campo);
	int i = 0;
	int ponto = 0;

	while(tip[i]!='\0') {
		if (isdigit(tip[i])==0 && tip[i]!='.'){
			return 1;
		}
		if (tip[i] == '.') {
			ponto++;
		}
		i++;
	}

	if (ponto<=1){
		
		return 0;
	}

	return 1;
}