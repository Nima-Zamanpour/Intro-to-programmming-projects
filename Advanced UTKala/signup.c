#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

person* insert(person* Person, person* tree);
person* signup(char* entery, person* root) {
	int i = 0, username_len = 1, password_len = 0;
	int signup_grant = 1, system_occupance = 0;
	char c;
	person* temp = root;
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

	// username uniqueness check
	while (temp != NULL) {
		if (!strncmp(entery + 7, temp->username, username_len))
			if (entery[9 + password_len + username_len] == temp->role[0]) {
				signup_grant = 0;
				printf("username for this role is used, try another\nsignup wasn't successful\n");
				return root;
			}

		if (alphabet_check(entery + 7, temp->username) == 2)
			temp = temp->left;
		if ((temp) && (alphabet_check(entery + 7, temp->username) != 2))
			temp = temp->right;

	}
	system_occupance = log_check(root);
	log_check(root);		 // stack overflow جلوگیری از فرایند

	if (system_occupance != NULL) {
		printf("can't signup when a user in logged in\n");
		return root;
	}

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
	Person->role = malloc(6 * sizeof(char));
	if (entery[9 + password_len + username_len] == 's') {
		Person->role = realloc(Person->role, 7 * sizeof(char));
		strncpy(Person->role, entery + 9 + password_len + username_len, 6);
		Person->role[6] = NULL;
	}
	else {
		strncpy(Person->role, entery + 9 + password_len + username_len, 5);
		Person->role[5] = NULL;
	}
	Person->wallet = 0;			//setting account
	Person->goods = NULL;
	if (root != NULL)
		insert(Person, root);  //adding person to the tree
	else
		root = insert(Person, root);
	printf("signup was successful.\n");
	return root;
}
person* insert(person*Person, person* tree) {
	if (tree == NULL) {
		tree = Person;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	if (alphabet_check(Person->username,tree->username)==2) {
		tree->left = insert(Person, tree->left);
	}
	else if ((Person)&&(alphabet_check(Person->username, tree->username) != 2)) {
		tree->right = insert(Person, tree->right);
	}
	return tree;
}