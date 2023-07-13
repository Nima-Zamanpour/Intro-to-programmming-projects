#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
typedef struct good {                             
	char* good_name;
	char* seller_name;
	long int price;
	int count;
}good;
typedef struct person {
	char* username;
	char* password;
	char* role;
	long int wallet;
	int log_status;
	good** goods;                          //for different kinds of goods.
	int numofgoodtype;
}person;
person* signup(char* entery) {
	int i = 0, username_len = 1, password_len = 0;
	char c;
	while (entery[i + 8] != ' ') {
		username_len++;
		i++;
	}
	i = 0;
	while (entery[i + 8 + username_len] != ' ') {
		password_len++;
		i++;
	}
	i = 0;
	person* Person = (person*)malloc(sizeof(person));
	if (Person == NULL) {
		printf("Error! memory not allocated.");
		exit(0);
	}
	Person->log_status = 0;											//setting users info
	Person->username = malloc((username_len + 1) * sizeof(char));
	if (Person->username == NULL) {
		printf("Error! memory not allocated.");
		exit(0);
	}
	strncpy(Person->username, entery + 7, username_len);
	Person->username[username_len] = NULL;
	Person->password = malloc((password_len + 1) * sizeof(char));
	if (Person->password == NULL) {
		printf("Error! memory not allocated.");
		exit(0);
	}
	strncpy(Person->password, entery + 8 + username_len, password_len);			//setting user's info
	Person->password[password_len] = NULL;
	Person->role = malloc(7 * sizeof(char));
	strcpy(Person->role, entery + 9 + password_len + username_len);
	Person->wallet = 0;
	Person->numofgoodtype = 0;
	Person->goods = (good**)malloc(sizeof(good*));
	if (Person->goods == NULL) {
		printf("Error! memory not allocated.");
		exit(0);
	}
	return Person;
}