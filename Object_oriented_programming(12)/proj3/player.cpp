#include<iostream>
#include<algorithm>
#include"card.h"
using namespace std;

player::player() {
	cover = 0;
	cardn = 13;
	for (int i = 0; i < 13; i++)carda[i] = 13;
	memset(cord, 0, sizeof(cord));
}

bool player::check(card a[]) {
	int flag = 0, i = 0, tmp = 0;
	//偵測手牌是否有7
	for (int j = cardn; j >= 0; j--) {
		if (Card[j].card_num() == 7) {
			flag = 1, cord[tmp++] = j;
			carda[j] = 3 + Card[j].card_suit();
		}
	}
	if (flag == 1)return tmp;
	else {
		//偵測是否有手牌可以接
		tmp = 0;
		for (i = 0; i < 4; i++) {
			for (int j = 0; j < cardn; j++) {
				if (Card[j].card_suit() == a[i].card_suit() && Card[j].card_num() == a[i].card_num() + 1) {
					if (a[i].card_suit()) {
						flag = 1, cord[tmp++] = j;
						carda[j] = i;
					}
				}
			}
		}
		for (i = 8; i < 12; i++) {
			for (int j = 0; j < cardn; j++) {
				if (Card[j].card_suit() == a[i].card_suit() && Card[j].card_num() == a[i].card_num() - 1) {
					if (a[i].card_suit()) {
						flag = 1, cord[tmp++] = j;
						carda[j] = i;
					}
				}
			}
		}
	}
	return tmp;
}

void player::output() {
	for (int i = 0; i < 13; i++) {
		int a = Card[i].card_suit();
		if (a == 1)cout << "梅花 ";
		else if (a == 2) cout << "方塊 ";
		else if (a == 3)cout << "紅心 ";
		else cout << "黑桃 ";
		cout << Card[i].card_num() << ' ';
	}
	cout << endl;
}

bool player::playcard(int n, card a[]) {
	if (check(a)) {
		if (carda[n]==13)return 0;
		else {
			a[carda[n]] = Card[n];
			if (Card[n].card_num() == 7)a[Card[n].card_suit() - 1] = a[Card[n].card_suit() + 7] = Card[n];
			Card[n].card_in(0, 0);
			for (int i = 0; i < 13; i++)carda[i] = 13;
			return 1;
		}
	}
	else {
		cover += Card[n].card_num();
		Card[n].card_in(0, 0);
		return 1;
	}
}

void player::computerplay(card a[]) {
	int tmp = check(a);
	if (!tmp) {
		for (int i = 0; i < 13; i++) {
			if (Card[i].card_suit() && Card[i].card_num()) {
				cover += Card[i].card_num();
				Card[i].card_in(0, 0);
				break;
			}
		}
	}
	else {
		cout << endl;
		int n = cord[0];
		a[carda[n]] = Card[n];
		if (Card[n].card_num() == 7)a[Card[n].card_suit() - 1] = a[Card[n].card_suit() + 7] = Card[n];
		Card[n].card_in(0, 0);
		for (int i = 0; i < 13; i++)carda[i] = 13;
	}
	memset(cord, 0, sizeof(cord));
}