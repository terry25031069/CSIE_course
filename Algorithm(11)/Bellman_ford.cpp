#include<bits/stdc++.h>
using namespace std;

double a[100][100], d[100];
int p[100];

void bellman_ford(int root, int n){
	for (int i = 1; i <= n; i++)d[i] = 1e9;
	d[root] = 0, p[root] = 0;
	for (int i = 0; i < n - 1; i++){
		for (int j = 1; j <= n; j++){
			for (int k = 1; k <= n; k++){
				if (d[j] != 1e9 && a[j][k] != 1e9){
					if (d[j] + a[j][k]<d[k]){
						d[k] = d[j] + a[j][k], p[k] = j;
					}
				}
			}
		}
	}
}

bool nega_cyc(int n){
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (d[i] != 1e9 &&a[i][j] != 1e9)
			if (d[i] + a[i][j] < d[j]){
				return 0;
			}
		}
	}
	return 1;
}

int main(){
	int n, m, aa, bb; double dd;
	while (cin >> n >> m){
		for (int i = 0; i <= n; i++)for (int j = 0; j <= n; j++){
			a[i][j] = 1e9;
		}
		memset(p, 0, sizeof(p));
		for (int i = 0; i<m; i++){
			cin >> aa >> bb >> dd;
			a[aa][bb] = min(a[aa][bb], dd);
		}
		cin >> aa;
		bellman_ford(aa, n);
		int t = nega_cyc(n);
		if (t){
			cout << fixed << setprecision(3);
			for (int i = 1; i <= n; i++)cout << d[i] << " \n"[i == n];
			for (int i = 1; i <= n; i++)cout << p[i] << " \n"[i == n];
		}
		else cout << "There is a negative weight cycle in the graph\n";
	}
}
