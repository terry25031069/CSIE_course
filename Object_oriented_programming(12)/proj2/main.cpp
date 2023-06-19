#include<regex>
#include<time.h>
#include"card.h"
#include<string>
#include<cctype>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

bool pokayoke(string s, int _begin, int _end) {
	int flag = 0;
	for (int i = 0; i < s.size(); i++) {
		if (!isdigit(s[i])) {
			cout << "輸入錯誤，請重新輸入\n";
			return 0;
		}
	}
	int num = stoi(s);
	if (num > _end || num < _begin) {
		cout << "輸入錯誤，請重新輸入\n";
		return 0;
	}
	return 1;
}

int main() {
	string num, sor1, line, sor2, check;
	int pointer = 0;
yee: {};
	srand(time(NULL));
	int flag = 0, a[100] = {};
	for (int i = 0; i < 52; i++)a[i] = i;
	random_shuffle(a, a + 52, [](int i) {return rand() % i; });
	pointer = 0;
	while (1) {
		if (52 - pointer > 0) {
			cout << "-------------------------------------------------------------------\n";
			cout << "| 請輸入撲克牌總張數，輸入完畢請按Enter鍵：                       |\n";
			cout << "| （注意：僅能輸入1-";
			cout << 52 - pointer;
			if (52 - pointer < 10)cout << ' ';
			cout << "）";
			cout << "                                          |\n";
			cout << "-------------------------------------------------------------------\n";
		}
		else {
			cout << "-------------------------------------------------------------------\n";
			cout << "| 已經沒有牌可以發了QQ                                            |\n";
			cout << "| 想開一副新的撲克牌，請輸入1之後按Enter鍵，輸入0結束程式         |\n";
			cout << "-------------------------------------------------------------------\n";
			while (getline(cin, check)) {
				if ((pokayoke(check, 0, 1) == 1))break;
			}
			if (check == "0")break;
			else goto yee;
		}
		while (getline(cin, num)) {
			if ((pokayoke(num, 1, 52 - pointer) == 1))break;
		}
		cout << "-------------------------------------------------------------------\n";
		cout << "| 請輸入撲克牌每行張數，輸入完畢請按Enter鍵：                     |\n";
		cout << "| （注意：僅能輸入1-7）                                           |\n";
		cout << "-------------------------------------------------------------------\n";
		while (getline(cin, line)) {
			if ((pokayoke(line, 1, 7) == 1))break;
		}
		cout << "-------------------------------------------------------------------\n";
		cout << "| 請輸入撲克牌花色排序方式，輸入完畢請按Enter鍵：                 |\n";
		cout << "| 1.梅花                                                          |\n";
		cout << "| 2.方塊                                                          |\n";
		cout << "| 3.愛心                                                          |\n";
		cout << "| 4.黑桃                                                          |\n";
		cout << "| （舉例：若想要依照「梅花」，「方塊」，「愛心」，「黑桃」)       |\n";
		cout << "| （請輸入\"1234\"）                                                |\n";
		cout << "| 若不要排序，請輸入3333                                          |\n";
		cout << "-------------------------------------------------------------------\n";
		while (getline(cin, sor1)) {
			int flag = 0; string sor11 = sor1;
			if (pokayoke(sor11, 1234, 4321) == 0)continue;
			sort(sor11.begin(), sor11.end());
			if (sor11 != "1234"&&sor1 != "3333") {
				flag = 1;
				cout << "輸入錯誤，請重新輸入\n";
			}
			if (flag == 0)break;
		}
		card card[100] = {};
		int pn = pointer;
		for (int i = pointer; i < pointer + stoi(num); i++)card[i - pn].card_in(a[i] / 13 + 1, a[i] % 13 + 1);

		card::print_line(card, stoi(num), stoi(line), sor1);
		pointer += stoi(num);
	}
}
