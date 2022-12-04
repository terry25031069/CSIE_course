#include<bits/stdc++.h>
using namespace std;

int main() {
	int tc;
	while (cin >> tc) {
		vector<int>ans; ans.clear();
		int p[1000] = {}, b[1000] = {};
		for (int i = 1; i <= tc; i++)cin >> p[i], b[i] = i;
		for (int i = 1; i <= tc; i++) {
			for (int j = 1; j + i <= tc; j++) {
				if (p[j + i] < p[j] + p[i])b[j + i] = j,p[j + i] = p[j] + p[i];
			}
		}
		cout << p[tc] << endl;
		int point = tc;
		if (point == b[point])ans.push_back(point);
		else{
			while (point != b[point])ans.push_back(point - b[point]),point = b[point];
			ans.push_back(point);
		}
		cout << (ans.size()?ans.size():1) << endl;
		cout << tc << "=" << ans[0];
		for (int i = 1; i < ans.size(); i++)cout << '+' << ans[i];
		cout << endl;
	}
}
