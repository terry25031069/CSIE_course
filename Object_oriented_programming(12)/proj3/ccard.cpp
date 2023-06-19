#include<string>
#include"card.h"
#include<iostream>
#include<utility>
#include<windows.h>
using namespace std;

string __suit[5][8] = {
{" *****   ***** "
,"   *       *   "
,"    **   **    "
,"     *****     "
,"     *****     "
,"    **   **    "
,"   *       *   "
," *****   ***** " },

{"      ***      "
,"     *****     "
," ***   *   *** "
,"***** **** ****"
,"***************"
," ***   *   *** "
,"       *       "
,"     *****     " },

{"       *       "
,"     *****     "
,"   *********   "
,"  ***********  "
,"   *********   "
,"    *******    "
,"     *****     "
,"       *       " },

{"   ***   ***   "
," ************* "
,"***************"
," ************* "
,"  ***********  "
,"   ********    "
,"     *****     "
,"       *      " },

{"       *       "
,"    *******    "
," ************* "
,"***************"
,"***************"
," ****  *  **** "
,"      ***      "
,"     *****     " }
};

void SetColor(int f = 7, int b = 0) {
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}

card::card() {
	_suit = 0;
	_number = 0;
	for (int i = 0; i < 18; i++)card::cface[i] = "                       ";
	card_in(_suit, _number);
}

void card::card_in(int suit, int num) {
	_suit = suit;
	_number = num;
	int r = 16, c = 21;
	for (int i = 0; i < 18; i++)cface[i] = "                       ";
	for (int i = 0; i < c; i++)cface[0][i] = cface[r - 1][i] = '-';
	for (int i = 1; i < r - 1; i++)cface[i][0] = cface[i][c - 1] = '|';

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 15; j++) {
			cface[i + 4][j + 3] = __suit[suit][i][j];
		}
	}

	if (_number == 1)cface[2][2] = cface[r - 3][c - 3] = 'A';
	else if (_number > 1 && _number < 10)cface[2][2] = cface[r - 3][c - 3] = (char)'0' + _number;
	else if (_number == 10) {
		cface[2][2] = cface[r - 3][c - 4] = '1', cface[2][3] = cface[r - 3][c - 3] = '0';
	}
	else cface[2][2] = cface[r - 3][c - 3] = (_number == 11 ? 'J' : (_number == 12 ? 'Q' : (_number == 13 ? 'K' : ' ')));
}

int card::card_num() {
	return _number;
}

int card::card_suit() {
	return _suit;
}

void card::print_line(card a[], int num, int n ,int _sort) {
	string _print[18] = {};
	int tmp = 0;
	if(_sort)sort(a, a + num, [](card aa, card bb) {
		if(aa.card_suit() != bb.card_suit())return aa.card_suit() < bb.card_suit(); 
		return aa.card_num() < bb.card_num();
	});
	for (int i = 0; i < num; i++) {
		for (int ii = 0; ii < 18; ii++) {
			_print[ii] += ' ' + a[i].cface[ii];
		}
		tmp++;
		if (tmp % n == 0) {
			for (int ii = 0; ii < 16; ii++) {
				for (int jj = 0; jj < _print[ii].size(); jj++) {
					if (jj % 24 == 0) {
						cout << _print[ii][jj];
						int coord = (tmp - 1) / n * n + jj / 24, __suit = a[coord].card_suit();
						if (__suit == 2 || __suit == 3) {
							SetColor(4, 7);
						}
						else {
							SetColor(0, 7);
						}
					}
					else {
						if (jj % 24 == 22) {
							SetColor();
							cout << _print[ii][jj];
						}
						else cout << _print[ii][jj];
					}
				}
				SetColor();
				cout << endl;
				_print[ii] = "";
			}
		}
		//cout << endl;
	}

	for (int ii = 0; ii < 16; ii++) {
		for (int jj = 0; jj < _print[ii].size(); jj++) {
			if (jj % 24 == 0) {
				cout << _print[ii][jj];
				//cout << tmp << ' ' << jj ;
				int coord = (tmp - 1) / n * n + jj / 24, __suit = a[coord].card_suit();
				if (__suit == 2 || __suit == 3) {
					SetColor(4, 7);
				}
				else {
					SetColor(0, 7);
				}
			}
			else {
				if (jj % 24 == 22) {
					SetColor();
					cout << _print[ii][jj];
				}
				else cout << _print[ii][jj];
			}
		}
		if(_print[ii].size())cout << endl;
	}
	tmp = 0; SetColor();
}