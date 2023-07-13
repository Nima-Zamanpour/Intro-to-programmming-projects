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
void deposit_buy(char* entery, struct person** Person, int numofpeople) {
	int i=0,j = 0,count=0;
	int good_name_len = 0,seller_name_len=0,count_len=0;
	long int credit = 0,price=0;
	char* good_name;
	char* seller_name;
	int first_time_good_type = 1;
	int seller_availability = 0;
	int good_availability = 0;
	if (entery[0] == 'b') {
		while (entery[i + 4] != ' ') {					//extracting buying info
			good_name_len++;
			i++;
		}
		i = 0;
		while (entery[i + 5 + good_name_len] != ' ') {
			count_len++;
			i++;
		}
		i = 0;
		while (entery[i + 6 + good_name_len + count_len] != '\n') {
			seller_name_len++;
			i++;
		}
		i = 0;
	}
	count = atoi(entery + 5 + good_name_len);
	good_name = malloc((good_name_len + 1) * sizeof(char));
	strncpy(good_name, entery + 4, good_name_len);
	good_name[good_name_len] = NULL;
	seller_name = malloc((seller_name_len + 1) * sizeof(char));
	strncpy(seller_name, entery + 6 + good_name_len + count_len, seller_name_len);
	seller_name[seller_name_len] = NULL;
	
	
	for (i = 0; i < numofpeople; i++) {
		if (Person[i]->log_status == 1) {					//login check
			if (entery[0] == 'd') {							//deposit command
				credit = atoi(entery + 8);

				if (Person[i]->role[0] == 'b')
					if (credit > 0) {
						Person[i]->wallet += credit;
						printf("you deposited %d to your account.\n", credit);
					}
					else printf("enter a positive number!.\n");
				else
					printf("Sellers can't deposit.It is only for buyers\n");
				break;

			}
			else {											//buy command
				if (count > 0)
					for (i = 0; i < numofpeople; i++) {
						if (Person[i]->log_status == 1) {			//check if a user if logged
							if (Person[i]->role[0] == 'b') {			//check if user is buyer
								for (j = 0; j < numofpeople; j++) {
									if (Person[j]->role[0] == 's') {		//picking sellers	
										if (!strncmp(Person[j]->username, seller_name, seller_name_len)) {//matching seller
											for (int k = 0; k < Person[j]->numofgoodtype; k++) {
												if (!strncmp(Person[j]->goods[k]->good_name, good_name, good_name_len)) { //checking good availability.
													good_availability = 1;
													price = Person[j]->goods[k]->price;
													if (Person[j]->goods[k]->count >= count) {
														if (price * count <= Person[i]->wallet) {	//checking if buyer has enough money
															Person[j]->goods[k]->count -= count;	// buying process
															Person[j]->wallet += count * price;
															Person[i]->wallet -= count * price;
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
																Person[i]->goods[(Person[i]->numofgoodtype)]->good_name = malloc((good_name_len + 1) * sizeof(char));
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
																strcpy(Person[i]->goods[(Person[i]->numofgoodtype)]->seller_name, seller_name);
																Person[i]->goods[(Person[i]->numofgoodtype)]->price = price;
																Person[i]->goods[(Person[i]->numofgoodtype)]->count = count;
																Person[i]->numofgoodtype++;
																Person[i]->goods = realloc(Person[i]->goods, (Person[i]->numofgoodtype + 1) * sizeof(struct good*));
																if (Person[i]->goods == NULL) {
																	printf("Error! memory not allocated.");
																	exit(0);
																}
															}
															else {
																for (k = 0; k < Person[i]->numofgoodtype; k++) {
																	if (!strcmp(Person[i]->goods[k]->good_name, good_name)) {
																		Person[i]->goods[k]->count += count;
																		break;
																	}
																}
															}
															printf("buying was successful\n");
															break;					//end of buying proccess
														}
														else
															printf("you don't have enough money\n");
													}
													else
														printf("not enough number of this product is in inventory.\n");
												}
												else
													good_availability = 0;
											}
											seller_availability = 1;
										}

									}
								}
							}
							else
								printf("only buyers can buy\n");
						}
					}
				else
					printf("numbers entered invalid??!!\n");
			}
		}
	}

	if (entery[0] == 'b') {
		if (!good_availability&&seller_availability)
			printf("this seller doesn't have this product.\n");
		if (!seller_availability)
			printf("no seller with this name found.\n");
	}
		int system_occupance = 0; // checking whether anyone entered the system
	for (i = 0; i < numofpeople; i++)
		if (Person[i]->log_status == 1)
			system_occupance = 1;
	if (!system_occupance)
		printf("login first to buy or deposit.\n");
	free(good_name);
	free(seller_name);
}