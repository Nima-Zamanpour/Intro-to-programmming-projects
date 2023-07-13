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
void log(char* entery, struct person** Person, int numofpeople) {
	int i = 0, username_len = 1, password_len = 0,no_match=1;
	char c;
	int login_success = 0, logout_success = 0, system_occupance = 0;
	if (entery[3] == 'i') {
		while (entery[i + 7] != ' ') {
			username_len++;
			i++;
		}
		i = 0;
		while (entery[i + 7 + username_len] != ' ') {
			password_len++;
			i++;
		}
	}
	
	i = 0;
	char* username = (char*)malloc((username_len + 1) * sizeof(char));
	char* password = (char*)malloc((password_len + 1) * sizeof(char));
	strncpy(username, entery + 6, username_len);
	username[username_len] = NULL;
	strncpy(password, entery + 7 + username_len, password_len);
	password[password_len] = NULL;
	for (i = 0; i < numofpeople; i++) {			//checking system occupance and username match
		if (Person[i]->log_status == 1)
			system_occupance = 1;
		if (!strcmp(username, Person[i]->username))
			no_match = 0;
	}

	if (entery[3] == 'i') {
		for (i = 0; i < numofpeople; i++) {
			if (!strcmp(username, Person[i]->username))
				if (!strcmp(password, Person[i]->password))
					if (Person[i]->role[0] == entery[8 + username_len + password_len]) {
						if (Person[i]->log_status == 0)
							if (!system_occupance) {
								Person[i]->log_status = 1;
								login_success = 1;
								break;
							}
							else
								printf("a person is already logged in.\n");
					}
		}
		if (login_success)
			printf("login was successful\n");
		else
			printf("login was not successful\n");
		if (no_match)
			printf("no user with this username found.\n");
	}
	else {
		for (i = 0; i < numofpeople; i++) {
			if (Person[i]->log_status == 1) {
				Person[i]->log_status = 0;
				logout_success = 1;
				break;
			}

		}
		if (logout_success)
			printf("logout was successful\n");
		else
			printf("logout was not successful.nobody is logged in.\n");
	}
	free(username);
	free(password);
}