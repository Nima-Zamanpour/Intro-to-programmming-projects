#include <stdio.h>
#include <stdlib.h>
#include <string.h>                       
#include "Header.h"

person* person_insert(person* Person, person* tree);
good* Good_insert(good* Good, good* tree);
person* createPerson(person* user, char* user_line);
good* GoodFile_reader(person* user);
good* createGood(good* user, char* good_line);
void traverse_tree(person* root, FILE* file, char* number_temp,FILE* good_file);
void traverse_good(person* Person,good* good_root, FILE* good_file, char* number_temp);
void File_writer(person* root) {
	if (root == NULL)
		return;
	char* number_temp = malloc(11 * sizeof(char));
	//since program uses int & long int,the biggest number is ~10 billion
	good* good_temp;
	FILE* file = fopen("users.txt", "w");
	FILE* good_file = fopen("goods.txt", "w");
	traverse_tree(root, file, number_temp, good_file);



	free(number_temp);
	fclose(good_file);
	fclose(file);
}
person* File_reader() {
	person* root = NULL;
	FILE* file = fopen("users.txt", "r");
	if (file == NULL)
		return root;
	int first_person = 1, file_len = 0; //users file
	char c;
	while (1) {
		c = fgetc(file);
		if (feof(file))
			break;
		file_len++;
	}
	char* all_users_free, * all_users = malloc((file_len + 1) * sizeof(char));
	fseek(file, 0, SEEK_SET);
	fread(all_users, sizeof(char), file_len, file);
	all_users[file_len] = 0;
	all_users_free = all_users;
	fclose(file);
	if (all_users[0] == NULL)
		return root;

	while (all_users[0]) {
		person* user = malloc(sizeof(person));
		user = createPerson(user, all_users);
		all_users = strpbrk(all_users, "\n") + 1;
		if (first_person)
			root = person_insert(user, root);
		else
		person_insert(user, root);
		first_person = 0;
	}

	free(all_users_free);

	return root;
}
person* createPerson(person* user, char* user_line) {
	int i = 0, wallet, username_len = 0, passwoed_len = 0;
	while (user_line[i] != ',') {
		username_len++;
		i++;
	}
	i = 1;
	while (user_line[i + username_len]!=',') {
		passwoed_len++;
		i++;
	}						//adding info to user's account
	user->username = malloc((username_len + 1) * sizeof(char));//username
	strncpy(user->username, user_line, username_len);
	user->username[username_len] = NULL;

	user->password = malloc((passwoed_len + 1) * sizeof(char));//password
	strncpy(user->password, user_line + 1 + username_len, passwoed_len);
	user->password[passwoed_len] = NULL;
	if (user_line[passwoed_len + username_len + 2] == 'b') {//role & wallet
		user->role = malloc(6 * sizeof(char));
		strcpy(user->role, "buyer");
		user->wallet = atoi(user_line + passwoed_len + username_len + 8);
	}
	else {
		user->role = malloc(7 * sizeof(char));
		strcpy(user->role, "seller");
		user->wallet = atoi(user_line + passwoed_len + username_len + 9);
	}
	user->log_status = 0;
	//now the good function
	user->goods = GoodFile_reader(user);
	return user;
}
good* GoodFile_reader(person* user) {
	user->goods = NULL;
	FILE* good_file = fopen("goods.txt", "r");
	if (good_file == NULL)
		return user->goods;
	int good_file_len = 0, first_good = 1, username_len = 0, i = 0;
	char c;
	while (1) {
		c = fgetc(good_file);
		if (feof(good_file))
			break;
		good_file_len++;
	}
	char* all_goods_free, * all_goods = malloc((good_file_len + 1) * sizeof(char));
	fseek(good_file, 0, SEEK_SET);
	fread(all_goods, sizeof(char), good_file_len, good_file);//writing from file to all_goods
	all_goods[good_file_len] = 0;
	all_goods_free = all_goods;  //to free it later
	fclose(good_file);
	if (all_goods[0] == NULL)
		return user->goods;
	while ((alphabet_check(user->username, all_goods)==1)&&
		(strncmp(user->username,all_goods,strlen(user->username)))) {
		all_goods = strpbrk(all_goods, "\n") + 1;
		if (all_goods[0] == NULL)
			return user->goods;
	}
	while (all_goods[i] != ',') {
		username_len++;
		i++;
	}
	//
	while (all_goods[0]) {		//if is to match a user and its goods
		if ((!strncmp(all_goods, user->username, username_len)))
			if(((user->role[0] == 'b') && (all_goods[username_len + 1] != '2')) //buyer
			|| ((user->role[0] == 's') && (all_goods[username_len + 1] == '2'))) {//seller

			good* Good = malloc(sizeof(good));
			Good = createGood(Good, all_goods);
			if (first_good)
				user->goods = good_insert(Good, user->goods);
			else
			good_insert(Good, user->goods);
			first_good = 0;

		}
		all_goods = strpbrk(all_goods, "\n") + 1;
	}

	free(all_goods_free);

	return user->goods;


}
good* createGood(good* Good, char* good_line) {
	int i = 0, good_name_len = 0, username_len = 0, price_len = 0, count_len = 0;
	int seller_name_len = 0;
	while (good_line[i]!=',') {
		username_len++;
		i++;
	}
	i = 3;
	while (good_line[username_len+i]!=',') {
		good_name_len++;
		i++;
	}
	i = 4;
	while (good_line[username_len + good_name_len + i] != ',') {
		price_len++;
		i++;
	}
	i = 5;
	while (good_line[username_len + good_name_len + price_len + i] != ',') {
		count_len++;
		i++;
	}
	i = 13;
	while (good_line[username_len + good_name_len + price_len + count_len + i] != '\n') {
		seller_name_len++;
		i++;
	}//putting info to good node

	Good->seller_name = malloc((seller_name_len + 1) * sizeof(char));
	strncpy(Good->seller_name, good_line+ username_len + good_name_len + price_len + count_len + 13, seller_name_len);
	Good->seller_name[seller_name_len] = NULL;		//seller name
	Good->good_name = malloc((good_name_len + 1) * sizeof(char));
	strncpy(Good->good_name, good_line + username_len + 3, good_name_len);
	Good->good_name[good_name_len] = NULL;				// good name
	Good->price = atoi(good_line + username_len + good_name_len + 4);
	Good->count = atoi(good_line + username_len + good_name_len + price_len + 5);
	Good->rate = atof(good_line + username_len + good_name_len + price_len + count_len + 6);
	Good->numofrate = atoi(good_line + username_len + good_name_len + price_len + count_len + 11);
	Good->rated = atoi(good_line + username_len + 1);

	return Good;


}
person* person_insert(person* Person, person* tree) {
	if (tree == NULL) {

		tree = Person;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	if (alphabet_check(Person->username, tree->username) == 2) {
		tree->left = person_insert(Person, tree->left);
	}
	else if (alphabet_check(Person->username, tree->username) != 2) {
		tree->right = person_insert(Person, tree->right);
	}
	return tree;
}
good* Good_insert(good* Good, good* tree) {
	if (tree == NULL) {

		tree = (good*)malloc(sizeof(good));
		tree = Good;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	if (alphabet_check(Good->good_name, tree->good_name) == 2) {
		tree->left = insert(Good, tree->left);
	}
	else if ((Good)&&(alphabet_check(Good->good_name, tree->good_name) != 2)) {
		tree->right = insert(Good, tree->right);
	}
	return tree;
}
void traverse_tree(person* root, FILE* file, char* number_temp, FILE* good_file) {
	if (!root)
		return;
	traverse_tree(root->left, file, number_temp,good_file);

	fwrite(root->username, sizeof(char), strlen(root->username), file);
	fputc(',', file);
	fwrite(root->password, sizeof(char), strlen(root->password), file);
	fputc(',', file);
	fwrite(root->role, sizeof(char), strlen(root->role), file);
	fputc(',', file);
	sprintf(number_temp, "%d", root->wallet);
	fwrite(number_temp, sizeof(char), strlen(number_temp), file);
	fputc('\n', file);		//one person every line
	traverse_good(root,root->goods, good_file, number_temp);	// writing goods
	traverse_tree(root->right, file, number_temp,good_file);
}
void traverse_good(person* Person,good* good_root,FILE* good_file, char* number_temp) {
	if (!good_root)
		return;
	traverse_good(Person,good_root->left,good_file,number_temp);

	fwrite(Person->username, sizeof(char), strlen(Person->username), good_file);
	fputc(',', good_file);
	sprintf(number_temp, "%d", good_root->rated);
	fwrite(number_temp, sizeof(char), strlen(number_temp), good_file);
	fputc(',', good_file);
	fwrite(good_root->good_name, sizeof(char), strlen(good_root->good_name), good_file);
	fputc(',', good_file);
	sprintf(number_temp, "%d", good_root->price);
	fwrite(number_temp, sizeof(char), strlen(number_temp), good_file);
	fputc(',', good_file);
	sprintf(number_temp, "%d", good_root->count);
	fwrite(number_temp, sizeof(char), strlen(number_temp), good_file);
	fputc(',', good_file);
	sprintf(number_temp, "%0.2f", good_root->rate);
	fwrite(number_temp, sizeof(char), strlen(number_temp), good_file);
	fputc(',', good_file);
	sprintf(number_temp, "%d", good_root->numofrate);
	fwrite(number_temp, sizeof(char), strlen(number_temp), good_file);
	fputc(',', good_file);
	fwrite(good_root->seller_name, sizeof(char), strlen(good_root->seller_name), good_file);
	fputc('\n', good_file);		//one good every line
	traverse_good(Person,good_root->right, good_file, number_temp);
}