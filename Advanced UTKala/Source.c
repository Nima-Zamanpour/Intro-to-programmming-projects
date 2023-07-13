#include <stdio.h>
#include <stdlib.h>
#include <string.h>                       
#include "Header.h"
void freeperson(person* Person);
int main() {
    int i = 0, j = 0, numofpeople = 0;
    char c;
    char* command = (char*)malloc(19 * sizeof(char));            //stores different commands.
    if (command == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    person* root=NULL;
    root = File_reader();
    char* entery = NULL;                  //stores the whole entery each time.
    printf("Welcome to UTKala.\nexit is available using <exit> command.\n");
    while (1) {
            c = 'k';
        entery = Entery(entery);           //getting entery
        File_writer(root);    //writing to file every time
        while (c != ' ') {                //extracting the command.
            if (i == 19) {
                command[18] = NULL;
                break;
            }
            c = entery[i];
            command[i] = c;
            if (c == ' ')
                command[i] = NULL;
            if (c == NULL) {
                command[i - 1] = NULL;
                break;
            }
            i++;
        }
        i = 0, c = 'k';   //resetting the extraction process
        if (!strncmp(command, "signup", 6) && entery[6] == ' ') {                  // signup function
            j = 0;
            int flag = 0;
            while (c != NULL) {          // counting the number of spaces and correct spelling of roles
                c = entery[8 + i];
                if (c == ' ')
                    j++;
                i++;
            }
            if (j == 2) {
                if (!strncmp(entery + i + 1, "buyer", 5) && entery[i + 6] == 10)
                    if (i > 9)
                        flag = 1;
                if (!strncmp(entery + i, "seller", 6) && entery[i + 6] == 10)
                    if (i > 10)
                        flag = 1;
                if (flag) {
                    if(!root)
                        root= signup(entery, root);
                    else
                    signup(entery, root);
                }
                else
                    printf("unsuccessful signup.\n");
            }
            else
                printf("username or password enterd in a wrong way\nsignup <username> <password> <role> is the proper way\n");

        }
        else if (!strncmp(command, "login", 5) && entery[5] == ' ') {
            j = 0;
            while (c != NULL) {          // counting the number of spaces and correct spelling of roles
                c = entery[7 + i];
                if (c == ' ')
                    j++;
                i++;
            }
            if (j == 2) {
                log(entery, root);
            }
            else {
                printf("username or password enterd in wrong way\nlogin <username> <password> <role> is the proper way\n");
            }

        }
        else if (!strncmp(command, "logout", 6) && entery[6] == 10) {
            log(entery, root);
        }
        else if (!strncmp(command, "view", 4) && entery[4] == 10) { //denies viewing or showing command without login
            view_show_search(entery, root);
        }
        else if (!strncmp(command, "show_goods", 10) && entery[10] == 10) {
                view_show_search(entery, root);
        }
        else if (!strncmp(entery, "search ", 7) && entery[8] == 10) {
            view_show_search(entery, root);
        }
        else if (!strncmp(command, "deposit", 7)) {
            if (entery[7] == ' ')
                deposit_buy_rate(entery, root);
            else
                printf("deposit command enterd worng\ndeposit <amount_of_money> is the proper way\n");
        }
        else if (!strncmp(command, "buy", 3)) {
            j = 0;
            while (c != NULL) {          // counting the number of spaces 
                c = entery[5 + i];
                if (c == ' ')
                    j++;
                i++;
            }
            if (entery[3] == ' ' && j == 2)
                deposit_buy_rate(entery, root);
            else
                printf("buy command enterd worng\nbuy <goods_name> <goods_count> <seller_username> is the proper way\n");

        }
        else if (!strncmp(command, "rate_goods", 10)) {
            j = 0;
            while (c != NULL) {          // counting the number of spaces 
                c = entery[12 + i];
                if (c == ' ')
                    j++;
                i++;
            }
            if (entery[10] == ' ' && j == 2)
                deposit_buy_rate(entery, root);
            else
                printf("rate command enterd worng\nrate_goods <goods_name> <seller_username> <rating> is the proper way\n");

        }
        else if (!strncmp(command, "remove_goods", 12)) {
            if (entery[12] == ' ')
                add_remove_change(entery, root);
            else
                printf("remove command enterd worng\nremove_goods <goods_name> is the proper way\n");
        }
        else if (!strncmp(command, "add_goods", 9)) {
            j = 0;
            int flag = 0;
            while (c != NULL) {          // counting the number of spaces 
                c = entery[11 + i];
                if (c == ' ')
                    j++;
                i++;
            }
            if (entery[9] == ' ' && j == 2)
                add_remove_change(entery, root);
            else
                printf("add_goods command enterd worng\nadd_goods <goods_name> <goods_price> <goods_count> is the proper way\n");
        }
        else if (!strncmp(command, "change_goods_price", 18)) {
        j = 0;
        while (c != NULL) {          // counting the number of spaces 
            c = entery[20 + i];
            if (c == ' ')
                j++;
            i++;
        }
        if (entery[18] == ' '&&j==1)
            add_remove_change(entery, root);
        else
            printf("change command enterd worng\nchange_goods_price <goods_name> <new_price> is the proper way\n");
        }
        else if (!strncmp(command, "exit", 4)) {
            free(entery);
            File_writer(root);    //writing to file every time
            break;
        }
        else {                      // end of all commands
            printf("invalid command try again\n");

        }
        File_writer(root);    //writing to file every time

        free(entery);
        i = 0;
    }
    free(command);          //freeing every freeable
    freeperson(root);
    return 0;
}
void freeperson(person* Person) {
    if (Person != NULL) {
        freeperson(Person->left);
        freeperson(Person->right);
        freeGood(Person->goods);
        free(Person->username);
        free(Person->password);
        free(Person->role);
        free(Person);
    }
}
void freeGood(good* Good) {
    if (Good != NULL) {

        freeGood(Good->left);
        freeGood(Good->right);
        free(Good->good_name);
        free(Good->seller_name);
        free(Good);
    }
}
