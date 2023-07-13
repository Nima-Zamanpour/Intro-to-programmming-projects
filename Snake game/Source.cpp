#include <iostream>
#include<vector>
#include "windows.h"
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <conio.h>

using namespace std;

class Snake
{
public:
	Snake();

	void putFood();
	void print_board();
	bool game_over();
	void movement();
	void steer();
	void apply_Body();
	void getFood();
private:
	int score;
	int health;
	int length;
	int direction;
	int board[20][20];
	vector<std::pair<int, int>>  Body;
	pair<int, int> FoodPos;
};

Snake::Snake() {

	score = 0;
	health = 3;
	length = 1;
	direction = 1;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			board[i][j] = 0;

	Body.push_back(std::make_pair(10,10));

}

void Snake::print_board() {
	system("cls");
	cout << "You health is :" << health << "\t\t Your score is :" << score;
	cout << "\n------------------------" << endl;
	for (int i = 0; i < 20; i++) {
		cout << "||";
		for (int j = 0; j < 20; j++) {
			if (Snake::board[i][j] == 1)
				cout << "*";
			else if (Snake::board[i][j] == 2)
				cout << "$";
			else
				cout << " ";

		}
		cout << "||\n";
	}
	cout << "------------------------" << endl;

}

bool Snake::game_over() {

	for (int i = 1; i < Snake::Body.size(); i++) {
		if ((Snake::Body[0].first == Snake::Body[i].first) && (Snake::Body[0].second == Snake::Body[i].second)) {
			health--;
			length = 1;
			direction = 1;
			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 20; j++)
					board[i][j] = 0;
			Body.clear();
			Body.push_back(std::make_pair(10, 10));
			break;
		}
	}
	if (health)
		return 1;
	else return 0;
}

void Snake::putFood() {
	srand((unsigned)100 * time(0));
	long double rand1 = rand();
	long double rand2 = pow(rand1, (int)rand1 % 10) + rand1+321466;
	rand1=sqrtl(rand1);
	rand1 = ((int)(1000 * rand1)) % 20;
	rand2 = sqrtl(rand2);
	rand2 = ((int)(1000 * rand2)) % 20;
	rand2 = abs(rand2), rand1 = abs(rand1);
	if (Snake::board[(int)rand1][(int)rand2] != 1) {
		Snake::board[(int)rand1][(int)rand2] = 2;
		FoodPos.first = rand1, FoodPos.second = rand2;
	}
	else putFood();
}

void Snake::movement() {
	int i = 0;
	for (i = length - 1; i > 0; i--) {
		Body[i].first = Body[i - 1].first;
		Body[i].second = Body[i - 1].second;
	}
	if (direction == 1)
		Body[0].first--;
	else if (direction == 2)
		Body[0].second++;
	else if (direction == 3)
		Body[0].first++;
	else
		Body[0].second--;

	if (Body[0].second > 19)
		Body[0].second = 0;
	if (Body[0].second < 0)
		Body[0].second = 19;
	if (Body[0].first > 19)
		Body[0].first = 0;
	if (Body[0].first < 0)
		Body[0].first = 19;
}

void Snake::steer() {
	if (_kbhit()) {
		int key = _getch();
		switch (key){
		case 119:
			if(direction!=3)
			direction = 1;
			break;
		case 100:
			if (direction != 4)
			direction = 2;
			break;
		case 115:
			if (direction != 1)
			direction = 3;
			break;
		case 97:
			if (direction != 2)
			direction = 4;
			break;
		default:
			break;
		}
	}


}

void Snake::getFood() {
	if ((Body[0].first == FoodPos.first) && (Body[0].second == FoodPos.second)) {
		putFood();
		length++;
		score = score + 50;
		pair<int, int> tail = make_pair(Body[Body.size() - 1].first, Body[Body.size() - 1].second);
		pair<int, int> retail = make_pair(Body[Body.size() - 1].first, Body[Body.size() - 1].second);
		/*
		if (FoodPos.first == 0) {
			Body.push_back(make_pair(tail.first + 1, tail.second));
			return;
		}
		if (FoodPos.first == 19) {
			Body.push_back(make_pair(tail.first - 1, tail.second));
			return;
		}
		if (FoodPos.second == 0) {
			Body.push_back(make_pair(tail.first, tail.second + 1));
			return;
		}
		if (FoodPos.second == 19) {
			Body.push_back(make_pair(tail.first + 1, tail.second - 1));
			return;
		}*/
		if (board[retail.first][retail.second + 1] != 0) {
			tail.first++;
			tail.second--;
			if (board[retail.first + 1][retail.second] != 0) {
				tail.first--;
				tail.second--;
			}
			if (board[retail.first][retail.second - 1] != 0) {
				tail.first--;
				tail.second++;
			}
		}

		Body.push_back(make_pair(tail.first, tail.second+1));
	}
}

void Snake::apply_Body() {

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			board[i][j] = 0;
	board[FoodPos.first][FoodPos.second]=2;
	for (int i = 0; i < length; i++) {
		board[Body[i].first][Body[i].second] = 1;
	}

}

int main() {
	Snake snake;
	int speed;
	cout << "welcome to Snake game\t\t\nChoose a level for Snake speed \n1 2 3 :\n";
	cin >> speed;
	if (speed == 1)
		speed = 40;
	else if (speed == 2)
		speed = 65;
	else
		speed = 90;
	Sleep(400);
	system("cls");
	snake.print_board();
	snake.putFood();
	while (snake.game_over()) {
		snake.movement();
		snake.getFood();
		snake.apply_Body();
		snake.steer();
		snake.print_board();
		Sleep(75);
	}
	snake.print_board();
	
	return 0;
}