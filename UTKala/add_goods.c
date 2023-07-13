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
void add_goods(char* entery, struct person** Person, int numofpeople) {
	int i = 0, j = 0, k = 0, count = 0;
	int good_name_len = 0, good_count_len = 0, good_price_len = 0,seller_name_len=0;
	long int price = 0;
	char* good_name;
	int first_time_good_type = 1;								//first time a seller adds a new kind of goods
	int add_goods_grant = 1;
	while (entery[i + 10] != ' ') {					//extracting buying info
		good_name_len++;
		i++;
	}
	i = 0;
	while (entery[i + 11 + good_name_len] != ' ') {	//len of good price
		good_price_len++;
		i++;
	}
	i = 0;
	while (entery[i + 12 + good_name_len + good_price_len] != '\n') {
		good_count_len++;
		i++;
	}
	i = 0;

	price = atoi(entery + 11 + good_name_len);
	good_name = malloc((good_name_len + 1) * sizeof(char));
	if (good_name == NULL) {
		printf("Error! memory not allocated.");
		exit(0);
	}
	strncpy(good_name, entery + 10, good_name_len);
	good_name[good_name_len] = NULL;
	count = atoi(entery + 12 + good_name_len + good_price_len);
	if(count>0&&price>0)
	for (i = 0; i < numofpeople; i++) {
		if (Person[i]->log_status == 1) {
			if (Person[i]->role[0] == 's') {				//picking sellers
				for (j = 0; j < numofpeople; j++) {			//checking whether anyone already added this good
					if (j == i) {
						if (j < numofpeople - 1)
							j++;
						else 
							break;
					}
					for (k = 0; k < Person[j]->numofgoodtype; k++) {
						if (!strcmp(Person[j]->goods[k]->good_name, good_name))
							if(Person[j]->role[0]=='s')
							add_goods_grant = 0;
					}
					
				}
				if (add_goods_grant) {								//adding goods
					for (k = 0; k < Person[i]->numofgoodtype; k++) {
						if (!strcmp(Person[i]->goods[k]->good_name, good_name))
							first_time_good_type = 0;
					}
					if (first_time_good_type) {			
						Person[i]->goods[(Person[i]->numofgoodtype)] = malloc(sizeof(struct good));
						if (Person[i]->goods[Person[i]->numofgoodtype] == NULL) {
							printf("Error! memory not allocated.");
							exit(0);
						}
						Person[i]->goods[(Person[i]->numofgoodtype)]->good_name = malloc((good_name_len+1) * sizeof(char));
						if (Person[i]->goods[Person[i]->numofgoodtype]->good_name == NULL) {
							printf("Error! memory not allocated.");
							exit(0);
						}
						strcpy(Person[i]->goods[(Person[i]->numofgoodtype)]->good_name, good_name);
						seller_name_len = strlen(Person[i]->username);
						Person[i]->goods[(Person[i]->numofgoodtype)]->seller_name = malloc((seller_name_len + 1) * sizeof(char));
						if (Person[i]->goods[Person[i]->numofgoodtype]->seller_name == NULL) {
							printf("Error! memory not allocated.");
							exit(0);
						}
						strcpy(Person[i]->goods[(Person[i]->numofgoodtype)]->seller_name,Person[i]->username);
						Person[i]->goods[(Person[i]->numofgoodtype)]->price = price;
						Person[i]->goods[(Person[i]->numofgoodtype)]->count = count;
						Person[i]->numofgoodtype++;
						Person[i]->goods = realloc(Person[i]->goods, (Person[i]->numofgoodtype + 1)*sizeof(struct good*));
						if (Person[i]->goods == NULL) {
							printf("Error! memory not allocated.");
							exit(0);
						}
					}
					else{			//for goods that are already added malloc isn't needed
						for (k = 0; k < Person[i]->numofgoodtype; k++) {
							if (!strcmp(Person[i]->goods[k]->good_name, good_name)) {
								Person[i]->goods[k]->count += count;
								break;
							}
						}
					}
					printf("goods were added successfuly\n");
				}
				else {
					printf("this product is already in the inventory of another seller.You can't add this good.\n");
					break;
				}



			}
			else {
				printf("buyers can't add goods.\n");
				break;
			}
		}
	}
	else {
		printf("price or count can't be negetive!!??\n");
	}
	free(good_name);
	int system_occupance = 0; // checkign whether anyone entered the system
	for (i = 0; i < numofpeople; i++)
		if (Person[i]->log_status == 1)
			system_occupance = 1;
	if (!system_occupance)
		printf("login first to add goods.\n");
}