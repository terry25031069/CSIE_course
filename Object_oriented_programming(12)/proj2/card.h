#include<string>
#include<cctype>
#include<algorithm>
using namespace std;

class card {
public:
	card();
	void card_in(int suit, int num);
	pair<int, int> card_out();
	static void print_line(card a[], int num, int n, string sor1);

private:
	int _suit;
	int _number;
	string cface[18];
};
