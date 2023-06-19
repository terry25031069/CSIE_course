#include<bits/stdc++.h>
using namespace std;

struct edge{
	int a, b;double data;
	bool operator <(const edge b)const{
		return data>b.data;
	}
};

int main(){
	int n, m, root, aa, bb, cc;
	while (cin >> n >> m){
		priority_queue<edge>yee;
		int visit[500] = {}, p[500] = {};double a[500][500] = {};
		for (int i = 0; i<m; i++){
			cin >> aa >> bb >> cc;
			a[aa][bb] = a[bb][aa] = cc;
		}
		cin >> root; yee.push({ 0, root, 0 });
		edge tmp; double total = 0;
		while (!yee.empty()){
			tmp = yee.top(); yee.pop();
			//cout << tmp.a << ' ' << tmp.b << ' ' << tmp.data << endl;
			if (visit[tmp.b])continue;
			total += tmp.data; p[tmp.b] = tmp.a; visit[tmp.b] = 1;
			for (int i = 1; i <= n; i++){
				if (a[tmp.b][i]!=.0&&(!visit[i])){
					yee.push({tmp.b,i,a[tmp.b][i]});
				}
			}
		}
		for (int i = 1; i <= n; i++)cout << p[i] << ' ';
		cout << fixed << setprecision(3) << endl << total << endl;
	}
}
