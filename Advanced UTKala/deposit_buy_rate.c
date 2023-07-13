#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"


void deposit_buy_rate(char* entery, struct person* root) {
	int good_name_len = 0, seller_name_len = 0, count_len = 0, changed_price_rate = 0;
	long int credit = 0, price = 0;
	char* good_name;
	char* seller_name;
	int first_time_good_type = 1, entery_i = 0;
	int seller_availability = 0, i = 0, rate = 0;
	int good_availability = 0, count = 0, has_good = 0;
	person* temp = root, * seller_temp = root;//a temporary pointer to people
	good* good_temp, * GS_temp;
	temp = log_check(root);   //temp is the logged in person if there is anyone logged in
	if (!temp) {
		switch (entery[0]) {
		case 98:
			printf("login first to buy.\n");
			break;
		case 100:
			printf("login first to deposit.\n");
			break;
		case 114:
			printf("login first to rate.\n");
		}
		return;
	}
	if (entery[0] == 'b')		//switches from buy to rate
		entery_i = 4;
	else if (entery[0] == 'r')
		entery_i = 11;
	if (entery[0] != 'd') {
		while (entery[i + entery_i] != ' ') {					//extracting buying info
			good_name_len++;
			i++;
		}
		i = 0;
		while (entery[i + entery_i + 1 + good_name_len] != ' ') {
			count_len++;
			i++;
		}
		i = 0;
		if (entery[0] == 'r')
			credit = count_len + 1;
		while (entery[i + entery_i + 2 + good_name_len + count_len - credit] != '\n') {
			seller_name_len++;
			i++;
		}
	}
	i = 0;
	if (entery[0] == 'd') {							//deposit command
		credit = atoi(entery + 8);
		if (temp->role[0] == 'b')
			if (credit > 0) {
				temp->wallet += credit;
				printf("you deposited %d to your account.\n", credit);
			}
			else printf("enter a positive number!.\n");
		else
			printf("Sellers can't deposit.It is only for buyers\n");
	}
	else if (entery[0] == 'b') { // buying command
		good_name = malloc((good_name_len + 1) * sizeof(char));
		strncpy(good_name, entery + entery_i, good_name_len);
		good_name[good_name_len] = NULL;
		seller_name = malloc((seller_name_len + 1) * sizeof(char));
		strncpy(seller_name, entery + entery_i + 2 + good_name_len + count_len, seller_name_len);
		seller_name[seller_name_len] = NULL;
		count = atoi(entery + 1 + entery_i + good_name_len);										//buy command
		if (count > 0)
			if (temp->role[0] == 'b') {			//check if user is buyer
				while (seller_temp) {
					has_good = 1;
					if (seller_temp->role[0] == 's') {		//picking sellers	
						if (alphabet_check(seller_temp->username, seller_name)==0) {	//matching seller
							GS_temp = seller_temp->goods;
							seller_availability = 1;
							while (GS_temp) {
								if (((alphabet_check(GS_temp->good_name, good_name)==0) && ((
									GS_temp->rate >= 2 && GS_temp->numofrate > 4) || GS_temp->numofrate <= 4))) { //checking good availability.
									good_availability = 1;
									price = GS_temp->price;
									if (GS_temp->count >= count) {
										if (price * count <= temp->wallet) {	//checking if buyer has enough money
											GS_temp->count -= count;	// buying process
											seller_temp->wallet += count * price;
											temp->wallet -= count * price;
											good_temp = temp->goods;
											while (good_temp) {
												if (!strcmp(good_temp->good_name, good_name)
													&& good_temp->price == GS_temp->price) {
													first_time_good_type = 0;
													break;
												}
												if (alphabet_check(good_name, good_temp->good_name) == 2)
													good_temp = good_temp->left;
												else if ((good_temp)&&(alphabet_check(good_name, good_temp->good_name) != 2))
													good_temp = good_temp->right;
											}
											if (first_time_good_type) {
												good* Good = malloc(sizeof(struct good));
												if (Good == NULL) {
													printf("Error! memory not allocated.");
													exit(0);
												}
												Good->good_name = malloc((good_name_len + 1) * sizeof(char));
												if (Good->good_name == NULL) {
													printf("Error! memory not allocated.");
													exit(0);
												}
												strcpy(Good->good_name, good_name);
												seller_name_len = strlen(temp->username);
												Good->seller_name = malloc((seller_name_len + 1) * sizeof(char));
												if (Good->seller_name == NULL) {
													printf("Error! memory not allocated.");
													exit(0);
												}
												strcpy(Good->seller_name, seller_name);
												Good->price = price, Good->count = count;
												Good->rated = 0, Good->rate = 0;
												Good->numofrate = 0;
												if (temp->goods != NULL)
													good_insert(Good, temp->goods);
												else
													temp->goods = good_insert(Good, temp->goods);
											}
											else {
												good_temp->rated = 0;
												good_temp->count += count;
											}
											printf("buying was succssful\n");	    //end of buying proccess
										}
										else
											printf("you don't have enough money\n");
									}
									else
										printf("not enough number of this product is in inventory.\n");
									break;
								}
								if(alphabet_check(good_name, GS_temp->good_name) == 2)
									GS_temp = GS_temp->left;
								else if ((GS_temp)&&alphabet_check(good_name, GS_temp->good_name) != 2)
									GS_temp = GS_temp->right;
							}
						break;
						}
					}
					if (alphabet_check(seller_name, seller_temp->username) == 2)
						seller_temp = seller_temp->left;
					else if ((seller_temp)&&alphabet_check(seller_name, seller_temp->username) != 2)
						seller_temp = seller_temp->right;
				}
			}
			else
				printf("only buyers can buy\n");
		else
			printf("numbers entered invalid??!!\n");
		free(good_name);
		free(seller_name);
	}
	else {				//rating command
		good_name = malloc((good_name_len + 1) * sizeof(char));
		strncpy(good_name, entery + entery_i, good_name_len);
		good_name[good_name_len] = NULL;
		seller_name = malloc((seller_name_len + 1) * sizeof(char));
		strncpy(seller_name, entery + entery_i + 2 + good_name_len + count_len, seller_name_len);
		seller_name[seller_name_len] = NULL;
		rate = atoi(entery + good_name_len + seller_name_len + 11);
		good_temp = temp->goods;
		GS_temp = seller_temp->goods;
		if (temp->role[0] == 'b') {
			while (seller_temp != NULL) {		//search seller
				if (!strncmp(entery + 12 + good_name_len, seller_temp->username, seller_name_len - 2)
					&& (seller_temp->role[0] == 's')) {
					seller_availability = 1;
					GS_temp = seller_temp->goods;
					while (good_temp != NULL) {		//search buyer goods
						if (!strncmp(entery + 11, good_temp->good_name, good_name_len)) {
							has_good = 1;
							while (GS_temp != NULL) {		//search seller goods
								if (!strncmp(good_name, GS_temp->good_name, good_name_len)) {	//rating
									if (!good_temp->rated)
										if (rate >= 0 && rate <= 5) {
											GS_temp->numofrate++;
											GS_temp->rate = (((GS_temp->rate*(GS_temp->numofrate -1)+ rate)) /( GS_temp->numofrate));
											good_availability = 1;
											changed_price_rate = 1;
											//for goods that are bought with different prices
											good_temp->rated = 1;					//to rate once
											printf("rating was successful.\n");
											return;
										}
										else
											printf("you can rate from 0 to 5.\n");
									else {
										changed_price_rate = 0;
									}
									good_availability = 1;
								}
								if (alphabet_check(good_name, GS_temp->good_name) == 2)
									GS_temp = GS_temp->left;
								else if ((GS_temp)&&(alphabet_check(good_name, GS_temp->good_name) != 2))
									GS_temp = GS_temp->right;

							}
						}
						GS_temp = seller_temp->goods;

						if (alphabet_check(good_name, good_temp->good_name) == 2)
							good_temp = good_temp->left;
						else if ((good_temp)&&(alphabet_check(good_name, good_temp->good_name) != 2))
							good_temp = good_temp->right;
					}
				}
				good_temp = temp->goods;

				if (alphabet_check(entery + 12 + good_name_len, seller_temp->username) == 2)
					seller_temp = seller_temp->left;
				else if ((seller_temp)&&(alphabet_check(entery + 12 + good_name_len, seller_temp->username) != 2))
					seller_temp = seller_temp->right;
			}


		}
		else
			printf("only buyers can rate.\n");
	}

	if (entery[0] == 'b' || entery[0] == 'r') {
		if (has_good) {
			if (!good_availability && seller_availability)
				printf("this seller doesn't have this product.\n");
			if (!seller_availability)
				printf("no seller with this name found.\n");
			if(entery[0]=='r'&&!changed_price_rate&&good_availability)
			printf("you've already rated.\n");
		}
		else if (seller_availability&&entery[0] == 'r')
			printf("you dont have this good.you can't rate\n");
		if(entery[0]=='r')
			printf("rating was not successful.\n");
	}
}
