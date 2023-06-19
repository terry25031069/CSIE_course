#include<string>
#include<cctype>
#include<algorithm>
using namespace std;

class card{
public:
	card();
	void card_in(int suit, int num);
	string suit_out();
	pair<string, int> card_out();
	void print();
private:
	int _suit;
	int _number;
};
