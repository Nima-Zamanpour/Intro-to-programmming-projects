#include <stdio.h>
#include "Board.h"
#include "choice.h"
#include "rotate.h"
#include "win_check.h"
int Board(char board[6][6], char flag[5]);
int choice(char board[6][6], char flag[5]);
int rotate(char board[6][6], char flag[5]);
int win_check(char board[6][6], char flag[5]);


int main() {
	int i,j;
	char flag[5] = { 'c','b','b','n','n'};
	// خانه اول ارایه برای تداوم حلقه کلی
	// خانه دوم برای تغییر بازیکن ها برای چرخش و
	//خانه سوم تغییر بازیکن ها برای انتخاب مکان 
	// خانه های 4و 5 برای اعلام پیروزی سیاه و سفید به تابع اصلی
	char board[6][6];
	for (i = 0; i <6; i++) {// شروع بازی و خالی کردن صفحه
		for (j = 0; j < 6; j++) {
			board[i][j] = '.';
		}
	}
	Board(board, flag);
	while (flag[0] == 'c' || flag[0] == 'r') {			//حلقه کلی تکرار بازی
		if (flag[0] == 'r') {
			rotate(board, flag);
			Board(board, flag);
			win_check(board,flag);		// چک شرط پیروزی هر بار
		}
		
		else if (flag[0] == 'c') {
			choice(board, flag);
			Board(board, flag);
		}
	}
	if ((flag[3]=='y'&& flag[4]=='y')) {       // چک مساوی یا پر شدن صفحه
		printf("we have a tie, nice game");
	}
	else if (flag[3] == 'y') {				
		printf("black won ,well done");
	}
	else if (flag[4] == 'y') {
		printf("white won ,well done");
	}
	
 }	