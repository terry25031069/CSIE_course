#include<iostream>
#include"card.h"
#include<string>
#include<regex>
#include<cstdlib>
#include<time.h>
using namespace std;

int main() {
	string suit, num;
	while (1) {
		srand(time(NULL));
		//簡易UI
		cout << "---------------------------------------------------------\n";
		cout << "| 請輸入您要的花色所代表的數字，輸入完畢請按Enter鍵：   |\n";
		cout << "| （注意：僅能輸入一位數字）                            |\n";
		cout << "|                                                       |\n";
		cout << "| 1 梅花                                                |\n";
		cout << "| 2 菱形                                                |\n";
		cout << "| 3 愛心                                                |\n";
		cout << "| 4 黑桃                                                |\n";
		cout << "| 5 隨機                                                |\n";
		cout << "---------------------------------------------------------\n";

		//花色防呆，使用regular experssion
		getline(cin, suit);
		regex check1{ "^[^12345]*$" };
		regex check2{ "^[0-9AJQK]$" };
		if (regex_match(suit, check1) || suit.size() != 1) {
			cout << "輸入錯誤!\n";
		}
		else {
			cout << "---------------------------------------------------------\n";
			cout << "| 請輸入您要的數字(1~14)，輸入完畢請按Enter鍵:          |\n";
			cout << "|(輸入14則代表隨機)              　　　                 |\n";
			cout << "---------------------------------------------------------\n";
			getline(cin, num);
			if (!((regex_match(num, check2) && num.size() == 1) || (num == "10") || (num == "11") || (num == "12") || (num == "13") || (num == "14"))) {
				cout << "輸入錯誤!\n";
			}
			else {
				if (num == "A")num = "1";
				if (num == "J")num = "11";
				if (num == "Q")num = "12";
				if (num == "K")num = "13";
				int suitn = stoi(suit), numn = stoi(num);
				if (suitn == 5)suitn = rand() % 4 + 1;
				if (numn == 14)numn = rand() % 13 + 1;

				card card1;
				card1.card_in(suitn, numn);
				cout << card1.card_out().first << ' ';

				if (card1.card_out().second == 1)cout << "A" << endl;
				else if (card1.card_out().second == 11)cout << "J" << endl;
				else if (card1.card_out().second == 12)cout << "Q" << endl;
				else if (card1.card_out().second == 13)cout << "K" << endl;
				else cout << card1.card_out().second << endl;

				card1.print();
			}
		}
	}
}
