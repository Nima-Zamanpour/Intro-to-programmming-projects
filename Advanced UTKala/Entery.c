#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#define _CRT_SECURE_NO_WARNINGS
char* Entery(char* entery) {       
    int size = 1, i = 0;
    char* temp = NULL;              //a temporary pointer
    entery = malloc(size + 1);//allocate space for two char one for the '\0' to terminate the string
    while (1) {
        size++;
        temp = realloc(entery, size + 1);//reallocate space.
        if (temp == NULL) {
            printf("error allocating memory");
            free(entery);
            return 1;
        }
        entery = temp;
        if ((scanf("%c", &entery[i])) == 1) {
            i++;
            entery[i] = '\0'; // terminate the string
            if (entery[i - 1] == '\n') {
                break;
            }
        }
        else {
            break;
        }
    }
    return entery;
}