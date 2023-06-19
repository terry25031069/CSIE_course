#include<string>
#include<cctype>
#include<algorithm>
#include<vector>
using namespace std;

class card {
public:
	card();
	void card_in(int suit, int num);
	int card_num();
	int card_suit();
	static void print_line(card a[], int num, int n,int _sort);

private:
	int _suit;
	int _number;
	string cface[18];
};

class player{
public:
	player();
	int carda[100];
	int cardn, cord[100],cover;
	card Card[100];
	bool check(card a[]);
	void output();
	bool playcard(int n, card a[]);
	void computerplay(card a[]);
};
