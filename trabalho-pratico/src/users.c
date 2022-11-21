#include "users.h"

#include <string.h>

struct user{

	char *username;
	char *name;
	char gender;
	Date *birth_date;
	Date *account_creation;
	//char *pay_method;
	char *account_status;
	int anos_user;

};


User *newUser(char *username, char *name, char gender, Date *birth_date, Date *account_creation, char *account_status, int anos_user){

	User *new_User=(User *)malloc(sizeof(User));
	new_User->username=strdup(username);
	new_User->name=strdup(name);
	new_User->gender=gender;
	new_User->birth_date=cloneDate(birth_date);
	new_User->account_creation=cloneDate(account_creation);
	new_User->account_status=strdup(account_status);
	new_User->anos_user=anos_user;

	return new_User;
}

int userComparator(const void *a, const void *b){ // const pointer para garantir que elementos nao sao alterados
	const User *u1=(*(User **)a);
	const User *u2=(*(User **)b);


	return strcmp(u1->username, u2->username);
}

int userNameComparator(const void *a, const void *b){
	char *s=a;
	User *u2= ((User *)b);

	return strcmp(s, u2->username);
}

/*void *bSearchU(Array *a,const void *key,int (*comparator)(const void *, const void *)){
	//printf("chega aqui\n");
	//return bsearch(key,a->data,a->n_elem,a->elem_size,comparator);
	
	for(int i=0;i<sizeArray(a);i++){
		User *u=getElement(a,i);
		if(nameUser(u)==key) return u;
	}

	return NULL;

}*/

char userGender(User *u){
	return u->gender;
}

int userAnos(User *u){
	return u->anos_user;
}

char *nameUser(User *u){
	return strdup(u->username);
}

char *userRealName(User *u){
	return strdup(u->name);
}

GHashTable *parse_users(char *path) {

	time_t seconds = time(NULL);
	struct tm* current_time = localtime(&seconds);

	char buffer[200];
	char directory[100];
	snprintf(directory, sizeof(directory), "%s/users.csv", path);

	
	FILE* users = fopen(directory,"r");

	if(users == NULL) return 0;

	fgets(buffer, 200, users); // ignora o cabeçalho

	//Array* a=newArray(200,sizeof(User));
	GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);

	while(fgets(buffer, 200, users)) {

		char *buffer_aux = buffer;

		char *username = (strsep(&buffer_aux, ";")); // strsep - vai dar o que ĺê até ao primeiro ;  
		char *name = (strsep(&buffer_aux, ";"));
		char gender = *strsep(&buffer_aux, ";");
		Date *birth_date = dateFromString(strsep(&buffer_aux, ";"));
		Date *account_creation = dateFromString(strsep(&buffer_aux, ";"));
		strsep(&buffer_aux,";"); //para ignorar pay_method
		char *account_status = (strsep(&buffer_aux, ";"));

		int anos_user=(current_time->tm_year + 1900)-(getYear(account_creation));
		

		User* u = newUser(username,name,gender,birth_date,account_creation,account_status,anos_user);

		g_hash_table_insert(hash, (u->username), u);
/*
		int x=addToArray(a,u);
		if(x==0){
			printf("ERRO");
			return 0;
		}
*/

	}

	fclose(users);

//	printf("%d\n", sizeArray(a));

//	sortArray(a, userComparator);

	return hash;

}