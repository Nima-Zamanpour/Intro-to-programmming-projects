#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int traverse_goods(person* seller, char* good_name);
int add_good_grant_check(person* root,person* seller ,char* good_name);
good* lowest_upper(good* node);
good* delete_good(good* root, char* good_name);
void add_remove_change(char* entery, person* root) {
	int i = 0, j = 0, k = 0, count = 0;
	int good_name_len = 0, good_count_len = 0, good_price_len = 0, seller_name_len = 0;
	long int price = 0;
	char* good_name;
	int first_time_good_type = 1;	//first time a seller adds a new kind of goods
	int add_goods_grant = 1, good_availability = 0;
	person* temp = root, * checker = root;//a temporary pointer to people


	temp = log_check(root);   //temp is the logged in person is anyone is logged in
	if (!temp) {
		switch (entery[0]) {
		case 97:
			printf("login first to add goods.\n");
			break;
		case 114:
			printf("login first to remove goods.\n");
			break;
		case 99:
			printf("login first to change goods price.\n");
		}
		return;
	}
	good* good_temp, * remove_temp, * good_checker = checker->goods;

	if (entery[0] == 'a') {
		while (entery[i + 10] != ' ') {					//extracting good info
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

		if (temp->role[0] == 's') {				//picking sellers
			good_temp = temp->goods;
			add_goods_grant = add_good_grant_check(root,temp,good_name);//checking whether anyone already added this good
			if (count > 0 && price > 0)
				if (add_goods_grant) {								//adding goods
					while (good_temp) {		//fisrt time a good type is added
						if (!strcmp(good_temp->good_name, good_name)) {
							first_time_good_type = 0;
							break;
						}

						if (alphabet_check(good_temp->good_name, good_name) == 2)
							good_temp = good_temp->left;
						if ((good_temp)&&(alphabet_check(good_temp->good_name, good_name) != 2))
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
						strcpy(Good->seller_name, temp->username);
						Good->price = price, Good->count = count;
						Good->numofrate = 0;
						Good->rate = 0, Good->rated = 2;		//now adding Good to seller's inventory
						if (temp->goods != NULL)
							good_insert(Good, temp->goods);
						else
							temp->goods = good_insert(Good, temp->goods);
					}
					else {
						good_temp->count += count;
					}
					printf("goods were added successfuly\n");
				}
				else {
					printf("this product is already in the inventory of another seller.You can't add this good.\n");
				}
			else {
				printf("price or count are invalid !!??\n");
			}
		}
		else {
			printf("buyers can't add goods.\n");
		}
		free(good_name);
	}
	else if (entery[0] == 'r') {
		while (entery[i + 13] != '\n') {					//extracting removed good info
			good_name_len++;
			i++;
		}
		good_name = malloc((good_name_len + 1) * sizeof(char));
		strcpy(good_name, entery + 13);
		good_name[good_name_len]=NULL;
		if (temp->role[0] == 's') 	// deleting the good
			temp->goods = delete_good(temp->goods, good_name);		
		else {
			printf("buyers can't remove goods\n");
			good_availability = 1;
		}
	}
	else {
		i = 0;		//change good's price
		while (entery[i + 19] != ' ') {					//extracting buying info
			good_name_len++;
			i++;
		}
		good_name = malloc((good_name_len + 1) * sizeof(char));
		strncpy(good_name, entery + 19, good_name_len);
		good_name[good_name_len] = NULL;



		if (temp->role[0] == 's') {
			good_temp = temp->goods;
			while (good_temp) {
				if (!strncmp(entery + 19, good_temp->good_name, good_name_len)) {
					price = atoi(entery + 19 + good_name_len);
					good_temp->price = price;
					good_availability = 1;
					printf("good's price changed\n");
					break;
				}

				if (alphabet_check(good_name, good_temp->good_name) == 2) {
					good_temp=good_temp->left ;
				}
				else if ((good_temp)&&(alphabet_check(good_name, good_temp->good_name) != 2)) {
					good_temp=good_temp->right;
				}
			}
		}
		else
			printf("buyers can't change price.\n");



	}

	if (!good_availability && entery[0] == 'c')
		printf("good wasn't found in your inventory.\n");
}
good* lowest_upper(good* node) {		//finds the father of smallest node
	good* temp = node;
	while (temp && temp->left != NULL)
		temp = temp->left;

	return temp;
}
good* delete_good(good* root, char* good_name) {
	if (root == NULL) {
		printf("good wasn't found in your inventory.\n");
		return root;
	}
	
	if (alphabet_check(good_name,root->good_name)  == 2)
		root->left = delete_good(root->left, good_name);
	else if (alphabet_check(good_name,root->good_name ) == 1)
		root->right = delete_good(root->right, good_name);
	else {
		if (root->left == NULL) {//freeing a node that is the father of a right node
			printf("good removed seccessfuly\n");
			good* temp = root->right;
			free(root->good_name);
			free(root->seller_name);
			free(root);
			return temp;
		}
		else if (root->right == NULL) {//freeing a node that is the father of a left node
			printf("good removed seccessfuly\n");
			good* temp = root->left;
			free(root->good_name);
			free(root->seller_name);
			free(root);
			return temp;
		}
		good* temp = lowest_upper(root->right);
		printf("good removed seccessfuly\n");//freeing a node that is the father of two nodes
		root->count = temp->count;
		root->numofrate = temp->numofrate;
		root->price = temp->price;
		root->rate = temp->rate;
		root->rated = temp->rated;
		int good_name_len = 0, seller_name_len = 0;
		good_name_len = strlen(temp->good_name);
		seller_name_len = strlen(temp->seller_name);
		free(root->good_name);
		root->good_name = malloc((good_name_len + 1) * (sizeof(char)));
		strcpy(root->good_name, temp->good_name);
		free(root->seller_name);
		root->seller_name = malloc((seller_name_len + 1) * (sizeof(char)));
		strcpy(root->seller_name, temp->seller_name);

		root->right = delete_good(root->right, good_name);
	}
	return root;
}
int add_good_grant_check(person* root,person* seller,char* good_name) {	
	int result=1,real_result=1;
	person* temp, * pre;
	if (root == NULL)	//empty tree
		return 1;
	temp = root;
	while (temp != NULL) {
		if (temp->left == NULL) {
			if (temp->role[0] == 's')
				if (temp != seller) {
					result = traverse_goods(temp, good_name);
					if (!result)
						real_result = 0;
				}
			temp = temp->right;
		}
		else {
			pre = temp->left;
			while (pre->right != NULL && pre->right != temp)
				pre = pre->right;

			if (pre->right == NULL) {
				pre->right = temp;
				temp = temp->left;
			}
			else {
				pre->right = NULL;
				if (temp->role[0] == 's')
					if (temp != seller) {
						result = traverse_goods(temp, good_name);
						if (!result)
							real_result = 0;
					}
				temp = temp->right;
			}
		}
	}
	return real_result;
}
int traverse_goods(person* seller, char* good_name) {	//to find goods with same name
	int result = 1;
	good* temp, * pre;
	if (seller->goods == NULL)	//empty tree
		return result;
	temp = seller->goods;
	while (temp != NULL) {
		if (temp->left == NULL) {
			if (!strcmp(temp->good_name, good_name)) 
				result= 0;

			temp = temp->right;
		}
		else {
			pre = temp->left;
			while (pre->right != NULL && pre->right != temp)
				pre = pre->right;

			if (pre->right == NULL) {
				pre->right = temp;
				temp = temp->left;
			}
			else {
				pre->right = NULL;
				if (!strcmp(temp->good_name, good_name)) 
					result = 0;

				temp = temp->right;
			}
		}
	}
	return result;

}