#include<bits/stdc++.h>
using namespace std;

int dp[105][1005][1005] = {};

int main() {
	int tc, m, v;
	int p[1005], a[1005], b[1005];
	while (cin >> tc >> m >> v) {
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= tc; i++)cin >> p[i];
		for (int i = 1; i <= tc; i++)cin >> a[i];
		for (int i = 1; i <= tc; i++)cin >> b[i];
		for (int i = 1; i <= tc; i++) {
			for (int j = m; j >= 0; j--) {
				for (int k = v; k >= 0; k--) {
					if ((j - a[i] < 0) || (k - b[i] < 0))dp[i][j][k] = dp[i - 1][j][k];
					else dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - a[i]][k - b[i]] + p[i]);
				}
			}
		}
		int ma = 0, i = tc, jj = m, kk = v;;
		for (int i = 0; i <= m; i++)for (int j = 0; j <= v; j++) {
			if (dp[tc][i][j] > ma) {
				ma = dp[tc][i][j];
				jj = i, kk = j;
			}
		}
		cout << ma << endl;
		vector<int>ans;
		while (kk > 0 && jj > 0) {
			if (dp[i][jj][kk] == dp[i - 1][jj - a[i]][kk - b[i]] + p[i]) {
				ans.push_back(i);
				jj -= a[i], kk -= b[i];
			}
			i--;
		}
		sort(ans.begin(),ans.end());
		cout << ans.size() << endl;
		cout << "(" << ans[0];
		for (int i = 1; i < ans.size(); i++)cout << "," << ans[i];
		cout << ")\n";
	}
}
