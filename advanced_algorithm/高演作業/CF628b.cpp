#include<bits/stdc++.h>
using namespace std;
#define int long long

int32_t main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string s;
	while(cin >> s){
		int ans = 0;
		for(int i = 0; i < s.size(); i++){
			if(s[i] == '0' || s[i] == '4' || s[i] == '8'){
				ans++;
			}
			if(i > 0){
				string tmps = s.substr(i-1, 2);
				int tmp = stoi(tmps);
				if(tmp % 4 == 0){
					ans += i;
				}
			}
		}
		cout << ans << endl;
	}
}

