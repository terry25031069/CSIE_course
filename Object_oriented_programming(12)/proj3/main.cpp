#include<time.h>
#include"card.h"
#include<string>
#include<cctype>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
	//各種宣告
	string s;
	int flag = 0, aa[100] = {},num;
	card a[100] = {}, table[12] = {};
	player p[4];

	//洗牌，發牌，整牌
	int T = time(NULL);
	//int T = 1557930574;
	srand(T);
	//cout << T << endl;
	for (int i = 0; i < 52; i++)aa[i] = i;
	for (int I = 0; I < 4; I++)random_shuffle(aa, aa + 52, [](int i) {return rand() % i; });
	for (int i = 0; i < 52; i++)a[i].card_in(aa[i] / 13 + 1, aa[i] % 13 + 1);
	for (int i = 0; i < 52; i++)p[i / 13].Card[i % 13] = a[i];
	for (int i = 0; i < 4; i++) {
		sort(p[i].Card, p[i].Card+13,
		[](card aa, card bb) {
		if(aa.card_suit()!=bb.card_suit())return aa.card_suit() < bb.card_suit(); 
		return aa.card_num() < bb.card_num();
		});
	}

	//讓擁有黑桃7的人先出(利用排序使他變成第零位玩家)
	sort(p, p + 4, [](player a, player b) {
		int aa = 0, bb = 0;
		for (int i = 0; i < 13; i++) (a.Card[i].card_num() == 7) && (aa = max(aa, a.Card[i].card_suit()));
		for (int i = 0; i < 13; i++) (b.Card[i].card_num() == 7) && (bb = max(bb, b.Card[i].card_suit()));
		return aa > bb;
	});

	int tc = 13, flagg=0;
	while(tc--) {
		cout << "目前場面上的牌：\n";
		card::print_line(table, 12, 4, 0);
		cout<< "\n目前你手上的牌：\n";
		card::print_line(p[0].Card, 13, 7, 0);
		cout << "輸入你要出第幾張牌：(刪除的牌也算歐，請不要忽略)\n";
		while (getline(cin,s)) {
			for (int i = 0; i < s.size(); i++) {
				if (!isdigit(s[i])) {
					flagg = 1;
					cout << "輸入錯誤，請重新輸入\n";
					break;
				}
			}
			if (!flagg) {
				num = stoi(s);
				num -= 1;
				if (p[0].Card[num].card_num() && p[0].Card[num].card_suit()&&num>-1&&num<13) {
					if (p[0].playcard(num, table))break;
					else {
						cout << "阿歐，這不是你能出的牌歐，請重新輸入\n";
					}
				}
				else {
					cout << "輸入錯誤，請重新輸入\n";
				}
			}
		}
		card::print_line(table, 12, 4, 0);
		for (int i = 1; i < 4; i++) {
			p[i].computerplay(table);
		}
	}
	pair<int,int> rank[4] = {};
	for (int i = 0; i < 4; i++)rank[i].first =i,rank[i].second= p[i].cover;
	sort(rank, rank + 4, [](pair<int, int>aa, pair<int, int>bb) {return aa.second < bb.second; });
	for (int i = 0; i < 4; i++) {
		cout << "第" << i + 1 << "名是:";
		if(rank[i].first!=0)cout<<" 第" << rank[i].first << "位電腦玩家，";
		else cout << "是你！";
		cout << "蓋了" << rank[i].second << "點\n";
	}
	system("pause");
}