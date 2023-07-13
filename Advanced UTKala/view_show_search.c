#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

void print_searched_tree(good* root, long max_price, long min_price, char* username, char* name);
void print_tree(good* root);
good* make_copy(good* Good);
good* add_to_big_tree(good* sorted_goods,person* temp,int first_good);
good* new_sorted(person* root);
void view(good* good_temp);
void view_show_search(char* entery, person* root) {
	int i = 0, j = 0, numofcond = 0, name_len, seller_name_len;
	long int max_price = -1, min_price = -1;
	person* temp = root;	//a temporary pointer to people
	good* good_temp, * good_free_temp;
	char* condition_temp = NULL, * name = NULL, * seller_username = NULL;	//condition's temporary strings
	temp = log_check(root);   //temp is the logged in person if there is anyone logged in
	if (!temp) {
		if (entery[1] != 'e')
			printf("login first to view items.\n");
		else
			printf("login first to search.\n");
		return;
	}

	if (entery[0] == 'v') {
		//viewing users info
		printf("view was successful\n\n");
		printf("your username is :%s\n", temp->username);
		printf("your role is :%s\n", temp->role);
		printf("your credit is :%d\nHere is your goods list:\n", temp->wallet);
		good_temp = temp->goods;
		view(good_temp);
	}
	else if (entery[1] == 'h') { //showing goods
		printf("showing goods was successful\n\n");
		//creates a temporary BST of all goods
		good* sorted_tree = new_sorted(root);
		print_tree(sorted_tree);
		freeGood(sorted_tree); //frees it
	}
	else {			// search
		numofcond = atoi(entery + 7);
		if (numofcond > 4 || numofcond < 1) {	//valid entery
			printf("not valid number of conditions entered. search failed.\n");
			return;
		}
		printf("you are searching.\nnow enter %d conditions:\n", numofcond);
		for (i = 0; i < numofcond; i++) {	//getting N conditions as entered
			condition_temp = Entery(condition_temp);	//condition stored in condition temp
			if (!strncmp(condition_temp, "min_price ", 10)) {
				min_price = atoi(condition_temp + 10);
				if (min_price <= 0) {
					printf("min price can't be zero!\n search failed.\n");
					return;
				}
			}
			else if (!strncmp(condition_temp, "max_price ", 10)) {
				max_price = atoi(condition_temp + 10);
				if (max_price <= 0 || max_price < min_price) {
					printf("min or max entered wrong.\n search failed.\n");
					return;
				}
			}
			else if (!strncmp(condition_temp, "name ", 5)) { //saving condition to name string
				name_len = strlen(condition_temp + 5) - 1;
				name = malloc((name_len + 1) * sizeof(char));
				strncpy(name, condition_temp + 5, name_len);
				name[name_len] = NULL;
			}
			else if (!strncmp(condition_temp, "seller_username ", 16)) {	//saving condition to seller_username string
				seller_name_len = strlen(condition_temp + 16) - 1;
				seller_username = malloc((seller_name_len + 1) * sizeof(char));
				strncpy(seller_username, condition_temp + 16, seller_name_len);
				seller_username[seller_name_len] = NULL;
			}
			else {
				printf("There's no such condition .\nconditions are min_price, max_price, name & seller_username.\n");
				return;
			}


			free(condition_temp);
		}
		good_temp = new_sorted(root);
		good_free_temp = good_temp;
		if (max_price == -1)//if max price isn't entered 
			max_price = 2147483647;	//I assign it to a large number to minimize coding 
			//largest long double=2^31-1
		if (min_price == -1)//The same for min price
			min_price = 0;
		printf("here is the search result.\n");
		print_searched_tree(good_temp, max_price, min_price, seller_username, name);
		freeGood(good_temp);		//freeing temporary sorting list
		if (name)//freeing sreach condition temp strings
			free(name);
		if (seller_username)
			free(seller_username);
	}
}
void view(good* good_temp) {
	if (!good_temp)
		return;
	view(good_temp->left);
	printf("\nname of good is :%s\n", good_temp->good_name);
	printf("number left :%d\n", good_temp->count);
	printf("good's price :%d\n", good_temp->price);
	if (good_temp->rated != 2)		//for buyers info
		printf("good's seller name :%s\n", good_temp->seller_name);
	view(good_temp->right);
}
good* new_sorted(person* root) {
	person* temp, * pre;
	good* sorted_goods=NULL;
	int fisrt_good = 1;	//used to make good tree
	if (root == NULL)	//empty tree
		return 0;
	temp = root;
	while (temp != NULL) {
		if (temp->left == NULL) {
			if (temp->role[0] == 's') {
				if (fisrt_good)
					sorted_goods = add_to_big_tree(sorted_goods, temp, fisrt_good);
				else add_to_big_tree(sorted_goods, temp, fisrt_good);
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
				if (temp->role[0] == 's') {
					if (fisrt_good)
						sorted_goods = add_to_big_tree(sorted_goods, temp, fisrt_good);
					else add_to_big_tree(sorted_goods, temp, fisrt_good);
				}
				temp = temp->right;
			}
		}
		if(sorted_goods!=NULL)
			fisrt_good = 0;
	}
	return sorted_goods;
}
good* good_insert(good* Good, good* tree) {
	if (tree == NULL) {
		tree = Good;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	if (alphabet_check(Good->good_name, tree->good_name) == 2) {
		tree->left = good_insert(Good, tree->left);
	}
	else if ((Good)&&(alphabet_check(Good->good_name, tree->good_name) != 2)) {
		tree->right = good_insert(Good, tree->right);
	}
	return tree;
}
int alphabet_check(char* temp1, char* temp_next) {
	int k = 0, result = 0;
	while (!(temp1[k] == NULL && temp_next[k] == NULL)) {
		if (temp_next[k] < temp1[k]) {
			result = 1;
			break;
		}
		else if (temp_next[k] > temp1[k]) {
			result = 2;
			break;
		}
		else {
			if (temp1[k] == NULL || temp_next[k] == NULL) {
				break;
			}
			k++;
		}
	}
	return result;
}
good* add_to_big_tree(good* sorted_goods, person* seller, int first_good) {
	good* temp, * pre;
	if (seller->goods == NULL)	//empty tree
		return 0;
	temp = seller->goods;
	while (temp != NULL) {
		if (temp->left == NULL) {
			good* good_copy = make_copy(temp);
			if (first_good)
				sorted_goods = good_insert(good_copy, sorted_goods);
			else
				good_insert(good_copy, sorted_goods);
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
				good* good_copy = make_copy(temp);
				if (first_good)
					sorted_goods = good_insert(good_copy, sorted_goods);
				else
					good_insert(good_copy, sorted_goods);
				temp = temp->right;
			}
		}
	}
	return sorted_goods;
}
good* make_copy(good* Good) {		//copiyng all good's data
	good* good_copy = malloc(sizeof(good));
	good_copy->count = Good->count;
	good_copy->numofrate = Good->numofrate, good_copy->price = Good->price;
	good_copy->rate = Good->rate, good_copy->rated = Good->rated;
	good_copy->good_name = malloc((1 + strlen(Good->good_name)) * sizeof(char));
	strcpy(good_copy->good_name, Good->good_name);
	good_copy->seller_name = malloc((1 + strlen(Good->seller_name)) * sizeof(char));
	strcpy(good_copy->seller_name, Good->seller_name);
	return good_copy;
}
void print_tree(good* root) {
	if (!root)
		return;
	print_tree(root->left);
	if ((root->rate >= 2 && root->numofrate > 4) || root->numofrate <= 4) {
		printf("\ngood's name is :%s\n", root->good_name);
		printf("seller's name is :%s\n", root->seller_name);
		printf("good's count is :%d\n", root->count);
		printf("good's price is :%d\n", root->price);
		if (root->numofrate > 0)
			printf("good's rate is :%0.2f\n", root->rate);
		else
			printf("good's rate is :NaN\n");
	}
	print_tree(root->right);
}
void simple_print(good* Good) {
	if ((Good->rate >= 2 && Good->numofrate > 4) || Good->numofrate <= 4) {
		printf("\ngood's name is :%s\n", Good->good_name);
		printf("seller's name is :%s\n", Good->seller_name);
		printf("good's count is :%d\n", Good->count);
		printf("good's price is :%d\n", Good->price);
		if (Good->numofrate > 0)
			printf("good's rate is :%0.2f\n", Good->rate);
		else
			printf("good's rate is :NaN\n");
	}
}
void print_searched_tree(good* root, long max_price, long min_price, char* username, char* name) {

	if (!root)
		return;
	print_searched_tree(root->left,max_price,min_price,username,name);

	if (root->price >= min_price && root->price <= max_price) {
		if (name) {				//different conditions of search
			if (!strcmp(root->good_name, name))
				if (username) {
					if (!strcmp(root->seller_name, username))
						simple_print(root);

				}
				else
					simple_print(root);
		}
		else
			if (username) {
				if (!strcmp(root->seller_name, username))
					simple_print(root);
			}
			else
				simple_print(root);


	}

	print_searched_tree(root->right, max_price, min_price, username, name);
}