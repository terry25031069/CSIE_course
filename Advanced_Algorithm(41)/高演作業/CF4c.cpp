#include<bits/stdc++.h>
using namespace std;
 
int main(){
	int tc; cin >> tc;
	string s; map<string, int>a;
	while(tc--){
		cin >> s;
		if(a[s]++ == 0){
			cout << "OK\n";
		}else{
			cout << s << a[s] - 1 << endl; 
		}
	}
}
