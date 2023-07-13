#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

person* log_check(person* root);
void log(char* entery, struct person* root) {
	int i = 0, username_len = 1, password_len = 0, no_match = 1;
	char c;
	int login_success = 0, logout_success = 0;
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
	person* temp = root;
	i = 0;
	char* username = (char*)malloc((username_len + 1) * sizeof(char));
	char* password = (char*)malloc((password_len + 1) * sizeof(char));
	strncpy(username, entery + 6, username_len);
	username[username_len] = NULL;
	strncpy(password, entery + 7 + username_len, password_len);
	password[password_len] = NULL;
	temp = log_check(root);   //temp is the logged in person is anyone is logged in
	if (temp && entery[3] == 'i') {
		printf("a person is already logged in.\n");
		printf("login was not successful\n");
		return;
	}
	if (entery[3] == 'i') {
		temp = root;
		while (temp != NULL) {
			if (!strcmp(username, temp->username)) {
				if (!strcmp(password, temp->password))
					if (temp->role[0]==entery[ + 8 + username_len + password_len]) {
						temp->log_status = 1;
						login_success = 1;
						no_match = 0;
						break;
					}
				no_match = 0;
			}
			if (alphabet_check(username,temp->username) == 2)
				temp = temp->left;
			else if ((temp)&&(alphabet_check(username ,temp->username) != 2))
				temp = temp->right;
		}
		if (login_success)
			printf("login was successful\n");
		else
			printf("login was not successful\n");
		if (no_match)
			printf("no user with this username found.\n");
	}
	else {
			if (temp) {
				temp->log_status = 0;
				logout_success = 1;
			}
		if (logout_success)
			printf("logout was successful\n");
		else
			printf("logout was not successful.nobody is logged in.\n");
	}
	free(username);
	free(password);
}//returns the logged in person
person* log_check(person* root) {		//روش موریس برای طی درخت 
	person* chosen=NULL;
	person* temp, * pre;
	if (root == NULL)	//empty tree
		return 0;
	temp = root;
	while (temp != NULL) {
		if (temp->left == NULL) {
			if (temp->log_status)
				chosen= temp;
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
				if (temp->log_status)
					chosen=temp;
				temp = temp->right;
			}
		}
	}
	return chosen;
}