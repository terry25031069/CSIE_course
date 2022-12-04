#include<bits/stdc++.h>
using namespace std;

double e[300][300], d[300];int p[300];

struct node {
	int b;double w;
	bool operator < (const node& bb)const {
		return w>bb.w;
	}
};

void dijkstra(int root, int n) {
	for (int i = 0; i <= n; i++)d[i] = 1e10;
	memset(p, 0, sizeof(p));

	priority_queue<node>yee;

	d[root] = p[root] = 0;
	yee.push({ root, d[root] });

	while (!yee.empty()) {
		node tmp = yee.top(); yee.pop();
		for (int i = 1; i <= n; i++) {
			if (d[i]>d[tmp.b] + e[tmp.b][i]) {
				d[i] = d[tmp.b] + e[tmp.b][i];
				p[i] = tmp.b;
				yee.push( { i, d[tmp.b] });
			}
		}
	}
}

int main() {
	int n, m, aa, bb, root;double cc;
	while (cin >> n >> m) {
		memset(e, 0, sizeof(e));
		for (int i = 0; i <= n; i++)for (int j = 0; j <= n; j++)e[i][j] = 1e10 + 1;
		for (int i = 0; i<m; i++) {
			cin >> aa >> bb >> cc;
			e[aa][bb] = cc;
		}
		cin >> root;
		dijkstra(root, n);
		cout<<fixed<<setprecision(3);
		for (int i = 1; i <= n; i++)cout << d[i] << ' ';
		cout << endl;
		for (int i = 1; i <= n; i++)cout << p[i] << ' ';
		cout << endl;
	}
}
