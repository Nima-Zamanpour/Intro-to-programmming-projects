#include "Board.h"
#include  <stdio.h>
int Board(char board[6][6], char flag[5]) {
	system("cls");// پاک کردن صفحه
	printf(" \t1 \t2\t3    |   4    \t5\t6\n");
	printf("1\t%c\t%c\t%c    |   %c\t%c\t%c\n\n", board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5]);
	printf("2\t%c\t%c\t%c    |   %c\t%c\t%c\n\n", board[1][0], board[1][1], board[1][2], board[1][3], board[1][4], board[1][5]);
	printf("3\t%c\t%c\t%c    |   %c\t%c\t%c\n\n", board[2][0], board[2][1], board[2][2], board[2][3], board[2][4], board[2][5]);
	printf("--\t--\t--\t--       -- \t--\t--\n\n");
	printf("4\t%c\t%c\t%c    |   %c\t%c\t%c\n\n", board[3][0], board[3][1], board[3][2], board[3][3], board[3][4], board[3][5]);
	printf("5\t%c\t%c\t%c    |   %c\t%c\t%c\n\n", board[4][0], board[4][1], board[4][2], board[4][3], board[4][4], board[4][5]);
	printf("6\t%c\t%c\t%c    |   %c\t%c\t%c\n", board[5][0], board[5][1], board[5][2], board[5][3], board[5][4], board[5][5]);
}