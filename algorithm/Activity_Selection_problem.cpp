#include<bits/stdc++.h>
using namespace std;

struct act{
	int l, r, index;
};

bool yee(act a,act b){
	if(a.r != b.r) return a.r<b.r;
	return a.l < b.l; 
}

int main(){
	int tc;
	while(cin >> tc){
		vector<int> ac;
		act a[1005];
		for(int i = 0;i < tc; i++)cin >> a[i].l, a[i].index = i+1;
		for(int i = 0;i < tc; i++)cin >> a[i].r;
		sort(a, a+tc, yee);
		int ans = 1,rr = a[0].r;
		ac.push_back(a[0].index);
		for(int i = 1; i < tc; i++){
			if(rr <= a[i].l){
				ac.push_back(a[i].index);
				rr = a[i].r;
			}
		}
		cout<< ac.size() <<endl;
		cout<< "(" << ac[0];
		for(int i=1;i<ac.size();i++)cout << "," <<ac[i];
		cout << ")\n";
	}
}

