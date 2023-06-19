#include<string>
#include"card.h"
#include<iostream>
#include<utility>
#include<windows.h>
using namespace std;

string club[8] =
{ "      ***      "
,"     *****     "
," ***   *   *** "
,"***** **** ****"
,"***************"
," ***   *   *** "
,"       *       "
,"     *****     " };

string diam[8] =
{ "       *       "
,"     *****     "
,"   *********   "
,"  ***********  "
,"   *********   "
,"    *******    "
,"     *****     "
,"       *       " };

string heart[8] =
{ "   ***   ***   "
," ************* "
,"***************"
," ************* "
,"  ***********  "
,"   ********    "
,"     *****     "
,"       *      " };

string spare[8] =
{ "       *       "
,"    *******    "
," ************* "
,"***************"
,"***************"
," ****  *  **** "
,"      ***      "
,"     *****     " };

void SetColor(int f = 7, int b = 0)
{
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}

card::card() {
	_suit = 0;
	_number = 0;
	for (int i = 0; i < 18; i++)card::cface[i] = "                       ";
}

void card::card_in(int suit, int num) {
	_suit = suit;
	_number = num;
	int r = 16, c = 21;
	for (int i = 0; i < c; i++)cface[0][i] = cface[r - 1][i] = '-';
	for (int i = 1; i < r - 1; i++)cface[i][0] = cface[i][c - 1] = '|';

	if (_suit == 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 15; j++) {
				cface[i + 4][j + 3] = club[i][j];
			}
		}
	}
	else if (_suit == 2) {
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

	if (_number == 1)cface[2][2] = cface[r - 3][c - 3] = 'A';
	else if (_number > 1 && _number < 10)cface[2][2] = cface[r - 3][c - 3] = (char)'0' + _number;
	else if (_number == 10) {
		cface[2][2] = cface[r - 3][c - 4] = '1', cface[2][3] = cface[r - 3][c - 3] = '0';
	}
	else cface[2][2] = cface[r - 3][c - 3] = (_number == 11 ? 'J' : (_number == 12 ? 'Q' : 'K'));
}

pair<int, int> card::card_out() {
	return make_pair(_suit, _number);
}


void card::print_line(card a[], int num, int n, string sor1) {
	string _print[18] = {};
	int _sort[5] = {}, tmp = 0;
	for (int i = 0; i < sor1.size(); i++)_sort[sor1[i] - '0'] = i;
	if (sor1 != "3333")sort(a, a + num, [&](card aa, card bb) {
		int af = aa.card_out().first, bf = bb.card_out().first;
		return (_sort[af] < _sort[bf]); }
	);
	//for (int i = 0; i < num; i++)cout << a[i].card_out().first << ' ' << a[i].card_out().second << endl;
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
						//cout << tmp << ' ' << jj ;
						int coord = (tmp - 1) / n * n + jj / 24, __suit = a[coord].card_out().first;
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
		cout << endl;
	}
	for (int ii = 0; ii < 16; ii++) {
		for (int jj = 0; jj < _print[ii].size(); jj++) {
			if (jj % 24 == 0) {
				cout << _print[ii][jj];
				//cout << tmp << ' ' << jj ;
				int coord = (tmp - 1) / n * n + jj / 24, __suit = a[coord].card_out().first;
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
		cout << endl;
	}
	tmp = 0; SetColor();
}