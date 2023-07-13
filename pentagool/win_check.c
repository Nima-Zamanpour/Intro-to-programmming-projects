#include "win_check.h"
#include <stdio.h>
int win_check(char board[6][6], char flag[5]) {
	int i;
	int j;
	int tie_check = 0;
	for (i = 0; i < 6; i++) { // چک پر شدن همه خانه ها
		for (j = 0; j < 6; j++) {
			if ((board[i][j] == 'b') || (board[i][j] == 'w'))
				tie_check++;
		}
	}
	if (tie_check == 36) {
		flag[0] = 'e';
		flag[4] = 'y';
		flag[3] = 'y';
	}
	for (j = 0; j < 6; j++) {   //چک حالات پرشمار بردن
		if (board[j][2] == board[j][3] && !(board[j][2] == '.')) {     // for horizontal check
			if ((board[j][1] == board[j][4]) && (board[j][1] == board[j][3])) {
				if (board[j - 1][1] == board[j][4] || board[j + 1][1] == board[j][4] ||
					board[j - 1][4] == board[j][4] || board[j + 1][4] == board[j][4]) {
					if (board[j][3] == 'b') {
						flag[0] = 'e';  // تغییر پرچم اصلی برای خروج از حلقه
						flag[3] = 'y';      // پرچم پیروزی سیاه
					}
					else {
						flag[0] = 'e';
						flag[4] = 'y';
					}
				}
			}
			if (board[j][1] == board[j][0] && board[j][3] == board[j][0]) {
				if (board[j - 1][0] == board[j][1] || board[j + 1][0] == board[j][1] ||
					board[j - 1][3] == board[j][1] || board[j + 1][3] == board[j][1]) {
					if (board[j][3] == 'b') {
						flag[0] = 'e';
						flag[3] = 'y';
					}
					else {
						flag[0] = 'e';
						flag[4] = 'y';
					}
				}
			}
			if(board[j][4] == board[j][5] && board[j][3] == board[j][4]) {
				if (board[j - 1][2] == board[j][4] || board[j + 1][2] == board[j][4] ||
					board[j - 1][5] == board[j][4] || board[j + 1][5] == board[j][4]) {
					if (board[j][3] == 'b') {
						flag[0] = 'e';
						flag[3] = 'y';
					}
					else {
						flag[0] = 'e';
						flag[4] = 'y';
					}
				}
			}										// end of horizontal check
		}


		if ((board[2][j] == board[3][j]) && (!(board[2][j] == '.'))) {			//for vertical check
			if ((board[1][j] == board[4][j]) && (board[1][j] == board[3][j])) {
				if (board[1][j-1] == board[4][j]  || board[1][j+1] == board[4][j] ||
					board[4][j-1] == board[4][j]|| board[4][j+1] == board[4][j]) {
					if (board[3][j] == 'b') {
						flag[0] = 'e';
						flag[3] = 'y';
					}
					else {
						flag[0] = 'e';
						flag[4] = 'y';
					}
				}
			}
			if  (board[1][j] == board[0][j] &&  board[3][j] == board[0][j]) {
				if (board[0][j-1] == board[1][j] || board[0][j+1] == board[1][j] ||
					board[3][j - 1] == board[1][j] || board[3][j+1] == board[1][j]) {
					if (board[3][j] == 'b') {
						flag[0] = 'e';
						flag[3] = 'y';
					}
					else {
						flag[0] = 'e';
						flag[4] = 'y';
					}
				}
			}
			if (board[4][j] == board[5][j] && board[3][j] == board[4][j]) {
				if (board[5][j-1] == board[j][4] || board[2][j+1] == board[4][j] ||
					board[2][j-1] == board[j][4] || board[5][j+1] == board[4][j]) {
					if (board[3][j] == 'b') {
						flag[0] = 'e';
						flag[3] = 'y';
					}
					else {
						flag[0] = 'e';
						flag[4] = 'y';
					}
				}
			}
		}																// end of vertical check
	}

	if ((board[2][3] == board[3][2]) && !(board[2][3] == '.')) {					//  قطر فرعی
		if ((board[4][1] == board[5][0]) && (board[3][2] == board[5][0])) {
			if (board[1][2] == board[2][3] || board[3][4] == board[2][3]) {
				if (board[3][2] == 'b') {
					flag[0] = 'e';
					flag[3] = 'y';
				}
				else {
					flag[0] = 'e';
					flag[4] = 'y';
				}
			}
		}
		if ((board[4][1] == board[3][2] )&& (board[3][2] == board[1][4])) {
			if (board[3][0] == board[2][3] || board[5][2] == board[2][3] || 
				board[0][3] == board[2][3] || board[2][5] == board[2][3] ) {
				if (board[3][2] == 'b') {
					flag[0] = 'e';
					flag[3] = 'y';
				}
				else {
					flag[0] = 'e';
					flag[4] = 'y';
				}
			}
		}
		if ((board[1][4] == board[3][2]) && ( board[0][5] == board[1][4])) {
			if (board[2][1] == board[2][3] || board[4][3] == board[2][3] ) {
				if (board[3][2] == 'b') {
					flag[0] = 'e';
					flag[3] = 'y';
				}
				else {
					flag[0] = 'e';
					flag[4] = 'y';
				}
			}
		}// اخر قطر فرعی

	}															
 	if (board[2][2] == board[3][3] && (!(board[3][3] == '.'))) {				// قطراصلی
		if (board[4][4] == board[5][5] && board[3][3] == board[5][5]) {
			if (board[3][1] == board[3][3] || board[1][3] == board[3][3]) {
				if (board[3][3] == 'b') {
					flag[0] = 'e';
					flag[3] = 'y';
				}
				else {
					flag[0] = 'e';
					flag[4] = 'y';
				}
			}
		}
		if ((board[1][1] == board[3][3] )&&(board[2][2] == board[4][4])){
			if (board[0][2] == board[3][3] || board[5][3] == board[3][3] ||
				board[2][0] == board[3][3] || board[3][5] == board[3][3]) {
				if (board[3][3] == 'b') {
					flag[0] = 'e';
					flag[3] = 'y';
				}
				else {
					flag[0] = 'e';
					flag[4] = 'y';
				}
			}
		}
		if (board[0][0] == board[3][3] && board[1][1] == board[2][2]) {
			if (board[4][2] == board[3][3] || board[2][4] == board[2][2]) {
				if (board[3][3] == 'b') {
					flag[0] = 'e';
					flag[3] = 'y';
				}
				else {
					flag[0] = 'e';
					flag[4] = 'y';
				}
			}
		}													//اخر قطر اصلی
	}
	if (((board[3][1] == board[2][2]) &&( board[1][3] == board[2][2]) )&& !(board[3][1] == '.')) {  // بالای قطر فرعی
		if ((board[2][2] == board[4][0] && board[5][1] == board[2][2]) || 
			(board[0][4]==board[2][2]&&board[1][5]==board[2][2]) ||
			(board[0][4] == board[2][2] && board[0][2] == board[2][2]) ||
			(board[0][4] == board[2][2] && board[2][0] == board[2][2]) ||
			(board[0][4] == board[2][2] && board[4][2] == board[2][2]) ||
			(board[4][0] == board[2][2] && board[2][4] == board[2][2])) {
			if (board[2][2] == 'b') {
				flag[0] = 'e';
				flag[3] = 'y';
			}
			else {
				flag[0] = 'e';
				flag[4] = 'y';
			}
		}
		}
	if (board[3][0] == board[2][1] && board[2][1] == board[1][2] && board[2][1] == board[0][3] && !(board[0][3] == '.')) {
		if (board[4][1] == board[1][2] || board[1][4] == board[1][2]) {
			if (board[2][1] == 'b') {
				flag[0] = 'e';
				flag[3] = 'y';
			}
			else {
				flag[0] = 'e';
				flag[4] = 'y';
			}
		}
	}
	if (board[4][2] == board[3][3] && board[2][4] == board[3][3] && !(board[3][3] == '.')) {		// پایین قطر فرعی
		if ((board[5][1] == board[4][2] && board[5][1] == board[4][0]) ||
			(board[5][1] == board[3][3] && board[1][3] == board[3][3]) ||
			(board[5][1] == board[3][3] && board[3][5] == board[3][3]) ||
			(board[1][5] == board[3][3] && board[0][4] == board[3][3]) ||
			(board[1][5] == board[3][3] && board[3][1] == board[3][3]) ||
			(board[1][5] == board[3][3] && board[5][3] == board[3][3])) {
			if (board[3][3] == 'b') {
				flag[0] = 'e';
				flag[3] = 'y';
			}
			else {
				flag[0] = 'e';
				flag[4] = 'y';
			}
		}
	}
	if (board[5][2] == board[4][3] && board[3][4] == board[2][5] && board[2][5] == board[5][2]&& !(board[5][2]=='.')) {
		if (board[4][0] == board[5][1] || board[5][1] == board[1][4]) {
			if (board[4][3] == 'b') {
				flag[0] = 'e';
				flag[3] = 'y';
			}
			else {
				flag[0] = 'e';
				flag[4] = 'y';
			}
		}
	}												//اتمام کلیه فرعی ها 

	if (board[1][2] == board[2][3] && board[3][4] == board[1][2] && !(board[1][2] == '.')) {  // بالای قطر اصلی
		if ((board[0][1] == board[1][2] && board[1][0] == board[1][2]) ||
			(board[0][1] == board[1][2] && board[2][5] == board[1][2]) ||
			(board[0][1] == board[1][2] && board[4][3] == board[1][2]) ||
			(board[4][5] == board[1][2] && board[5][4] == board[1][2]) ||
			(board[4][5] == board[1][2] && board[0][3] == board[1][2]) ||
			(board[4][5] == board[1][2] && board[2][1] == board[1][2])) {
			if (board[2][3] == 'b') {
				flag[0] = 'e';
				flag[3] = 'y';
			}
			else {
				flag[0] = 'e';
				flag[4] = 'y';
			}
		}
	}	      
	if (board[0][2] == board[1][3] && board[2][4] == board[3][5] && board[0][2] == board[3][5] && !(board[1][3] == '.')) 
	{
		if (board[3][5] == board[4][4] || board[3][5] == board[1][1]) {
			if (board[1][3] == 'b') {
				flag[0] = 'e';
				flag[3] = 'y';
			}
			else {
				flag[0] = 'e';
				flag[4] = 'y';
			}
		}
	}
	if (board[2][1] == board[4][3] && board[2][1] == board[3][2] && !(board[3][2] == '.')) {  
		if ((board[1][0] == board[3][2] && board[0][1] == board[4][3]) ||
			(board[1][0] == board[3][2] && board[3][4] == board[3][2]) ||
			(board[1][0] == board[3][2] && board[5][2] == board[3][2]) ||
			(board[5][4] == board[3][2] && board[4][5] == board[3][2]) ||
			(board[5][4] == board[3][2] && board[3][0] == board[3][2]) ||
			(board[5][4] == board[3][2] && board[1][2] == board[3][2])) {
			if (board[2][1] == 'b') {
				flag[0] = 'e';
				flag[3] = 'y';
			}
			else {
				flag[0] = 'e';
				flag[4] = 'y';
			}
		}
	}
	if (board[2][0] == board[3][1] && board[4][2] == board[5][3] && board[5][3] == board[2][0] &&
		!(board[2][0] == '.')) {
		if (board[1][1] == board[2][0] || board[4][4] == board[2][0]) {
			if (board[4][2] == 'b') {
				flag[0] = 'e';
				flag[3] = 'y';
			}
			else {
				flag[0] = 'e';
				flag[4] = 'y';
			}
		}
	}
	return (board,flag);
}