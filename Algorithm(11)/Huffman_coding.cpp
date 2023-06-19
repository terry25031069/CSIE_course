#include<bits/stdc++.h>
using namespace std;

struct node {
	int L, R, index, data, leng;
	bitset<128>ans;
	bool operator <(const node& b)const {
		if (data != b.data)return data > b.data;
	}
};

node tree[1000]; priority_queue<node>q; bitset<128>code;

void dfs(int idx, int bit, int bound) {
	if (tree[idx].index != -1 && tree[idx].index < bound) {
		tree[idx].ans = code, tree[idx].leng = bit;
		return;
	}
	if (tree[idx].L != -1) {
		code[bit] = 0;
		dfs(tree[idx].L, bit + 1, bound);
	}
	if (tree[idx].R != -1) {
		code[bit] = 1;
		dfs(tree[idx].R, bit + 1, bound);
	}
}

int main() {
	int tc;
	while (cin >> tc) {
		for (int i = 0; i<tc; i++) {
			cin >> tree[i].data;
			tree[i].index = i; tree[i].L = tree[i].R = -1;
			q.push(tree[i]);
		}
		int n = tc;
		while (q.size()>1) {
			node a = q.top(); q.pop(); node b = q.top(); q.pop();
			tree[n].index = n; tree[n].L = a.index; tree[n].R = b.index; tree[n].data = a.data + b.data;
			q.push(tree[n++]);
		}
		cout << tc << endl;
		if (tc == 1)cout << "0\n";
		else {
			dfs(n - 1, 0, tc);
			for (int i = 0; i<tc; i++) {
				if (i != 0)cout << " ";
				for (int j = 0; j<tree[i].leng; j++) cout << tree[i].ans[j];
			}
			cout << endl;
		}
	}
}
