#include<string>
#include"card.h"
#include<iostream>
#include<utility>
#include<windows.h>
using namespace std;

void SetColor(int f = 7, int b = 0)
{
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}
	
card::card() {
	_suit = 0;
	_number = 0;
}

void card::card_in(int suit, int num) {
	_suit = suit;
	_number = num;
}

string card::suit_out() {
	if (_suit == 1)return "梅花";
	if (_suit == 2)return "方塊";
	if (_suit == 3)return "愛心";
	if (_suit == 4)return "黑桃";
}

pair<string, int> card::card_out() {
	if (_suit == 1)return make_pair("梅花", _number);
	if (_suit == 2)return make_pair("方塊", _number);
	if (_suit == 3)return make_pair("愛心", _number);
	if (_suit == 4)return make_pair("黑桃", _number);

}

void card::print() {
	int r = 16, c = 21;
	char cface[18][23] = {};
	string club[8] =
	{"      ***      "
	,"     *****     "
	," ***   *   *** "
	,"***** **** ****"
	,"***************"
	," ***   *   *** "
	,"       *       "
	,"     *****     " };

	string diam[8] = 
	{"       *       "
	,"     *****     "
	,"   *********   "
	,"  ***********  "
	,"   *********   "
	,"    *******    "
	,"     *****     "
	,"       *       " };

	string heart[8] = 
	{"   ***   ***   "
	," ************* "
	,"***************"
	," ************* "
	,"  ***********  "
	,"   ********    "
	,"     *****     "
	,"       *      "};

	string spare[8] = 
	{"       *       "
	,"    *******    "
	," ************* "
	,"***************"
	,"***************"
	," ****  *  **** "
	,"      ***      "
	,"     *****     "
	};


	for (int i = 0; i < c; i++)cface[0][i] = cface[r-1][i] = '-';
	for (int i = 1; i < r-1; i++)cface[i][0] = cface[i][c-1] = '|';
	
	//鑲嵌花色至卡牌中心
	if (_suit == 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 15; j++) {
				cface[i + 4][j + 3] = club[i][j];
			}
		}
	}
	else if(_suit == 2) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 15; j++) {
				cface[i + 4][j + 3] = diam[i][j];
			}
		}
	}
	else if (_suit == 3) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 15; j++) {
				cface[i + 4][j + 3] = heart[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 15; j++) {
				cface[i + 4][j + 3] = spare[i][j];
			}
		}
	}
	//鑲嵌數字
	if(_number == 1)cface[2][2] = cface[r - 3][c - 3] = 'A';
	else if (_number>1&&_number < 10)cface[2][2] = cface[r-3][c-3] = (char)'0' + _number;
	else if (_number == 10) {
		cface[2][2] = cface[r-3][c-4] = '1', cface[2][3] = cface[r-3][c-3] = '0';
	}
	else cface[2][2] = cface[r-3][c-3] = (_number == 11 ? 'J' : (_number == 12 ? 'Q' : 'K'));

	//輸出
	if (_suit == 2 || _suit == 3) {
		SetColor(4, 7);
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++)cout << cface[i][j]; cout << endl;
		}
		SetColor();
	}
	else {
		SetColor(0, 7);
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++)cout << cface[i][j]; cout << endl;
		}
		SetColor();
	}
	cout << endl;
}