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
	char *role;
	long int wallet;
    int log_status;
	good** goods;                          //for different kinds of goods.
    int numofgoodtype;                     //number of good type for a user
}person;

int main()   {
    char c;
    char*command=(char*)malloc(11*sizeof(char));            //stores different commands.
    if(command ==NULL){
        printf("Error! memory not allocated.");
        exit(0);
    }
    person** Person = (person**)malloc(sizeof(person*));
    if (Person == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    int i = 0,numofpeople=0;
    char*  entery= NULL;                  //stores the whole entery each time.
    printf("Welcome to UTKala.\nexit is available using <exit> command.\n");
    while (1) {
        c = 'k';
        entery = Entery(entery);           //getting entery

        while (c != ' ') {                //extracting the command.
            if (i == 11) {
                command[10] = NULL;
                break;
            }
            c = entery[i];
            command[i] = c;    
            if (c==' ')
                command[i] = NULL;
            if (c == NULL) { 
                command[i-1] = NULL;
                break; 
            }
            i++;
        }
        i = 0,c = 'k';   //resetting the extraction process
        if (!strncmp(command, "signup", 6)&&entery[6]==' ') {                  // signup function
            int j = 0;
            int flag = 0;
                while (c!=NULL) {          // counting the number of spaces and correct spelling of roles
                    c = entery[8 + i];
                    if (c == ' ')
                        j++;
                    i++;
                }
                if (j == 2) {
                    if (!strncmp(entery + i+1,"buyer",5)&&entery[i+6]==10)
                        if (i > 9)
                            flag = 1;
                    if (!strncmp(entery + i, "seller", 6)&&entery[i+6]==10)
                        if (i > 10)
                            flag = 1;

                    if (flag) {
                        int signup_grant = 1;
                       
                        Person[numofpeople] = signup(entery);           //the  signup function
                        for (i = 0; i < numofpeople; i++) {
                            if (Person[i]->log_status == 1) {
                                signup_grant = 0;                   //denies signup without logout
                                printf("cant signup when a person is loged in\n");
                                break;
                            }
                            if (!strcmp(Person[numofpeople]->username, Person[i]->username))
                                if (!strcmp(Person[numofpeople]->role, Person[i]->role)) {
                                    signup_grant = 0;
                                    printf("username for this role is used, try another\n");
                                    break;
                                }
                        }
                        if (signup_grant) {
                            printf("signup was successful\n");
                            numofpeople++;
                            Person = (person**)realloc(Person, (numofpeople+1) * sizeof(person*));
                            if (Person == NULL) {
                                printf("Error! memory not allocated.");
                                exit(0);
                            }
                        }
                    }
                    else
                        printf("unsuccessful signup.\n");
                }
                else
                    printf("username or password enterd in a wrong way\nsignup <username> <password> <role> is the proper way\n");

        }
        else if (!strncmp(command, "login", 5)&&entery[5]==' ') {
            int j = 0;
            int flag = 0;
            while (c != NULL) {          // counting the number of spaces and correct spelling of roles
                c = entery[7 + i];
                if (c == ' ')
                    j++;
                i++;
            }
            if (j == 2) {
                log(entery, Person,numofpeople);
            }else{
                printf("username or password enterd in wrong way\nlogin <username> <password> <role> is the proper way\n");}

        }
        else if (!strncmp(command, "logout", 6)&&entery[6]==10) {
            log(entery, Person, numofpeople);
        }
        else if (!strncmp(command, "view", 4)&&entery[4]==10) {
            if (numofpeople > 0)                            //denies viewing or showing command without login
                view_show(entery, Person, numofpeople);
            else
                printf("signup and then login to view items.\n");
        }
        else if (!strncmp(command, "show_goods", 10) && entery[10] == 10) {
            if (numofpeople > 0) {
                if (entery[10] == '\n')                 // correct entery check
                    view_show(entery, Person, numofpeople);
                else
                    printf("signup and then login to see all goods.\n");
            }
        }
        else if (!strncmp(command, "deposit", 7)) {
            if (entery[7] == ' ')
                if (numofpeople > 0)
                    deposit_buy(entery, Person, numofpeople);
                else
                    printf("signup and then login to deposit.\n");
            else
                printf("deposit command enterd worng\ndeposit <amount_of_money> is the proper way\n");
        }
        else if (!strncmp(command,"buy",3)) {
            int j = 0;
            int flag = 0;
            while (c != NULL) {          // counting the number of spaces 
                c = entery[5  + i];
                if (c == ' ')
                    j++;
                i++;
            }
            if (entery[3] == ' '&&j==2)
                if (numofpeople>0)
                    deposit_buy(entery, Person, numofpeople);
                else
                    printf("signup and the login to buy items.\n");
        else
            printf("buy command enterd worng\nbuy <goods_name> <goods_count> <seller_username> is the proper way\n");

        }
        else if (!strncmp(command, "add_goods", 9)) {
        int j = 0;
        int flag = 0;
        while (c != NULL) {          // counting the number of spaces 
            c = entery[11 + i];
            if (c == ' ')
                j++;
            i++;
        }
        if (entery[9] == ' ' && j == 2)
            if (numofpeople>0)
                add_goods(entery, Person, numofpeople);
            else
                printf("signup and then login to add items.\n");
        else
            printf("add_goods command enterd worng\nadd_goods <goods_name> <goods_price> <goods_count> is the proper way\n");
}
        else if (!strncmp(command, "exit", 4)) {
            exit(EXIT_SUCCESS);
        }
        else {                      // end of all commands
            printf("invalid command try again\n");
            
        }


    
        free(entery);
        i = 0;
    }
    free(command);          //freeing every freeable
    for (i = 0; i < numofpeople; i++) {
        free(Person[i]->username);
        free(Person[i]->password);
        free(Person[i]->role);
        for (int j = 0; j < Person[i]->numofgoodtype; j++) {
            free(Person[i]->goods[j]->good_name);
            free(Person[i]->goods[j]->seller_name);
        }
        free(Person[i]->goods);
    }
    free(Person);
    return 0;
}