#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>

using namespace std;
HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int width = 20, height = 12;
COORD console_size = {23, 21};
unsigned short speed = 100;
bool endless = true, gameover;
int x, y, fruitX, fruitY, score, tailX[300], tailY[300], nTail;
enum class eDirection { STOP, LEFT, RIGHT, UP, DOWN };
eDirection dir;
void game();

void Setup() {
	srand(static_cast<unsigned>(time(0)));
	dir = eDirection::STOP;
	for (int x = 0; x < sizeof(tailX) / sizeof(tailX[0]); x++) {
		tailX[x] = NULL;
		tailY[x] = NULL;
	}
	nTail = 2;
	
	gameover = false;
	x = width / 2 - 1;
	y = height / 2 - 1;
	tailX[0] = x - 1;
	tailX[1] = x - 2;
	tailY[0] = y;
	tailY[1] = y;
	fruitX = rand() % (width - 1);
	fruitY = rand() % height;
	score = 0;
}

class Menu {
public:
	enum class menu_obj { PLAY_GAME, SETTINGS, EXIT };
	enum class sett_obj { ENDLESS, BACK };
	menu_obj m_obj = menu_obj::PLAY_GAME;
	sett_obj s_obj = sett_obj::ENDLESS;
	void menu_Input() {
		while (_kbhit()) {
			switch (_getch()) {
				case 's':
					if (m_obj == menu_obj::PLAY_GAME)
						m_obj = menu_obj::SETTINGS;
					else if (m_obj == menu_obj::SETTINGS)
						m_obj = menu_obj::EXIT;
					break;
				case 'w':
					if (m_obj == menu_obj::EXIT)
						m_obj = menu_obj::SETTINGS;
					else if (m_obj == menu_obj::SETTINGS)
						m_obj = menu_obj::PLAY_GAME;
					break;
				case VK_RETURN:
					if (m_obj == menu_obj::PLAY_GAME) {
						game();
					}
					else if (m_obj == menu_obj::SETTINGS)
						settings();
					else if (m_obj == menu_obj::EXIT)
						exit(0);
			}
		}
	}
	void settings_Input() {
		while (_kbhit()) {
			switch (_getch()) {
				case 's':
					s_obj = sett_obj::BACK;
					break;
				case 'w':
					s_obj = sett_obj::ENDLESS;
					break;
				case VK_RETURN:
					if (s_obj == sett_obj::ENDLESS)
						if (endless)
							endless = false;
						else {
							endless = true;

						}
					else if (s_obj == sett_obj::BACK) {
						m_obj = menu_obj::PLAY_GAME;
						s_obj = sett_obj::ENDLESS;
						menu();
					}
			}
		}
	}
	void menu_refresh() {
		menu_Input();
		FlushConsoleInputBuffer(hconsole);
		system("cls");
		for (int i = 0; i < width + 1; i++)
			cout << "#";
		cout << endl;
		for (int i = 0; i < height - 4; i++) {
			for (int j = 0; j < width + 1; j++) {
				if (j == 0 || j == width)
					cout << "#";
				else if (i == 1 && j == 1) {
					//       #                   #
					cout << "     Main Menu     #" << endl << "# ";
					
				}
				else if (i == 2 && j == 1) {
					//      #                   #
					cout << "####################" << endl << "# ";

				}
				else if (i == 3 && j == 1) {
					cout << "     ";
					if (m_obj == menu_obj::PLAY_GAME)
						SetConsoleTextAttribute(hconsole, 240);
					//       #                   #
					cout << "Play Game";
					SetConsoleTextAttribute(hconsole, 7);
					cout << "     #" << endl << "# ";
					continue;
					
				}
				else if (i == 4 && j == 1) {
					cout << "     ";
					if (m_obj == menu_obj::SETTINGS)
						SetConsoleTextAttribute(hconsole, 240);
					//       #                   #
					cout << "Settings";
					SetConsoleTextAttribute(hconsole, 7);
					cout << "      #" << endl << "# ";
					continue;
				}
				else if (i == 5 && j == 1) {
					cout << "     ";
					if (m_obj == menu_obj::EXIT)
						SetConsoleTextAttribute(hconsole, 240);
					//       #                   #
					cout << "Exit";
					SetConsoleTextAttribute(hconsole, 7);
					cout << "          #" << endl << "# ";
					continue;
				}
				else
					cout << " ";
			}
		
			cout << endl;
			
		}
		
		for (int i = 0; i < width + 1; i++)
			cout << "#";
	}
	void settings_refresh() {
		settings_Input();
		FlushConsoleInputBuffer(hconsole);
		system("cls");
		for (int i = 0; i < width + 1; i++)
			cout << "#";
		cout << endl;
		for (int i = 0; i < height - 3; i++) {
			for (int j = 0; j < width + 1; j++) {
				if (j == 0 || j == width)
					cout << "#";
				else if (i == 1 && j == 1) {
					//      #                   #
					cout << "      Settings     #" << endl << "# ";

				}
				else if (i == 2 && j == 1) {
					//      #                   #
					cout << "####################" << endl << "# ";

				}
				else if (i == 4 && j == 1) {
					//      #                   #
					cout << "    ";
					if (s_obj == sett_obj::ENDLESS)
					SetConsoleTextAttribute(hconsole, 240);
					cout << "Endless: ";
					if (endless)
						cout << "On";
					else
						cout << "Off";
					SetConsoleTextAttribute(hconsole, 7);
					if (endless)
						cout << "    #" << endl << "# ";
					else 
						cout << "   #" << endl << "# ";
				}
				else if (i == 6 && j == 1) {
					cout << "    ";
					if (s_obj == sett_obj::BACK)
					SetConsoleTextAttribute(hconsole, 240);
					cout << "Back";
					SetConsoleTextAttribute(hconsole, 7);
					cout << "           #" << endl << "# ";
				}
				else
					cout << " ";
			}

			cout << endl;
		}
		for (int i = 0; i < width + 1; i++)
			cout << "#";
	}
	void menu() {
		while (true) {
			menu_refresh();
			Sleep(speed);
		}
	}
	void settings() {
		while (true) {
			settings_refresh();
			Sleep(speed);
		}
	}
};



Menu menu;
void Draw() {
	system("cls");
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "O";
					}
				}
				if (!print)
					cout << " ";
			}
			
		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl << endl << "Score: " << score;
	cout << endl << "x = " << x << "  y = " << y;
	cout << endl << endl << "F_x = " << fruitX << "  F_y = " << fruitY;
	cout << endl << "Endless = ";
	if (endless)
		cout << "On";
	else
		cout << "Off";

	Sleep(150);
}
void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			if (dir != eDirection::RIGHT)
				dir = eDirection::LEFT;
			break;
		case 'd':
			if (dir != eDirection::LEFT)
			dir = eDirection::RIGHT;
			break;
		case 'w':
			if (dir != eDirection::DOWN)
			dir = eDirection::UP;
			break;
		case 's':
			if (dir != eDirection::UP)
			dir = eDirection::DOWN;
			break;
		case 'q':
			gameover = true;
			break;
		case 'z':
			system("pause");
			break;
		case 'p':
			gameover = true;
			menu.menu();
		}
	}
}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	Input();
	if (!(dir == eDirection::STOP)) {
		tailX[0] = x;
		tailY[0] = y;
		for (int i = 1; i < nTail; i++) {
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
	}
	switch (dir) {
	case eDirection::LEFT:
		x--;
		break;
	case eDirection::RIGHT:
		x++;
		break;
	case eDirection::DOWN:
		y++;
		break;
	case eDirection::UP:
		y--;
		break;
	case eDirection::STOP:
		break;
	}
	if (x == fruitX && y == fruitY) {
		score++;
		fruitX = rand() % (width - 1);
		fruitY = rand() % height;
		nTail++;
	}

	if ((x == -1 || x == width - 1 || y == -1 || y == height) && !endless) {
		gameover = true;
	}
	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;
	if (y >= height)
		y = 0;
	else if (y < 0) {
		y = height - 1;
	}
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y && !(dir == eDirection::STOP))
			gameover = true;
	}
	for (int x = 0; x < nTail; x++) {
		if (fruitX == tailX[x] && fruitY == tailY[x]) {
			fruitX = rand() % (width - 1);
			fruitY = rand() % height;
			break;
		}
	}
}
void game() {
	Setup();
	while (!gameover) {
		Draw();
		Input();
		Logic();
	}
	if (gameover) {
		menu.menu();
	}
}
int main() {
	SetConsoleScreenBufferSize(hconsole, console_size);
	system("mode con cols=23 lines=21");
	menu.menu();
	return 0;
}