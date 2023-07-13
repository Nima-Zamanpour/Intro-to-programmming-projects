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
	int log_status;						   //for buyers
	good** goods;
	int numofgoodtype;					   //it's for sellers
}person;
void view_show(char* entery, person** Person, int numofpeople) {
	int i = 0;
	int j = 0;
	int system_occupance = 0; // checking whether anyone entered the system
	for (i = 0; i < numofpeople; i++)
		if (Person[i]->log_status == 1)
			system_occupance = 1;
	if (!system_occupance)
		printf("login first to view items.\n");
	if (entery[0] == 'v')
		for (i = 0; i < numofpeople; i++) {
			if (Person[i]->log_status == 1) {
				if (Person[i]->role[0] == 's') {			//viewing sellers info
					printf("view was successful\n\n");
					printf("your username is :%s\n", Person[i]->username);
					printf("your role is :%s", Person[i]->role);
					printf("your credit is :%d\n", Person[i]->wallet);
					for (j = 0; j < Person[i]->numofgoodtype; j++) {
						printf("\nname of good is :%s\n", Person[i]->goods[j]->good_name);
						printf("number left :%d\n", Person[i]->goods[j]->count);
						printf("good's price :%d\n", Person[i]->goods[j]->price);
					}

				}
				else {										//viewing buyers info
					printf("your username is :%s\n", Person[i]->username);
					printf("your role is :%s", Person[i]->role);
					printf("your credit is :%d\n", Person[i]->wallet);
					for (j = 0; j < Person[i]->numofgoodtype; j++) {
						printf("\nname of good is :%s\n", Person[i]->goods[j]->good_name);
						printf("number left :%d\n", Person[i]->goods[j]->count);
						printf("good's price :%d\n", Person[i]->goods[j]->price);
						printf("good's seller name :%s\n", Person[i]->goods[j]->seller_name);
					}
				}
				break;
			}
		}
	else if (system_occupance) {
		printf("showing goods was successful\n\n");
		for (i = 0; i < numofpeople; i++)
			if (Person[i]->role[0] == 's')
				for (j = 0; j < Person[i]->numofgoodtype; j++) {
					printf("\ngood's name is :%s\n", Person[i]->goods[j]->good_name);
					printf("seller's name is :%s\n", Person[i]->goods[j]->seller_name);
					printf("good's count is :%d\n", Person[i]->goods[j]->count);
					printf("good's price is :%d\n", Person[i]->goods[j]->price);
				}
	}
}	