#include "choice.h"
#include <stdio.h>
int choice(char board[6][6], char flag[5]) {
	if ( flag[2] == 'b') {
		printf("black player's turn\nenter house numbers form 11 to 66: ");
	}
	else if (flag[2] == 'w') {
		printf("white player's turn\nenter house numbers form 11 to 66: ");
	}
	int row=0, column=0, coordinate;    // تبدیل عدد به مختصات
	
	scanf_s("%d" ,&coordinate);

	if ((coordinate >= 11)&&(coordinate<=66)) {
		
		column = coordinate % 10;
		row = (coordinate - column) / 10;
		if (((column > 6) || (column < 1)) || ((row > 6) || (row < 1))) {
			printf("invalid coondinates, retry\n");
			choice(board, flag);
		}
		if (board[(row - 1)][(column - 1)] == '.') {  
			if (flag[2] == 'b') {
				board[row - 1][column - 1] = 'b';
			}
			else {
				board[row - 1][column - 1] = 'w';
			}
		}
		else {
			printf("invalid coondinates, already filled retry \n");		// اینجا کاربر میخواست در محل پر شده مهره بگذاره
			choice(board, flag);
		}
	}
	else {
														// درخواست دوباره از کاربر
		while ((coordinate = getchar()) != '\n' && coordinate != EOF) {}
		printf("invalid coondinates, retry \n");
	
			choice(board, flag);
	}
	flag[0] = 'r';       // تغییر پرچم برای رفتن به تابع چرخش و تعیین نوبت
	if (flag[2] == 'b')
		flag[1] = 'b';
	else if (flag[2]=='w')
	{ flag[1] = 'w'; }
	return (board, flag);
}