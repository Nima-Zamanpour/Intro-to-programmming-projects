#include "rotate.h"
#include <stdio.h>
int rotate(char board[6][6], char flag[5]) {
	int zone;
	char direction;
	if (flag[1] == 'b') {
		printf("Black's turn to rotate\n");
	}
	else  if (flag[1]=='w')     {
		printf("White's turn to rotate\n");
	}
	printf("Please choose a zone & a direction:\n");
	scanf_s("%d %c", &zone, &direction);
	if (((zone == 1) || (zone == 2) || (zone == 3) || (zone == 4)) && ((direction == '+') || (direction == '-'))) { // حذف ورودی های نا معتبر
		if (zone == 1) {
			int temp1 = board[0][3];
			int temp2 = board[0][4];
			if (direction == '+') {                      // اعمال چرخش ها
				board[0][3] = board[2][3], board[2][3] = board[2][5];
				board[2][5] = board[0][5], board[0][5] = temp1;
				board[0][4] = board[1][3], board[1][3] = board[2][4];
				board[2][4] = board[1][5], board[1][5] = temp2;
			}
			else {
				board[0][3] = board[0][5], board[0][5] = board[2][5];
				board[2][5] = board[2][3], board[2][3] = temp1;
				board[0][4] = board[1][5], board[1][5] = board[2][4];
				board[2][4] = board[1][3], board[1][3] = temp2;
			}
		}
		else if (zone == 2) {								
			int temp1 = board[3][3];
			int temp2 = board[3][4];
			if (direction == '+') {
				board[3][3] = board[5][3], board[5][3] = board[5][5];
				board[5][5] = board[3][5], board[3][5] = temp1;
				board[3][4] = board[4][3], board[4][3] = board[5][4];
				board[5][4] = board[4][5], board[4][5] = temp2;
			}
			else {
				board[3][3] = board[3][5], board[3][5] = board[5][5];
				board[5][5] = board[5][3], board[5][3] = temp1;
				board[3][4] = board[4][5], board[4][5] = board[5][4];
				board[5][4] = board[4][3], board[4][3] = temp2;

			}
		}
		else if (zone == 3) {							
			int temp1 = board[3][0];
			int temp2 = board[3][1];
			if (direction == '+') {
				board[3][0] = board[5][0], board[5][0] = board[5][2];
				board[5][2] = board[3][2], board[3][2] = temp1;
				board[3][1] = board[4][0], board[4][0] = board[5][1];
				board[5][1] = board[4][2], board[4][2] = temp2;
			}
			else {
				board[3][0] = board[3][2], board[3][2] = board[5][2];
				board[5][2] = board[5][0], board[5][0] = temp1;
				board[3][1] = board[4][2], board[4][2] = board[5][1];
				board[5][1] = board[4][0], board[4][0] = temp2;

			}
		}
		else if (zone == 4) {			   			   
			int temp1 = board[0][0];
			int temp2 = board[0][1];
			if (direction == '+') {
				board[0][0] = board[2][0], board[2][0] = board[2][2];
				board[2][2] = board[0][2], board[0][2] = temp1;
				board[0][1] = board[1][0], board[1][0] = board[2][1];
				board[2][1] = board[1][2], board[1][2] = temp2;
			}
			else {
				board[0][0] = board[0][2], board[0][2] = board[2][2];
				board[2][2] = board[2][0], board[2][0] = temp1;
				board[0][1] = board[1][2], board[1][2] = board[2][1];
				board[2][1] = board[1][0], board[1][0] = temp2;


			}
		}
	}
		else {
		while ((zone = getchar()) != '\n' && zone != EOF) {}
			printf("invalid zone or direction .valid values are 1,2,3,4 and +,-	.	retry\n"); // گرفتن ورودی دوباره
			rotate(board, flag);
		}
		flag[0] = 'c'; // تغییر پرچم برای انتخب جای مهره و همچنین تعویض نوبت
	if (flag[1] == 'b') {
		flag[2] = 'w';
	}
	else if (flag[1]=='w')  {
		flag[2] = 'b';
	}
	
		return(board, flag);
		}
		