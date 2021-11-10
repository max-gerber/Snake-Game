#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver, walls;
const int width = 20;
const int height = 20;
int headX, headY, bodyLength, tailX, tailY, fruitX, fruitY, score, speed;
int bodyX[100], bodyY[100];

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

// Pregame configuration
void Setup() {
	gameOver = false;
	walls = false;
	dir = STOP;
	headX = width / 2;
	headY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	speed = 0;
	// manage flags
	for (int i = 0; i < argc; i++)
	{
		string arg = argv[i];
		if (arg == "-w"){
			walls = true;
		} if (arg == "-m"){
			speed = 50;
		} if (arg == "-s"){
			speed = 100;
		}
	}
}

//Represent the game visually
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
				//Display the snake
				bool print = false;
				for (int k = 0; k < bodyLength; k++){
					//Check if eaten tail
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
}

//Manage keyboard input
void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			if (dir != RIGHT) {
				dir = LEFT;
			}
			break;
		case 'd':
			if (dir != LEFT) {
				dir = RIGHT;
			}
			break;
		case 'w':
			if (dir != DOWN) {
				dir = UP;
			}
			break;
		case 's':
			if (dir != UP) {
				dir = DOWN;
			}
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
	int storeX, storeY;
	bodyX[0] = headX;
	bodyY[0] = headY;
	//Move snake body one coordinate at a time
	for (int i = 1; i < bodyLength; i++)
	{
		storeX = bodyX[i];
		storeY = bodyY[i];
		bodyX[i] = prevX;
		bodyY[i] = prevY;
		prevX = storeX;
		prevY = storeY;
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
	//Encounter with walls, if wall(-w) flag is on contact will terminate the game, otherwise snake will loop around
	if (headX >= width) {
		if (walls){
			gameOver = true;
		} else {
			headX = 0;
		}
		headX = 0;
	} else if (headX < 0) {
		if (walls){
			gameOver = true;
		} else {
			headX = width;
		}
	}
	if (headY >= height) {
		if (walls){
			gameOver = true;
		} else {
			headY = 0;
		}
	} else if (headY < 0) {
		if (walls){
			gameOver = true;
		} else {
			headY = height;
		}
	}
	if (headX == fruitX && headY == fruitY) {
		score += 1;
		fruitX = rand() % width;
		fruitY = rand() % height;
		bodyLength++;
	}
}

int main(int argc, char* argv[]) {
	Setup(argc, argv);
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(speed);
	}
	return 0;
}
