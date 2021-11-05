#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int headX, headY, bodyLength, tailX, tailY, fruitX, fruitY, score;
int bodyX[100], bodyY[100];

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	headX = width / 2;
	headY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw() {
	system("cls");
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				cout << '#';
			} else if (j == width - 1) {
				cout << '#';
			} else if (i == headY && j == headX) {
				cout << 'O';
			} else if (i == fruitY && j == fruitX) {
				cout << '*';
			} else {
				bool print = false;
				for (int k = 0; k < bodyLength; k++){
					if (headX == bodyX[k] && headY == bodyY[k]) {
						gameOver = true;
					} else if (bodyX[k] == j && bodyY[k] == i) {
						cout << 'o';
						print = true;
					}
				}
				if (!print) {
					cout << ' ';
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score;
	cout << "Fruit: " << fruitX << ',' << fruitY;
	cout << "Head: " << headX << ',' << headY;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic() {
	int prevX = bodyX[0];
	int prevY = bodyY[0];
	int prev2X, prev2Y;
	bodyX[0] = headX;
	bodyY[0] = headY;
	for (int i = 1; i < bodyLength; i++)
	{
		prev2X = bodyX[i];
		prev2Y = bodyY[i];
		bodyX[i] = prevX;
		bodyY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		headX--;
		break;
	case RIGHT:
		headX++;
		break;
	case UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	default:
		break;
	}
	if (headX >= width) {
		headX = 0;
	} else if (headX <= 0) {
		headX = width - 1;
	}
	if (headY >= height) {
		headY = 0;
	} else if (headY <= 0) {
		headY = height - 1;
	}
	if (headX == fruitX && headY == fruitY) {
		score += 1;
		fruitX = rand() % width;
		fruitY = rand() % height;
		bodyLength++;
	}
}

int main() {
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
	return 0;
}