#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "array.h"
#include "queries.h"
#include "catalog.h"
#include "modoBatch.h"
#include "modoInterativo.h"
#include <glib.h>

int main(int argc, char *argv[]){
	//falta o argv[1] em cada para eu ler da diretoria
	if(argc == 1) return 0;
	char *path = argv[1];

	GHashTable *users=parse_users(path);
	GHashTable *drivers=parse_drivers(path);
	GHashTable *rides=parse_rides(path);

	//printf("%d\n", g_hash_table_size(rides));	
	//printf("%d\n", g_hash_table_size(users));
	//printf("%d\n", g_hash_table_size(drivers));
	Catalog *c=newCatalog(users,drivers,rides);

	printf("Que modo quer usar? Interativo[1] ou Batch[2] ");
	int res;
	scanf(" %d",&res);
	switch(res){
		case 1:{
			printf("\n");
			printf("Modo interativo ativo.\n");
			printf("\n");
			
			menu_queries(c,path);
			
			break;
		} case 2:{
			printf("\n");
			printf("Modo batch ativo.\n");
			printf("\n");
			
			char *commands = argv[2];
			parse_queries(c,path,commands);

			break;
		}
	}
 

	return 0;
}